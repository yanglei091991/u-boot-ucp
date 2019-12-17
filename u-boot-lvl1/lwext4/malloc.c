#include <string.h>
#include <stdio.h>
#include <assert.h>

#define HEAPSIZE (16 * 1024)
static char memory[HEAPSIZE];
static size_t ptr = 0;
static char *lastalloc;

void *ext4_user_malloc(size_t sz)
{
	size_t bufsz = ((sz + 3) / 4) * 4;
	void *res = memory + ptr;
	lastalloc = res;
	ptr += bufsz;
#ifdef BOOT1_PRINTF
	assert (ptr < HEAPSIZE);
	fprintf(stderr, "malloc %ld @ %p\n", sz, res);
#endif
	return res;
}

void *ext4_user_calloc(size_t nmemb, size_t size)
{
	size_t sz = nmemb * size;
	void *res = ext4_user_malloc(sz);
	memset(res, 0, sz);
	return res;
}

void ext4_user_free(void *p)
{
#ifdef BOOT1_PRINTF
	fprintf(stderr, "free @ %p\n", p);
#endif
	// if to free the last malloc'ed memory, then
	// set ptr to the previous one, otherwise just let it leak
	if (p == lastalloc) {
		ptr = lastalloc - memory;
		lastalloc = NULL;
	}
}
#ifdef BOOT1_PRINTF
void printptr(void)
{
	fprintf(stderr, "0x%08lx\n", ptr);
}
#endif
