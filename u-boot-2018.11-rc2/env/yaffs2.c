// SPDX-License-Identifier: GPL-2.0+
/*
 * (c) Copyright 2016 by VRT Technology
 *
 * Author:
 *  Stuart Longland <stuartl@vrt.com.au>
 *
 * Based on FAT environment driver
 * (c) Copyright 2011 by Tigris Elektronik GmbH
 *
 * Author:
 *  Maximilian Schwerin <mvs@tigris.de>
 *
 * and EXT4 filesystem implementation
 * (C) Copyright 2011 - 2012 Samsung Electronics
 * EXT4 filesystem implementation in Uboot by
 * Uma Shankar <uma.shankar@samsung.com>
 * Manjunatha C Achar <a.manjunatha@samsung.com>
 */

#include <common.h>

#include <command.h>
#include <environment.h>
#include <linux/stddef.h>
#include <malloc.h>
#include <memalign.h>
#include <search.h>
#include <errno.h>
#include <div64.h>
#include <config.h>

#define CONFIG_YAFFS_DIRECT                 1
#define CONFIG_YAFFS_SHORT_NAMES_IN_RAM     1 
#define CONFIG_YAFFS_YAFFS2                 1
#define NO_Y_INLINE                         1
#define CONFIG_YAFFS_PROVIDE_DEFS           1
#define CONFIG_YAFFSFS_PROVIDE_VALUES       1

#include "nand.h"
#include "yaffs2_include/yaffscfg.h"
#include "yaffs2_include/yaffsfs.h"
#include "yaffs2_include/yaffs_packedtags2.h"
#include "yaffs2_include/yaffs_mtdif.h"
#include "yaffs2_include/yaffs_mtdif2.h"

#include <common.h>
#include <errno.h>
#include <spi.h>
#include <spi-mem.h>
#include <linux/mtd/spinand.h>

static const char *yaffs_error_str(void)
{
	int error = yaffsfs_GetLastError();

	if (error < 0)
		error = -error;

	switch (error) {
	case EBUSY: return "Busy";
	case ENODEV: return "No such device";
	case EINVAL: return "Invalid parameter";
	case ENFILE: return "Too many open files";
	case EBADF:  return "Bad handle";
	case EACCES: return "Wrong permissions";
	case EXDEV:  return "Not on same device";
	case ENOENT: return "No such entry";
	case ENOSPC: return "Device full";
	case EROFS:  return "Read only file system";
	case ERANGE: return "Range error";
	case ENOTEMPTY: return "Not empty";
	case ENAMETOOLONG: return "Name too long";
	case ENOMEM: return "Out of memory";
	case EFAULT: return "Fault";
	case EEXIST: return "Name exists";
	case ENOTDIR: return "Not a directory";
	case EISDIR: return "Not permitted on a directory";
	case ELOOP:  return "Symlink loop";
	case 0: return "No error";
	default: return "Unknown error";
	}
}

static int yaffs_regions_overlap(int a, int b, int x, int y)
{
	return	(a <= x && x <= b) ||
		(a <= y && y <= b) ||
		(x <= a && a <= y) ||
		(x <= b && b <= y);
}

