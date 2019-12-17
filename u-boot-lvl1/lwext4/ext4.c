/*
 * Copyright (c) 2013 Grzegorz Kostka (kostka.grzegorz@gmail.com)
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

/** @addtogroup lwext4
 * @{
 */
/**
 * @file  ext4.h
 * @brief Ext4 high level operations (file, directory, mountpoints...)
 */

#include <ext4_config.h>
#include <ext4_types.h>
#include <ext4_misc.h>
#include <ext4_errno.h>
#include <ext4_oflags.h>
#include <ext4_debug.h>

#include <ext4.h>
#include <ext4_trans.h>
#include <ext4_blockdev.h>
#include <ext4_fs.h>
#include <ext4_dir.h>
#include <ext4_inode.h>
#include <ext4_super.h>
#include <ext4_block_group.h>
#include <ext4_dir_idx.h>
#include <ext4_journal.h>


#include <stdlib.h>
#include <string.h>

/**@brief   Mount point OS dependent lock*/
#define EXT4_MP_LOCK(_m)                                                       \
	do {                                                                   \
		if ((_m)->os_locks)                                            \
			(_m)->os_locks->lock();                                \
	} while (0)

/**@brief   Mount point OS dependent unlock*/
#define EXT4_MP_UNLOCK(_m)                                                     \
	do {                                                                   \
		if ((_m)->os_locks)                                            \
			(_m)->os_locks->unlock();                              \
	} while (0)

/**@brief   Mount point descriptor.*/
struct ext4_mountpoint {

	/**@brief   Mount done flag.*/
	bool mounted;

	/**@brief   Mount point name (@ref ext4_mount)*/
	char name[CONFIG_EXT4_MAX_MP_NAME + 1];

	/**@brief   OS dependent lock/unlock functions.*/
	const struct ext4_lock *os_locks;

	/**@brief   Ext4 filesystem internals.*/
	struct ext4_fs fs;

	/**@brief   JBD fs.*/
	struct jbd_fs jbd_fs;

	/**@brief   Journal.*/
	struct jbd_journal jbd_journal;

	/**@brief   Block cache.*/
	struct ext4_bcache bc;
};

/**@brief   Block devices descriptor.*/
struct ext4_block_devices {

	/**@brief   Block device name.*/
	char name[CONFIG_EXT4_MAX_BLOCKDEV_NAME + 1];

	/**@brief   Block device handle.*/
	struct ext4_blockdev *bd;
};

/**@brief   Block devices.*/
static struct ext4_block_devices s_bdevices[CONFIG_EXT4_BLOCKDEVS_COUNT];

/**@brief   Mountpoints.*/
static struct ext4_mountpoint s_mp[CONFIG_EXT4_MOUNTPOINTS_COUNT];

int ext4_device_register(struct ext4_blockdev *bd,
			 const char *dev_name)
{
	ext4_assert(bd && dev_name);

	if (strlen(dev_name) > CONFIG_EXT4_MAX_BLOCKDEV_NAME)
		return EINVAL;

	for (size_t i = 0; i < CONFIG_EXT4_BLOCKDEVS_COUNT; ++i) {
		if (!strcmp(s_bdevices[i].name, dev_name))
			return EEXIST;
	}

	for (size_t i = 0; i < CONFIG_EXT4_BLOCKDEVS_COUNT; ++i) {
		if (!s_bdevices[i].bd) {
			strcpy(s_bdevices[i].name, dev_name);
			s_bdevices[i].bd = bd;
			return EOK;
		}
	}

	return ENOSPC;
}

int ext4_device_unregister(const char *dev_name)
{
	ext4_assert(dev_name);

	for (size_t i = 0; i < CONFIG_EXT4_BLOCKDEVS_COUNT; ++i) {
		if (strcmp(s_bdevices[i].name, dev_name))
			continue;

		memset(&s_bdevices[i], 0, sizeof(s_bdevices[i]));
	}

	return ENOENT;
}

int ext4_device_unregister_all(void)
{
	memset(s_bdevices, 0, sizeof(s_bdevices));

	return EOK;
}

