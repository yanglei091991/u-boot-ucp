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
 * @file  ext4_dir_idx.c
 * @brief Directory indexing procedures.
 */

#include <ext4_config.h>
#include <ext4_types.h>
#include <ext4_misc.h>
#include <ext4_errno.h>
#include <ext4_debug.h>

#include <ext4_trans.h>
#include <ext4_dir_idx.h>
#include <ext4_dir.h>
#include <ext4_blockdev.h>
#include <ext4_fs.h>
#include <ext4_super.h>
#include <ext4_inode.h>
#include <ext4_crc32.h>
#include <ext4_hash.h>

#include <string.h>
#include <stdlib.h>

/**@brief Get hash version used in directory index.
 * @param root_info Pointer to root info structure of index
 * @return Hash algorithm version
 */
static inline uint8_t
ext4_dir_dx_rinfo_get_hash_version(struct ext4_dir_idx_rinfo *ri)
{
	return ri->hash_version;
}

/**@brief Set hash version, that will be used in directory index.
 * @param root_info Pointer to root info structure of index
 * @param v Hash algorithm version
 */
static inline void
ext4_dir_dx_rinfo_set_hash_version(struct ext4_dir_idx_rinfo *ri, uint8_t v)
{
	ri->hash_version = v;
}

/**@brief Get length of root_info structure in bytes.
 * @param root_info Pointer to root info structure of index
 * @return Length of the structure
 */
static inline uint8_t
ext4_dir_dx_rinfo_get_info_length(struct ext4_dir_idx_rinfo *ri)
{
	return ri->info_length;
}

/**@brief Set length of root_info structure in bytes.
 * @param root_info   Pointer to root info structure of index
 * @param info_length Length of the structure
 */
static inline void
ext4_dir_dx_root_info_set_info_length(struct ext4_dir_idx_rinfo *ri,
				      uint8_t len)
{
	ri->info_length = len;
}

/**@brief Get number of indirect levels of HTree.
 * @param root_info Pointer to root info structure of index
 * @return Height of HTree (actually only 0 or 1)
 */
static inline uint8_t
ext4_dir_dx_rinfo_get_indirect_levels(struct ext4_dir_idx_rinfo *ri)
{
	return ri->indirect_levels;
}

/**@brief Set number of indirect levels of HTree.
 * @param root_info Pointer to root info structure of index
 * @param lvl Height of HTree (actually only 0 or 1)
 */
static inline void
ext4_dir_dx_rinfo_set_indirect_levels(struct ext4_dir_idx_rinfo *ri, uint8_t l)
{
	ri->indirect_levels = l;
}

/**@brief Get maximum number of index node entries.
 * @param climit Pointer to counlimit structure
 * @return Maximum of entries in node
 */
static inline uint16_t
ext4_dir_dx_climit_get_limit(struct ext4_dir_idx_climit *climit)
{
	return to_le16(climit->limit);
}

/**@brief Set maximum number of index node entries.
 * @param climit Pointer to counlimit structure
 * @param limit Maximum of entries in node
 */
static inline void
ext4_dir_dx_climit_set_limit(struct ext4_dir_idx_climit *climit, uint16_t limit)
{
	climit->limit = to_le16(limit);
}

/**@brief Get current number of index node entries.
 * @param climit Pointer to counlimit structure
 * @return Number of entries in node
 */
static inline uint16_t
ext4_dir_dx_climit_get_count(struct ext4_dir_idx_climit *climit)
{
	return to_le16(climit->count);
}

/**@brief Set current number of index node entries.
 * @param climit Pointer to counlimit structure
 * @param count Number of entries in node
 */
static inline void
ext4_dir_dx_climit_set_count(struct ext4_dir_idx_climit *climit, uint16_t count)
{
	climit->count = to_le16(count);
}

/**@brief Get hash value of index entry.
 * @param entry Pointer to index entry
 * @return Hash value
 */
static inline uint32_t
ext4_dir_dx_entry_get_hash(struct ext4_dir_idx_entry *entry)
{
	return to_le32(entry->hash);
}

/**@brief Set hash value of index entry.
 * @param entry Pointer to index entry
 * @param hash  Hash value
 */
