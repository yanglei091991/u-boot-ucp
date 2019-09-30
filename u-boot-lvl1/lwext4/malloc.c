#include <string.h>
#include <stdio.h>
#include <assert.h>

#define HEAPSIZE (1 << 20)
static char memory[HEAPSIZE];
static size_t ptr = 0;

void *ext4_user_malloc(size_t sz)
{
	size_t bufsz = ((sz + 3) / 4) * 4;
	void *res = memory + ptr;
	ptr += bufsz;
	assert (ptr < HEAPSIZE);
	fprintf(stderr, "malloc %ld\n @ %p\n", sz, res);
	return res;
}

void *ext4_user_calloc(size_t nmemb, size_t size)
{
	size_t sz = nmemb * size;
	void *res = ext4_user_malloc(sz);
	memset(res, 0, sz);
	return res;
}

void ext4_user_free(void *ptr)
{
	fprintf(stderr, "free @ %p\n", ptr);
}

void printptr(void)
{
	fprintf(stderr, "0x%08lx\n", ptr);
}