void env_yaffs_devconfig(char *_mp, int start_block, int end_block)
{

	struct mtd_info *mtd = NULL;
	struct yaffs_dev *dev = NULL;
	struct yaffs_dev *chk;
	char *mp = NULL;
	struct nand_chip *chip;

	struct udevice *udev;
	int ret;

	ret = uclass_get_device_by_driver(UCLASS_MTD,
					  DM_GET_DRIVER(spinand),
					  &udev);
	if (ret && ret != -ENODEV)
		pr_err("Failed to initialize MXS NAND controller. (error %d)\n", ret);

    mtd = dev_get_uclass_priv(udev);

//	mtd = get_nand_dev_by_index(flash_dev);
  if (!mtd)
    printf("warning: empty global mtd_info!!!!!!\n");

	if (!mtd) {
		pr_err("\nno NAND devices available\n");
		return;
	}

	dev = calloc(1, sizeof(*dev));
	mp = strdup(_mp);

	if (!dev || !mp) {
		/* Alloc error */
		printf("Failed to allocate memory\n");
		goto err;
	}

	if (end_block == 0)
		end_block = lldiv(mtd->size, mtd->erasesize - 1);

	if (end_block < start_block) {
		printf("Bad start/end\n");
		goto err;
	}

	chip =  mtd_to_nand(mtd);

	/* Check for any conflicts */
	yaffs_dev_rewind();
	while (1) {
		chk = yaffs_next_dev();
		if (!chk)
			break;
		if (strcmp(chk->param.name, mp) == 0) {
			printf("Mount point name already used\n");
			goto err;
		}
		if (chk->driver_context == mtd &&
			yaffs_regions_overlap(
				chk->param.start_block, chk->param.end_block,
				start_block, end_block)) {
			printf("Region overlaps with partition %s\n",
				chk->param.name);
			goto err;
		}

	}

	/* Seems sane, so configure */
	memset(dev, 0, sizeof(*dev));
	dev->param.name = mp;
	dev->driver_context = mtd;
	dev->param.start_block = start_block;
	dev->param.end_block = end_block;
	dev->param.chunks_per_block = mtd->erasesize / mtd->writesize;
	dev->param.total_bytes_per_chunk = mtd->writesize;
	dev->param.is_yaffs2 = 1;
	dev->param.use_nand_ecc = 1;
	dev->param.n_reserved_blocks = 5;
	if (chip->ecc.layout->oobavail < sizeof(struct yaffs_packed_tags2))
		dev->param.inband_tags = 1;
	dev->param.n_caches = 10;
	dev->param.write_chunk_tags_fn = nandmtd2_write_chunk_tags;
	dev->param.read_chunk_tags_fn = nandmtd2_read_chunk_tags;
	dev->param.erase_fn = nandmtd_EraseBlockInNAND;
	dev->param.initialise_flash_fn = nandmtd_InitialiseNAND;
	dev->param.bad_block_fn = nandmtd2_MarkNANDBlockBad;
	dev->param.query_block_fn = nandmtd2_QueryNANDBlock;

	yaffs_add_device(dev);

	printf("Configures yaffs mount %s: dev %d start block %d, end block %d %s\n",
		mp, 0, start_block, end_block,
		dev->param.inband_tags ? "using inband tags" : "");
	return;

err:
	free(dev);
	free(mp);

}

void env_yaffs_mount(char *mp)
{
	int retval = yaffs_mount(mp);
	if (retval < 0)
		printf("Error mounting %s, return value: %d, %s\n", mp,
			yaffsfs_GetError(), yaffs_error_str());
}

static int env_yaffs_load(void)
{
	ALLOC_CACHE_ALIGN_BUFFER(char, buf, CONFIG_ENV_SIZE);
	int err;
//	loff_t off;

	int h;
	struct yaffs_stat s;
    char *fn = "/uboot.env"; 
//    char *addr;

    env_yaffs_devconfig("/", 0x80, 0x180);
    env_yaffs_mount("/");

	yaffs_stat(fn, &s);

//	printf("Copy %s to 0x%p... ", fn, addr);
	h = yaffs_open(fn, O_RDWR, 0);
	if (h < 0) {
		printf("File not found\n");
		return -EIO;
	}

	err = yaffs_read(h, buf, CONFIG_ENV_SIZE);
	printf("\t[DONE]\n");

	yaffs_close(h);
    yaffs_unmount("/");

	if (err == -1) {
		printf("\n** Unable to read \"%s\" from yaffs2 **\n", fn);
		goto err_env_relocate;
	}

	return env_import(buf, 1);

err_env_relocate:
	set_default_env(NULL, 0);

	return -EIO;
}