static inline void
ext4_dir_dx_entry_set_hash(struct ext4_dir_idx_entry *entry, uint32_t hash)
{
	entry->hash = to_le32(hash);
}

/**@brief Get block address where child node is located.
 * @param entry Pointer to index entry
 * @return Block address of child node
 */
static inline uint32_t
ext4_dir_dx_entry_get_block(struct ext4_dir_idx_entry *entry)
{
	return to_le32(entry->block);
}

/**@brief Set block address where child node is located.
 * @param entry Pointer to index entry
 * @param block Block address of child node
 */
static inline void
ext4_dir_dx_entry_set_block(struct ext4_dir_idx_entry *entry, uint32_t block)
{
	entry->block = to_le32(block);
}

/**@brief Sort entry item.*/
struct ext4_dx_sort_entry {
	uint32_t hash;
	uint32_t rec_len;
	void *dentry;
};

static int ext4_dir_dx_hash_string(struct ext4_hash_info *hinfo, int len,
				   const char *name)
{
	return ext2_htree_hash(name, len, hinfo->seed, hinfo->hash_version,
			       &hinfo->hash, &hinfo->minor_hash);
}

#if CONFIG_META_CSUM_ENABLE
static uint32_t ext4_dir_dx_checksum(struct ext4_inode_ref *inode_ref, void *de,
				     int count_offset, int count,
				     struct ext4_dir_idx_tail *t)
{
	uint32_t orig_cum, csum = 0;
	struct ext4_sblock *sb = &inode_ref->fs->sb;
	int sz;

	/* Compute the checksum only if the filesystem supports it */
	if (ext4_sb_feature_ro_com(sb, EXT4_FRO_COM_METADATA_CSUM)) {
		uint32_t ino_index = to_le32(inode_ref->index);
		uint32_t ino_gen;
		ino_gen = to_le32(ext4_inode_get_generation(inode_ref->inode));

		sz = count_offset + (count * sizeof(struct ext4_dir_idx_tail));
		orig_cum = t->checksum;
		t->checksum = 0;
		/* First calculate crc32 checksum against fs uuid */
		csum = ext4_crc32c(EXT4_CRC32_INIT, sb->uuid, sizeof(sb->uuid));
		/* Then calculate crc32 checksum against inode number
		 * and inode generation */
		csum = ext4_crc32c(csum, &ino_index, sizeof(ino_index));
		csum = ext4_crc32c(csum, &ino_gen, sizeof(ino_gen));
		/* After that calculate crc32 checksum against all the dx_entry */
		csum = ext4_crc32c(csum, de, sz);
		/* Finally calculate crc32 checksum for dx_tail */
		csum = ext4_crc32c(csum, t, sizeof(struct ext4_dir_idx_tail));
		t->checksum = orig_cum;
	}
	return csum;
}

static struct ext4_dir_idx_climit *
ext4_dir_dx_get_climit(struct ext4_inode_ref *inode_ref,
			   struct ext4_dir_en *dirent, int *offset)
{
	struct ext4_dir_en *dp;
	struct ext4_dir_idx_root *root;
	struct ext4_sblock *sb = &inode_ref->fs->sb;
	uint32_t block_size = ext4_sb_get_block_size(sb);
	uint16_t entry_len = ext4_dir_en_get_entry_len(dirent);
	int count_offset;


	if (entry_len == 12) {
		root = (struct ext4_dir_idx_root *)dirent;
		dp = (struct ext4_dir_en *)&root->dots[1];
		if (ext4_dir_en_get_entry_len(dp) != (block_size - 12))
			return NULL;
		if (root->info.reserved_zero)
			return NULL;
		if (root->info.info_length != sizeof(struct ext4_dir_idx_rinfo))
			return NULL;
		count_offset = 32;
	} else if (entry_len == block_size) {
		count_offset = 8;
	} else {
		return NULL;
	}

	if (offset)
		*offset = count_offset;
	return (struct ext4_dir_idx_climit *)(((char *)dirent) + count_offset);
}

/*
 * BIG FAT NOTES:
 *       Currently we do not verify the checksum of HTree node.
 */
static bool ext4_dir_dx_csum_verify(struct ext4_inode_ref *inode_ref,
				    struct ext4_dir_en *de)
{
	struct ext4_sblock *sb = &inode_ref->fs->sb;
	uint32_t block_size = ext4_sb_get_block_size(sb);
	int coff, limit, cnt;

