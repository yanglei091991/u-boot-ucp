#include <ext4.h>
#include <stdint.h>
#include <stdio.h>
#include "mmc_dev.h"

#ifdef  UART
#include "../uart.h"
#endif

#define BUFSZ 4096
#define SM3_END_ADDR 0x04f60000

int loadfile(void *addr)
{
	size_t size = BUFSZ;
	ext4_file bootfile;
	struct ext4_blockdev *blk = mmc_dev_get();
	int r;

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

	while (size) {
		r = ext4_fread(&bootfile, addr, BUFSZ, &size);
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

	ext4_fclose(&bootfile);
	ext4_umount("/");

    return true;
}