/****************************************************************************/

int ext4_mount(const char *dev_name, const char *mount_point,
	       bool read_only)
{
	int r;
	uint32_t bsize;
	struct ext4_bcache *bc;
	struct ext4_blockdev *bd = 0;
	struct ext4_mountpoint *mp = 0;

	ext4_assert(mount_point && dev_name);

	size_t mp_len = strlen(mount_point);

	if (mp_len > CONFIG_EXT4_MAX_MP_NAME)
		return EINVAL;

	if (mount_point[mp_len - 1] != '/')
		return ENOTSUP;

	for (size_t i = 0; i < CONFIG_EXT4_BLOCKDEVS_COUNT; ++i) {
		if (!strcmp(dev_name, s_bdevices[i].name)) {
			bd = s_bdevices[i].bd;
			break;
		}
	}

	if (!bd)
		return ENODEV;

	for (size_t i = 0; i < CONFIG_EXT4_MOUNTPOINTS_COUNT; ++i) {
		if (!s_mp[i].mounted) {
			strcpy(s_mp[i].name, mount_point);
			s_mp[i].mounted = 1;
			mp = &s_mp[i];
			break;
		}

		if (!strcmp(s_mp[i].name, mount_point))
			return EOK;
	}

	if (!mp)
		return ENOMEM;

	r = ext4_block_init(bd);
	if (r != EOK)
		return r;

	r = ext4_fs_init(&mp->fs, bd, read_only);
	if (r != EOK) {
		ext4_block_fini(bd);
		return r;
	}

	bsize = ext4_sb_get_block_size(&mp->fs.sb);
	ext4_block_set_lb_size(bd, bsize);
	bc = &mp->bc;

	r = ext4_bcache_init_dynamic(bc, CONFIG_BLOCK_DEV_CACHE_SIZE, bsize);
	if (r != EOK) {
		ext4_block_fini(bd);
		return r;
	}

	if (bsize != bc->itemsize)
		return ENOTSUP;

	/*Bind block cache to block device*/
	r = ext4_block_bind_bcache(bd, bc);
	if (r != EOK) {
		ext4_bcache_cleanup(bc);
		ext4_block_fini(bd);
		ext4_bcache_fini_dynamic(bc);
		return r;
	}

	bd->fs = &mp->fs;
	return r;
}


int ext4_umount(const char *mount_point)
{
	int i;
	int r;
	struct ext4_mountpoint *mp = 0;

	for (i = 0; i < CONFIG_EXT4_MOUNTPOINTS_COUNT; ++i) {
		if (!strcmp(s_mp[i].name, mount_point)) {
			mp = &s_mp[i];
			break;
		}
	}

	if (!mp)
		return ENODEV;

	r = ext4_fs_fini(&mp->fs);
	if (r != EOK)
		goto Finish;

	mp->mounted = 0;

	ext4_bcache_cleanup(mp->fs.bdev->bc);
	ext4_bcache_fini_dynamic(mp->fs.bdev->bc);

	r = ext4_block_fini(mp->fs.bdev);
Finish:
	mp->fs.bdev->fs = NULL;
	return r;
}

static struct ext4_mountpoint *ext4_get_mount(const char *path)
{
	for (size_t i = 0; i < CONFIG_EXT4_MOUNTPOINTS_COUNT; ++i) {

		if (!s_mp[i].mounted)
			continue;

		if (!strncmp(s_mp[i].name, path, strlen(s_mp[i].name)))
			return &s_mp[i];
	}

	return NULL;
}


__unused
static int __ext4_trans_start(struct ext4_mountpoint *mp)
{
	int r = EOK;

	if (mp->fs.jbd_journal && !mp->fs.curr_trans) {
		struct jbd_journal *journal = mp->fs.jbd_journal;
		struct jbd_trans *trans;
		trans = jbd_journal_new_trans(journal);
		if (!trans) {
			r = ENOMEM;
			goto Finish;
		}
		mp->fs.curr_trans = trans;
	}
Finish:
	return r;
}