	if (ext4_sb_feature_ro_com(sb, EXT4_FRO_COM_METADATA_CSUM)) {
		struct ext4_dir_idx_climit *climit;
		climit = ext4_dir_dx_get_climit(inode_ref, de, &coff);
		if (!climit) {
			/* Directory seems corrupted. */
			return true;
		}
		struct ext4_dir_idx_tail *t;
		limit = ext4_dir_dx_climit_get_limit(climit);
		cnt = ext4_dir_dx_climit_get_count(climit);
		if (coff + (limit * sizeof(struct ext4_dir_idx_entry)) >
		    (block_size - sizeof(struct ext4_dir_idx_tail))) {
			/* There is no space to hold the checksum */
			return true;
		}
		t = (void *)(((struct ext4_dir_idx_entry *)climit) + limit);

		uint32_t c;
		c = to_le32(ext4_dir_dx_checksum(inode_ref, de, coff, cnt, t));
		if (t->checksum != c)
			return false;
	}
	return true;
}


static void ext4_dir_set_dx_csum(struct ext4_inode_ref *inode_ref,
				 struct ext4_dir_en *dirent)
{
	int coff, limit, count;
	struct ext4_sblock *sb = &inode_ref->fs->sb;
	uint32_t block_size = ext4_sb_get_block_size(sb);

	if (ext4_sb_feature_ro_com(sb, EXT4_FRO_COM_METADATA_CSUM)) {
		struct ext4_dir_idx_climit *climit;
		climit = ext4_dir_dx_get_climit(inode_ref, dirent, &coff);
		if (!climit) {
			/* Directory seems corrupted. */
			return;
		}
		struct ext4_dir_idx_tail *t;
		limit = ext4_dir_dx_climit_get_limit(climit);
		count = ext4_dir_dx_climit_get_count(climit);
		if (coff + (limit * sizeof(struct ext4_dir_idx_entry)) >
		   (block_size - sizeof(struct ext4_dir_idx_tail))) {
			/* There is no space to hold the checksum */
			return;
		}

		t = (void *)(((struct ext4_dir_idx_entry *)climit) + limit);
		t->checksum = to_le32(ext4_dir_dx_checksum(inode_ref, dirent,
					coff, count, t));
	}
}
#else
#define ext4_dir_dx_csum_verify(...) true
#define ext4_dir_set_dx_csum(...)
#endif

/****************************************************************************/

/**@brief Initialize hash info structure necessary for index operations.
 * @param hinfo      Pointer to hinfo to be initialized
 * @param root_block Root block (number 0) of index
 * @param sb         Pointer to superblock
 * @param name_len   Length of name to be computed hash value from
 * @param name       Name to be computed hash value from
 * @return Standard error code
 */
static int ext4_dir_hinfo_init(struct ext4_hash_info *hinfo,
			       struct ext4_block *root_block,
			       struct ext4_sblock *sb, size_t name_len,
			       const char *name)
{
	struct ext4_dir_idx_root *root;

	root = (struct ext4_dir_idx_root *)root_block->data;
	if ((root->info.hash_version != EXT2_HTREE_LEGACY) &&
	    (root->info.hash_version != EXT2_HTREE_HALF_MD4) &&
	    (root->info.hash_version != EXT2_HTREE_TEA))
		return EXT4_ERR_BAD_DX_DIR;

	/* Check unused flags */
	if (root->info.unused_flags != 0)
		return EXT4_ERR_BAD_DX_DIR;

	/* Check indirect levels */
	if (root->info.indirect_levels > 1)
		return EXT4_ERR_BAD_DX_DIR;

	/* Check if node limit is correct */
	uint32_t block_size = ext4_sb_get_block_size(sb);
	uint32_t entry_space = block_size;
	entry_space -= 2 * sizeof(struct ext4_dir_idx_dot_en);
	entry_space -= sizeof(struct ext4_dir_idx_rinfo);
	if (ext4_sb_feature_ro_com(sb, EXT4_FRO_COM_METADATA_CSUM))
		entry_space -= sizeof(struct ext4_dir_idx_tail);
	entry_space = entry_space / sizeof(struct ext4_dir_idx_entry);

	struct ext4_dir_idx_climit *climit = (void *)&root->en;
	uint16_t limit = ext4_dir_dx_climit_get_limit(climit);
	if (limit != entry_space)
		return EXT4_ERR_BAD_DX_DIR;

	/* Check hash version and modify if necessary */
	hinfo->hash_version = ext4_dir_dx_rinfo_get_hash_version(&root->info);
	if ((hinfo->hash_version <= EXT2_HTREE_TEA) &&
	    (ext4_sb_check_flag(sb, EXT4_SUPERBLOCK_FLAGS_UNSIGNED_HASH))) {
		/* Use unsigned hash */
		hinfo->hash_version += 3;
	}

	/* Load hash seed from superblock */
	hinfo->seed = ext4_get8(sb, hash_seed);

	/* Compute hash value of name */
	if (name)
		return ext4_dir_dx_hash_string(hinfo, name_len, name);

	return EOK;
}

