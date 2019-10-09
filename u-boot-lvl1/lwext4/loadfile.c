#include <ext4.h>
#include <stdint.h>
#include <stdio.h>
#include "mmc_dev.h"

#define BUFSZ 4096

void loadfile(void *addr)
{
	size_t size = BUFSZ;
	ext4_file bootfile;
	struct ext4_blockdev *blk = mmc_dev_get();
	ext4_device_register(blk, "mmc");

	ext4_mount("mmc", "/", true /* read only */);

	ext4_fopen2(&bootfile, "/boot.bin", O_RDONLY);

	while (size) {
		ext4_fread(&bootfile, addr, BUFSZ, &size);
		addr += size;
	}

	ext4_fclose(&bootfile);
	ext4_umount("/");
}