__unused
static int __ext4_trans_stop(struct ext4_mountpoint *mp)
{
	int r = EOK;

	if (mp->fs.jbd_journal && mp->fs.curr_trans) {
		struct jbd_journal *journal = mp->fs.jbd_journal;
		struct jbd_trans *trans = mp->fs.curr_trans;
		r = jbd_journal_commit_trans(journal, trans);
		mp->fs.curr_trans = NULL;
	}
	return r;
}

__unused
static void __ext4_trans_abort(struct ext4_mountpoint *mp)
{
	if (mp->fs.jbd_journal && mp->fs.curr_trans) {
		struct jbd_journal *journal = mp->fs.jbd_journal;
		struct jbd_trans *trans = mp->fs.curr_trans;
		jbd_journal_free_trans(journal, trans, true);
		mp->fs.curr_trans = NULL;
	}
}

static int ext4_trans_start(struct ext4_mountpoint *mp __unused)
{
	int r = EOK;
#if CONFIG_JOURNALING_ENABLE
	r = __ext4_trans_start(mp);
#endif
	return r;
}

static int ext4_trans_stop(struct ext4_mountpoint *mp __unused)
{
	int r = EOK;
#if CONFIG_JOURNALING_ENABLE
	r = __ext4_trans_stop(mp);
#endif
	return r;
}

static void ext4_trans_abort(struct ext4_mountpoint *mp __unused)
{
#if CONFIG_JOURNALING_ENABLE
	__ext4_trans_abort(mp);
#endif
}

/********************************FILE OPERATIONS*****************************/

static int ext4_path_check(const char *path, bool *is_goal)
{
	int i;

	for (i = 0; i < EXT4_DIRECTORY_FILENAME_LEN; ++i) {

		if (path[i] == '/') {
			*is_goal = false;
			return i;
		}

		if (path[i] == 0) {
			*is_goal = true;
			return i;
		}
	}

	return 0;
}

/*
 * NOTICE: if filetype is equal to EXT4_DIRENTRY_UNKNOWN,
 * any filetype of the target dir entry will be accepted.
 */
static int ext4_generic_open2(ext4_file *f, const char *path, int flags,
			      int ftype, uint32_t *parent_inode,
			      uint32_t *name_off)
{
	bool is_goal = false;
	uint32_t imode = EXT4_INODE_MODE_DIRECTORY;
	uint32_t next_inode;

	int r;
	int len;
	struct ext4_mountpoint *mp = ext4_get_mount(path);
	struct ext4_dir_search_result result;
	struct ext4_inode_ref ref;

	f->mp = 0;

	if (!mp)
		return ENOENT;

	struct ext4_fs *const fs = &mp->fs;
	struct ext4_sblock *const sb = &mp->fs.sb;

	if (fs->read_only && flags & O_CREAT)
		return EROFS;

	f->flags = flags;

	/*Skip mount point*/
	path += strlen(mp->name);

	if (name_off)
		*name_off = strlen(mp->name);

	/*Load root*/
	r = ext4_fs_get_inode_ref(fs, EXT4_INODE_ROOT_INDEX, &ref);
	if (r != EOK)
		return r;

	if (parent_inode)
		*parent_inode = ref.index;

	len = ext4_path_check(path, &is_goal);
	while (1) {

		len = ext4_path_check(path, &is_goal);
		if (!len) {
			/*If root open was request.*/
			if (ftype == EXT4_DE_DIR || ftype == EXT4_DE_UNKNOWN)
				if (is_goal)
					break;

			r = ENOENT;
			break;
		}

		r = ext4_dir_find_entry(&result, &ref, path, len);
		if (r != EOK) {

			/*Destroy last result*/
			ext4_dir_destroy_result(&ref, &result);
			break; // ENOENT
		}

		if (parent_inode)
			*parent_inode = ref.index;

		next_inode = ext4_dir_en_get_inode(result.dentry);
		if (ext4_sb_feature_incom(sb, EXT4_FINCOM_FILETYPE)) {
			uint8_t t;
			t = ext4_dir_en_get_inode_type(sb, result.dentry);
			imode = ext4_fs_correspond_inode_mode(t);
		} else {
			struct ext4_inode_ref child_ref;
			r = ext4_fs_get_inode_ref(fs, next_inode, &child_ref);
			if (r != EOK)
				break;

			imode = ext4_inode_type(sb, child_ref.inode);
			ext4_fs_put_inode_ref(&child_ref);
		}

		r = ext4_dir_destroy_result(&ref, &result);
		if (r != EOK)
			break;

		/*If expected file error*/
		if (imode != EXT4_INODE_MODE_DIRECTORY && !is_goal) {
			r = ENOENT;
			break;
		}
		if (ftype != EXT4_DE_UNKNOWN) {
			bool df = imode != ext4_fs_correspond_inode_mode(ftype);
			if (df && is_goal) {
				r = ENOENT;
				break;
			}
		}

		r = ext4_fs_put_inode_ref(&ref);
		if (r != EOK)
			break;

		r = ext4_fs_get_inode_ref(fs, next_inode, &ref);
		if (r != EOK)
			break;

		if (is_goal)
			break;

		path += len + 1;

		if (name_off)
			*name_off += len + 1;
	}

	if (r != EOK) {
		ext4_fs_put_inode_ref(&ref);
		return r;
	}

	if (is_goal) {

		if ((f->flags & O_TRUNC)) {
			return EINVAL;
		}

		f->mp = mp;
		f->fsize = ext4_inode_get_size(sb, ref.inode);
		f->inode = ref.index;
		f->fpos = 0;

		if (f->flags & O_APPEND)
			f->fpos = f->fsize;
	}

	return ext4_fs_put_inode_ref(&ref);
}