static int env_yaffs_save(void)
{
	env_t	env_new;
	int outh;
    char *fn = "/uboot.env"; 
//    char *addr; 
//    int size;
    int err;

	err = env_export(&env_new);
	if (err)
		return err;
   
    env_yaffs_devconfig("/", 0x80, 0x180);
    env_yaffs_mount("/");
	
    outh = yaffs_open(fn, O_CREAT | O_RDWR | O_TRUNC, S_IREAD | S_IWRITE);
	if (outh < 0)
		printf("Error opening file: %d, %s\n", outh, yaffs_error_str());

	err = yaffs_write(outh, (void *)&env_new, sizeof(env_t));

	yaffs_close(outh);
    yaffs_unmount("/");
	
    if (err == -1) {
		printf("\n** Unable to write \"%s\" from yaffs2 **\n", fn);
		return 1;
	}

	puts("done\n");
	return 0;
}

U_BOOT_ENV_LOCATION(yaffs2) = {
	.location	= ENVL_YAFFS2,
	ENV_NAME("YAFFS2")
	.load		= env_yaffs_load,
	.save		= env_save_ptr(env_yaffs_save),
};

#if 0
#ifdef CONFIG_CMD_SAVEENV
static int env_ext4_save(void)
{
	env_t	env_new;
	struct blk_desc *dev_desc = NULL;
	disk_partition_t info;
	int dev, part;
	int err;

	err = env_export(&env_new);
	if (err)
		return err;

	part = blk_get_device_part_str(CONFIG_ENV_EXT4_INTERFACE,
				       CONFIG_ENV_EXT4_DEVICE_AND_PART,
				       &dev_desc, &info, 1);
	if (part < 0)
		return 1;

	dev = dev_desc->devnum;
	ext4fs_set_blk_dev(dev_desc, &info);

	if (!ext4fs_mount(info.size)) {
		printf("\n** Unable to use %s %s for saveenv **\n",
		       CONFIG_ENV_EXT4_INTERFACE,
		       CONFIG_ENV_EXT4_DEVICE_AND_PART);
		return 1;
	}

	err = ext4fs_write(CONFIG_ENV_EXT4_FILE, (void *)&env_new,
			   sizeof(env_t));
	ext4fs_close();

	if (err == -1) {
		printf("\n** Unable to write \"%s\" from %s%d:%d **\n",
			CONFIG_ENV_EXT4_FILE, CONFIG_ENV_EXT4_INTERFACE, dev,
			part);
		return 1;
	}

	puts("done\n");
	return 0;
}
#endif /* CONFIG_CMD_SAVEENV */

static int env_ext4_load(void)
{
	ALLOC_CACHE_ALIGN_BUFFER(char, buf, CONFIG_ENV_SIZE);
	struct blk_desc *dev_desc = NULL;
	disk_partition_t info;
	int dev, part;
	int err;
	loff_t off;

#ifdef CONFIG_MMC
	if (!strcmp(CONFIG_ENV_EXT4_INTERFACE, "mmc"))
		mmc_initialize(NULL);
#endif

	part = blk_get_device_part_str(CONFIG_ENV_EXT4_INTERFACE,
				       CONFIG_ENV_EXT4_DEVICE_AND_PART,
				       &dev_desc, &info, 1);
	if (part < 0)
		goto err_env_relocate;

	dev = dev_desc->devnum;
	ext4fs_set_blk_dev(dev_desc, &info);

	if (!ext4fs_mount(info.size)) {
		printf("\n** Unable to use %s %s for loading the env **\n",
		       CONFIG_ENV_EXT4_INTERFACE,
		       CONFIG_ENV_EXT4_DEVICE_AND_PART);
		goto err_env_relocate;
	}

	err = ext4_read_file(CONFIG_ENV_EXT4_FILE, buf, 0, CONFIG_ENV_SIZE,
			     &off);
	ext4fs_close();

	if (err == -1) {
		printf("\n** Unable to read \"%s\" from %s%d:%d **\n",
			CONFIG_ENV_EXT4_FILE, CONFIG_ENV_EXT4_INTERFACE, dev,
			part);
		goto err_env_relocate;
	}

	return env_import(buf, 1);

err_env_relocate:
	set_default_env(NULL, 0);

	return -EIO;
}

U_BOOT_ENV_LOCATION(ext4) = {
	.location	= ENVL_EXT4,
	ENV_NAME("EXT4")
	.load		= env_ext4_load,
	.save		= env_save_ptr(env_ext4_save),
};
#endif
