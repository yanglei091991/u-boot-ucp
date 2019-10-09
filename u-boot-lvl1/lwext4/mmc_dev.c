/*
 * Copyright (c) 2019 Cai Sipei
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <ext4_config.h>
#include <ext4_blockdev.h>
#include <ext4_errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

uint32_t mmc_bread(uint32_t start, uint32_t blkcnt,void *dst);

/**********************BLOCKDEV INTERFACE**************************************/
static int mmc_dev_open(struct ext4_blockdev *bdev);
static int mmc_dev_bread(struct ext4_blockdev *bdev, void *buf, uint64_t blk_id,
			 uint32_t blk_cnt);
static int mmc_dev_bwrite(struct ext4_blockdev *bdev, const void *buf,
			  uint64_t blk_id, uint32_t blk_cnt);
static int mmc_dev_close(struct ext4_blockdev *bdev);

/******************************************************************************/
EXT4_BLOCKDEV_STATIC_INSTANCE(mmc_dev, 512 /* block size */, 0, mmc_dev_open,
		mmc_dev_bread, mmc_dev_bwrite, mmc_dev_close, 0, 0);

/******************************************************************************/
static int mmc_dev_open(struct ext4_blockdev *bdev)
{
	/* TODO: do mmc init? */
	return EOK;
}

/******************************************************************************/

static int mmc_dev_bread(struct ext4_blockdev *bdev, void *buf, uint64_t blk_id,
			 uint32_t blk_cnt)
{
	/* NOTE: bdev->bdif->ph_bsize and MMC block size must be 512 */
	mmc_bread(blk_id, blk_cnt, buf);

	return EOK;
}

/******************************************************************************/
static int mmc_dev_bwrite(struct ext4_blockdev *bdev, const void *buf,
			  uint64_t blk_id, uint32_t blk_cnt)
{
	return EIO;
}
/******************************************************************************/
static int mmc_dev_close(struct ext4_blockdev *bdev)
{
	return EOK;
}

/******************************************************************************/
struct ext4_blockdev *mmc_dev_get(void)
{
	return &mmc_dev;
}
/******************************************************************************/
