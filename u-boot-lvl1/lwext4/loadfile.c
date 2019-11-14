#include <ext4.h>
#include <stdint.h>
#include <stdio.h>
#include "mmc_dev.h"

#ifdef  UART
#include "../uart.h"
#endif

#define BUFSZ 4096

//static void die(void)
//{
//	while (1)
//		;
//}

void loadfile(void *addr)
{
	size_t size = BUFSZ;
	ext4_file bootfile;
	struct ext4_blockdev *blk = mmc_dev_get();
	int r;

	r = ext4_device_register(blk, "mmc");
	if (r != EOK) {
#ifdef  UART
       Uart_Printf("BOOT1 ext4 device register error! \n\r");
#endif
	}

	r = ext4_mount("mmc", "/", true /* read only */);
	if (r != EOK) {
#ifdef  UART
       Uart_Printf("BOOT1 ext4 mount error! \n\r");
#endif
    }

	r = ext4_fopen2(&bootfile, "/u-boot.bin", O_RDONLY);
	if (r != EOK) {
#ifdef  UART
        Uart_Printf("ext4 fopen2 error! \n\r");
#endif
    }

	while (size) {
		r = ext4_fread(&bootfile, addr, BUFSZ, &size);
		if (r != EOK) {
#ifdef  UART
            Uart_Printf("ext4 fread error! \n\r");
#endif
        }
		addr += size;
	}

	ext4_fclose(&bootfile);
	ext4_umount("/");
}
