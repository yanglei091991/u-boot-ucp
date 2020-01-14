#include <ext4.h>
#include <stdint.h>
#include <stdio.h>
#include "mmc_dev.h"

#ifdef  UART
#include "../uart.h"
#endif

#define BUFSZ 4096
#define SM3_END_ADDR 0x04f60000

typedef struct part_entry
{
	uint8_t sts;
	uint8_t chs_first[3];
	uint8_t part_type;
	uint8_t chs_last[3];
	uint32_t lba_first;
	uint32_t lba_size;
} part_entry;

uint32_t mmc_bread(uint32_t start, uint32_t blkcnt,void *dst);

static int read_to_addr(ext4_file *bootfile, void *addr)
{
	size_t size = BUFSZ;
	int r;

	while (size) {
		r = ext4_fread(bootfile, addr, BUFSZ, &size);
		if (r != EOK) {
#ifdef  UART
            Uart_Printf("error: ext4 fread u-boot.bin fail! \n\r");
#endif
            return false;
        }
		addr += size;
        if((int)addr >= (int)SM3_END_ADDR)
        {
#ifdef  UART
            Uart_Printf("error: u-boot.bin file more than 1M! \n\r");
#endif
            return false;
        }
	}
	return true;
}

int try_partition(void *addr)
{
	uint8_t bootblock[512];
	ext4_file bootfile;
	int r;

	mmc_bread(0, 1, bootblock);

	// check MBR signature
	if (bootblock[510] != 0x55 || bootblock[511] != 0xaa)
		return 0;

	struct ext4_blockdev *ext4dev = mmc_part_dev_get();
	if (ext4_device_register(ext4dev, "mmcpart") != EOK) {
#ifdef  UART
       Uart_Printf("error: ext4 partition device register fail! \n\r");
#endif
       return false;
	}
	// check each partition
	// we're going to find the first available Linux partition
	for (size_t i = 0; i < 4; i++) {
		part_entry *part = (part_entry*)(&bootblock[446 + i * 16]);
		if (part->part_type == 0x83) {
			// mount the partition and find u-boot.bin
			mmc_part_dev_setpart(part->lba_first, part->lba_size);
			r = ext4_mount("mmcpart", "/", true /* read only */);
			if (r != EOK) {
#ifdef  UART
				Uart_Printf("error: mount mmc partition fail! \n\r");
#endif
				continue;
			}
			r = ext4_fopen2(&bootfile, "/u-boot.bin", O_RDONLY);
			if (r != EOK) {
#ifdef  UART
				Uart_Printf("error: open u-boot.bin in partition fail! \n\r");
#endif
				ext4_umount("/");
				continue;
			}
			if (!read_to_addr(&bootfile, addr)) {
#ifdef  UART
				Uart_Printf("error: load u-boot.bin error!\n\r");
#endif
				ext4_fclose(&bootfile);
				ext4_umount("/");
				continue;
			}
			ext4_fclose(&bootfile);
			ext4_umount("/");
			return true;
		}
	}
	return false;
}

int loadfile(void *addr)
{
	ext4_file bootfile;
	struct ext4_blockdev *blk = mmc_dev_get();
	int r;

	if (try_partition(addr))
		return true;

	r = ext4_device_register(blk, "mmc");
	if (r != EOK) {
#ifdef  UART
       Uart_Printf("error: ext4 device register fail! \n\r");
#endif
       return false;
	}

	r = ext4_mount("mmc", "/", true /* read only */);
	if (r != EOK) {
#ifdef  UART
       Uart_Printf("error: ext4 mount ""/"" fail! \n\r");
#endif
       return false;
    }

	r = ext4_fopen2(&bootfile, "/u-boot.bin", O_RDONLY);
	if (r != EOK) {
#ifdef  UART
        Uart_Printf("error: ext4 open u-boot.bin fail! \n\r");
#endif
        return false;
    }

	if (!read_to_addr(&bootfile, addr))
		return false;

	ext4_fclose(&bootfile);
	ext4_umount("/");

    return true;
}
