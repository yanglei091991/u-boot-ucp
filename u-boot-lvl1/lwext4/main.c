#include <ext4.h>
#include <stdint.h>
#include <stdio.h>
#include "file_dev.h"

#define BUFSZ 128

void printptr(void);

int main()
{
	ext4_file bootfile;
	uint8_t buffer[BUFSIZ];
	size_t size = -1;

	file_dev_name_set("/tmp/fs.img");
	struct ext4_blockdev *blk = file_dev_get();
	ext4_device_register(blk, "mmc");

	ext4_mount("mmc", "/", true /* read only */);

	ext4_fopen(&bootfile, "/boot.txt", "rb");

	while (size) {
		ext4_fread(&bootfile, buffer, BUFSZ, &size);
		for (size_t i = 0; i < size; i++)
			putchar(buffer[i]);
	}

	ext4_fclose(&bootfile);
	ext4_umount("/");
	puts("\nbuffer size used:");
	printptr();
}