/**@brief Walk through index tree and load leaf with corresponding hash value.
 * @param hinfo      Initialized hash info structure
 * @param inode_ref  Current i-node
 * @param root_block Root block (iblock 0), where is root node located
 * @param dx_block   Pointer to leaf node in dx_blocks array
 * @param dx_blocks  Array with the whole path from root to leaf
 * @return Standard error code
 */
static int ext4_dir_dx_get_leaf(struct ext4_hash_info *hinfo,
				struct ext4_inode_ref *inode_ref,
				struct ext4_block *root_block,
				struct ext4_dir_idx_block **dx_block,
				struct ext4_dir_idx_block *dx_blocks)
{
	struct ext4_dir_idx_root *root;
	struct ext4_dir_idx_entry *entries;
	struct ext4_dir_idx_entry *p;
	struct ext4_dir_idx_entry *q;
	struct ext4_dir_idx_entry *m;
	struct ext4_dir_idx_entry *at;
	ext4_fsblk_t fblk;
	uint32_t block_size;
	uint16_t limit;
	uint16_t entry_space;
	uint8_t ind_level;
	int r;

	struct ext4_dir_idx_block *tmp_dx_blk = dx_blocks;
	struct ext4_block *tmp_blk = root_block;
	struct ext4_sblock *sb = &inode_ref->fs->sb;

	block_size = ext4_sb_get_block_size(sb);
	root = (struct ext4_dir_idx_root *)root_block->data;
	entries = (struct ext4_dir_idx_entry *)&root->en;
	limit = ext4_dir_dx_climit_get_limit((void *)entries);
	ind_level = ext4_dir_dx_rinfo_get_indirect_levels(&root->info);

	/* Walk through the index tree */
	while (true) {
		uint16_t cnt = ext4_dir_dx_climit_get_count((void *)entries);
		if ((cnt == 0) || (cnt > limit))
			return EXT4_ERR_BAD_DX_DIR;

		/* Do binary search in every node */
		p = entries + 1;
		q = entries + cnt - 1;

		while (p <= q) {
			m = p + (q - p) / 2;
			if (ext4_dir_dx_entry_get_hash(m) > hinfo->hash)
				q = m - 1;
			else
				p = m + 1;
		}

		at = p - 1;

		/* Write results */
		memcpy(&tmp_dx_blk->b, tmp_blk, sizeof(struct ext4_block));
		tmp_dx_blk->entries = entries;
		tmp_dx_blk->position = at;

		/* Is algorithm in the leaf? */
		if (ind_level == 0) {
			*dx_block = tmp_dx_blk;
			return EOK;
		}

		/* Goto child node */
		uint32_t n_blk = ext4_dir_dx_entry_get_block(at);

		ind_level--;

		r = ext4_fs_get_inode_dblk_idx(inode_ref, n_blk, &fblk, false);
		if (r != EOK)
			return r;

		r = ext4_trans_block_get(inode_ref->fs->bdev, tmp_blk, fblk);
		if (r != EOK)
			return r;

		entries = ((struct ext4_dir_idx_node *)tmp_blk->data)->entries;
		limit = ext4_dir_dx_climit_get_limit((void *)entries);

		entry_space = block_size - sizeof(struct ext4_fake_dir_entry);
		if (ext4_sb_feature_ro_com(sb, EXT4_FRO_COM_METADATA_CSUM))
			entry_space -= sizeof(struct ext4_dir_idx_tail);

		entry_space = entry_space / sizeof(struct ext4_dir_idx_entry);

		if (limit != entry_space) {
			ext4_block_set(inode_ref->fs->bdev, tmp_blk);
			return EXT4_ERR_BAD_DX_DIR;
		}

		if (!ext4_dir_dx_csum_verify(inode_ref, (void *)tmp_blk->data)) {
			ext4_dbg(DEBUG_DIR_IDX,
					DBG_WARN "HTree checksum failed."
					"Inode: %" PRIu32", "
					"Block: %" PRIu32"\n",
					inode_ref->index,
					n_blk);
		}

		++tmp_dx_blk;
	}