/****************************************************************************/

int ext4_fopen2(ext4_file *file, const char *path, int flags)
{
	struct ext4_mountpoint *mp = ext4_get_mount(path);
	int r;
	int filetype;

	if (!mp)
		return ENOENT;

        filetype = EXT4_DE_REG_FILE;

	EXT4_MP_LOCK(mp);
	ext4_block_cache_write_back(mp->fs.bdev, 1);

	if (flags & O_CREAT)
		ext4_trans_start(mp);

	r = ext4_generic_open2(file, path, flags, filetype, NULL, NULL);

	if (flags & O_CREAT) {
		if (r == EOK)
			ext4_trans_stop(mp);
		else
			ext4_trans_abort(mp);
	}

	ext4_block_cache_write_back(mp->fs.bdev, 0);
	EXT4_MP_UNLOCK(mp);

	return r;
}

int ext4_fclose(ext4_file *file)
{
	ext4_assert(file && file->mp);

	file->mp = 0;
	file->flags = 0;
	file->inode = 0;
	file->fpos = file->fsize = 0;

	return EOK;
}

int ext4_fread(ext4_file *file, void *buf, size_t size, size_t *rcnt)
{
	uint32_t unalg;
	uint32_t iblock_idx;
	uint32_t iblock_last;
	uint32_t block_size;

	ext4_fsblk_t fblock;
	ext4_fsblk_t fblock_start;
	uint32_t fblock_count;

	uint8_t *u8_buf = buf;
	int r;
	struct ext4_inode_ref ref;

	ext4_assert(file && file->mp);

	if (file->flags & O_WRONLY)
		return EPERM;

	if (!size)
		return EOK;

	EXT4_MP_LOCK(file->mp);

	struct ext4_fs *const fs = &file->mp->fs;
	struct ext4_sblock *const sb = &file->mp->fs.sb;

	if (rcnt)
		*rcnt = 0;

	r = ext4_fs_get_inode_ref(fs, file->inode, &ref);
	if (r != EOK) {
		EXT4_MP_UNLOCK(file->mp);
		return r;
	}

	/*Sync file size*/
	file->fsize = ext4_inode_get_size(sb, ref.inode);

	block_size = ext4_sb_get_block_size(sb);
	size = ((uint64_t)size > (file->fsize - file->fpos))
		? ((size_t)(file->fsize - file->fpos)) : size;

	iblock_idx = (uint32_t)((file->fpos) / block_size);
	iblock_last = (uint32_t)((file->fpos + size) / block_size);
	unalg = (file->fpos) % block_size;

	/*If the size of symlink is smaller than 60 bytes*/
	bool softlink;
	softlink = ext4_inode_is_type(sb, ref.inode, EXT4_INODE_MODE_SOFTLINK);
	if (softlink && file->fsize < sizeof(ref.inode->blocks)
		     && !ext4_inode_get_blocks_count(sb, ref.inode)) {

		char *content = (char *)ref.inode->blocks;
		if (file->fpos < file->fsize) {
			size_t len = size;
			if (unalg + size > (uint32_t)file->fsize)
				len = (uint32_t)file->fsize - unalg;
			memcpy(buf, content + unalg, len);
			if (rcnt)
				*rcnt = len;

		}

		r = EOK;
		goto Finish;
	}

	if (unalg) {
		size_t len =  size;
		if (size > (block_size - unalg))
			len = block_size - unalg;

		r = ext4_fs_get_inode_dblk_idx(&ref, iblock_idx, &fblock, true);
		if (r != EOK)
			goto Finish;

		/* Do we get an unwritten range? */
		if (fblock != 0) {
			uint64_t off = fblock * block_size + unalg;
			r = ext4_block_readbytes(file->mp->fs.bdev, off, u8_buf, len);
			if (r != EOK)
				goto Finish;

		} else {
			/* Yes, we do. */
			memset(u8_buf, 0, len);
		}

		u8_buf += len;
		size -= len;
		file->fpos += len;

		if (rcnt)
			*rcnt += len;

		iblock_idx++;
	}

	fblock_start = 0;
	fblock_count = 0;
	while (size >= block_size) {
		while (iblock_idx < iblock_last) {
			r = ext4_fs_get_inode_dblk_idx(&ref, iblock_idx,
						       &fblock, true);
			if (r != EOK)
				goto Finish;

			iblock_idx++;

			if (!fblock_start)
				fblock_start = fblock;

			if ((fblock_start + fblock_count) != fblock)
				break;

			fblock_count++;
		}

		r = ext4_blocks_get_direct(file->mp->fs.bdev, u8_buf, fblock_start,
					   fblock_count);
		if (r != EOK)
			goto Finish;

		size -= block_size * fblock_count;
		u8_buf += block_size * fblock_count;
		file->fpos += block_size * fblock_count;

		if (rcnt)
			*rcnt += block_size * fblock_count;

		fblock_start = fblock;
		fblock_count = 1;
	}

	if (size) {
		uint64_t off;
		r = ext4_fs_get_inode_dblk_idx(&ref, iblock_idx, &fblock, true);
		if (r != EOK)
			goto Finish;

		off = fblock * block_size;
		r = ext4_block_readbytes(file->mp->fs.bdev, off, u8_buf, size);
		if (r != EOK)
			goto Finish;

		file->fpos += size;

		if (rcnt)
			*rcnt += size;
	}

Finish:
	ext4_fs_put_inode_ref(&ref);
	EXT4_MP_UNLOCK(file->mp);
	return r;
}

int ext4_fseek(ext4_file *file, int64_t offset, uint32_t origin)
{
	switch (origin) {
	case SEEK_SET:
		if (offset < 0 || (uint64_t)offset > file->fsize)
			return EINVAL;

		file->fpos = offset;
		return EOK;
	case SEEK_CUR:
		if ((offset < 0 && (uint64_t)(-offset) > file->fpos) ||
		    (offset > 0 &&
		     (uint64_t)offset > (file->fsize - file->fpos)))
			return EINVAL;

		file->fpos += offset;
		return EOK;
	case SEEK_END:
		if (offset < 0 || (uint64_t)offset > file->fsize)
			return EINVAL;

		file->fpos = file->fsize - offset;
		return EOK;
	}
	return EINVAL;
}

uint64_t ext4_ftell(ext4_file *file)
{
	return file->fpos;
}

uint64_t ext4_fsize(ext4_file *file)
{
	return file->fsize;
}