	/* Unreachable */
	return EOK;
}

/**@brief Check if the the next block would be checked during entry search.
 * @param inode_ref Directory i-node
 * @param hash      Hash value to check
 * @param dx_block  Current block
 * @param dx_blocks Array with path from root to leaf node
 * @return Standard Error code
 */
static int ext4_dir_dx_next_block(struct ext4_inode_ref *inode_ref,
				  uint32_t hash,
				  struct ext4_dir_idx_block *dx_block,
				  struct ext4_dir_idx_block *dx_blocks)
{
	int r;
	uint32_t num_handles = 0;
	ext4_fsblk_t blk_adr;
	struct ext4_dir_idx_block *p = dx_block;

	/* Try to find data block with next bunch of entries */
	while (true) {
		uint16_t cnt = ext4_dir_dx_climit_get_count((void *)p->entries);

		p->position++;
		if (p->position < p->entries + cnt)
			break;

		if (p == dx_blocks)
			return EOK;

		num_handles++;
		p--;
	}

	/* Check hash collision (if not occurred - no next block cannot be
	 * used)*/
	uint32_t current_hash = ext4_dir_dx_entry_get_hash(p->position);
	if ((hash & 1) == 0) {
		if ((current_hash & ~1) != hash)
			return 0;
	}

	/* Fill new path */
	while (num_handles--) {
		uint32_t blk = ext4_dir_dx_entry_get_block(p->position);
		r = ext4_fs_get_inode_dblk_idx(inode_ref, blk, &blk_adr, false);
		if (r != EOK)
			return r;

		struct ext4_block b;
		r = ext4_trans_block_get(inode_ref->fs->bdev, &b, blk_adr);
		if (r != EOK)
			return r;

		if (!ext4_dir_dx_csum_verify(inode_ref, (void *)b.data)) {
			ext4_dbg(DEBUG_DIR_IDX,
					DBG_WARN "HTree checksum failed."
					"Inode: %" PRIu32", "
					"Block: %" PRIu32"\n",
					inode_ref->index,
					blk);
		}

		p++;

		/* Don't forget to put old block (prevent memory leak) */
		r = ext4_block_set(inode_ref->fs->bdev, &p->b);
		if (r != EOK)
			return r;

		memcpy(&p->b, &b, sizeof(b));
		p->entries = ((struct ext4_dir_idx_node *)b.data)->entries;
		p->position = p->entries;
	}

	return ENOENT;
}

int ext4_dir_dx_find_entry(struct ext4_dir_search_result *result,
			   struct ext4_inode_ref *inode_ref, size_t name_len,
			   const char *name)
{
	/* Load direct block 0 (index root) */
	ext4_fsblk_t root_block_addr;
	int rc2;
	int rc;
	rc = ext4_fs_get_inode_dblk_idx(inode_ref,  0, &root_block_addr, false);
	if (rc != EOK)
		return rc;

	struct ext4_fs *fs = inode_ref->fs;

	struct ext4_block root_block;
	rc = ext4_trans_block_get(fs->bdev, &root_block, root_block_addr);
	if (rc != EOK)
		return rc;

	if (!ext4_dir_dx_csum_verify(inode_ref, (void *)root_block.data)) {
		ext4_dbg(DEBUG_DIR_IDX,
			 DBG_WARN "HTree root checksum failed."
			 "Inode: %" PRIu32", "
			 "Block: %" PRIu32"\n",
			 inode_ref->index,
			 (uint32_t)0);
	}

	/* Initialize hash info (compute hash value) */
	struct ext4_hash_info hinfo;
	rc = ext4_dir_hinfo_init(&hinfo, &root_block, &fs->sb, name_len, name);
	if (rc != EOK) {
		ext4_block_set(fs->bdev, &root_block);
		return EXT4_ERR_BAD_DX_DIR;
	}

	/*
	 * Hardcoded number 2 means maximum height of index tree,
	 * specified in the Linux driver.
	 */
	struct ext4_dir_idx_block dx_blocks[2];
	struct ext4_dir_idx_block *dx_block;
	struct ext4_dir_idx_block *tmp;

	rc = ext4_dir_dx_get_leaf(&hinfo, inode_ref, &root_block, &dx_block,
				  dx_blocks);
	if (rc != EOK) {
		ext4_block_set(fs->bdev, &root_block);
		return EXT4_ERR_BAD_DX_DIR;
	}

	do {
		/* Load leaf block */
		uint32_t leaf_blk_idx;
		ext4_fsblk_t leaf_block_addr;
		struct ext4_block b;

		leaf_blk_idx = ext4_dir_dx_entry_get_block(dx_block->position);
		rc = ext4_fs_get_inode_dblk_idx(inode_ref, leaf_blk_idx,
						&leaf_block_addr, false);
		if (rc != EOK)
			goto cleanup;

		rc = ext4_trans_block_get(fs->bdev, &b, leaf_block_addr);
		if (rc != EOK)
			goto cleanup;

		if (!ext4_dir_csum_verify(inode_ref, (void *)b.data)) {
			ext4_dbg(DEBUG_DIR_IDX,
				 DBG_WARN "HTree leaf block checksum failed."
				 "Inode: %" PRIu32", "
				 "Block: %" PRIu32"\n",
				 inode_ref->index,
				 leaf_blk_idx);
		}

		/* Linear search inside block */
		struct ext4_dir_en *de;
		rc = ext4_dir_find_in_block(&b, &fs->sb, name_len, name, &de);

		/* Found => return it */
		if (rc == EOK) {
			result->block = b;
			result->dentry = de;
			goto cleanup;
		}

		/* Not found, leave untouched */
		rc2 = ext4_block_set(fs->bdev, &b);
		if (rc2 != EOK)
			goto cleanup;

		if (rc != ENOENT)
			goto cleanup;

		/* check if the next block could be checked */
		rc = ext4_dir_dx_next_block(inode_ref, hinfo.hash, dx_block,
					    &dx_blocks[0]);
		if (rc < 0)
			goto cleanup;
	} while (rc == ENOENT);

	/* Entry not found */
	rc = ENOENT;

cleanup:
	/* The whole path must be released (preventing memory leak) */
	tmp = dx_blocks;

	while (tmp <= dx_block) {
		rc2 = ext4_block_set(fs->bdev, &tmp->b);
		if (rc == EOK && rc2 != EOK)
			rc = rc2;
		++tmp;
	}

	return rc;
}

int ext4_dir_dx_reset_parent_inode(struct ext4_inode_ref *dir,
                                   uint32_t parent_inode)
{
	/* Load block 0, where will be index root located */
	ext4_fsblk_t fblock;
	int rc = ext4_fs_get_inode_dblk_idx(dir, 0, &fblock, false);
	if (rc != EOK)
		return rc;

	struct ext4_block block;
	rc = ext4_trans_block_get(dir->fs->bdev, &block, fblock);
	if (rc != EOK)
		return rc;

	if (!ext4_dir_dx_csum_verify(dir, (void *)block.data)) {
		ext4_dbg(DEBUG_DIR_IDX,
			 DBG_WARN "HTree root checksum failed."
			 "Inode: %" PRIu32", "
			 "Block: %" PRIu32"\n",
			 dir->index,
			 (uint32_t)0);
	}

	/* Initialize pointers to data structures */
	struct ext4_dir_idx_root *root = (void *)block.data;

	/* Fill the inode field with a new parent ino. */
	ext4_dx_dot_en_set_inode(&root->dots[1], parent_inode);

	ext4_dir_set_dx_csum(dir, (void *)block.data);
	ext4_trans_set_block_dirty(block.buf);

	return ext4_block_set(dir->fs->bdev, &block);
}

/**
 * @}
 */
