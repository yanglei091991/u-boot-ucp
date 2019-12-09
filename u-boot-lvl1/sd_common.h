

#ifndef SD_COMMON_H_
#define SD_COMMON_H_


#include <stdbool.h>

#define  MMC_CARD_DETECT
#define  CONFIG_MMC_QUIRKS

typedef unsigned char		uchar;
typedef volatile unsigned long	vu_long;
typedef volatile unsigned short vu_short;
typedef volatile unsigned char	vu_char;

typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed long long s64;
typedef unsigned long  long u64;

typedef unsigned short ushort;
typedef unsigned int   uint;
//typedef unsigned int  ulong;
typedef unsigned long  ulong;


//typedef unsigned char		bool;

//typedef unsigned int   uint32_t;


//void udelay(unsigned long usec);
ulong get_timer(ulong usec);

#define true  1
#define false 0
//#define  NULL   0
#define ARCH_DMA_MINALIGN		128     /* DMA∂‡…Ÿ∂‘∆Î?? */

#if  0
#define debug(format, ...) printf(format, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif /* DUMPIMAGE_DEBUG */

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define BIT(nr)			(1UL << (nr))

//typedef unsigned long int uintptr_t;
#define __ALIGN_MASK(x,mask)	(((x)+(mask))&~(mask))
#define ALIGN(x,a)		__ALIGN_MASK((x),(typeof(x))(a)-1)

/* Reused from spi_nandflash_common.h */
#define ROUND(a, b)		(((a) + (b) - 1) & ~((b) - 1))

#define PAD_COUNT(s, pad) (((s) - 1) / (pad) + 1)
#define PAD_SIZE(s, pad) (PAD_COUNT(s, pad) * pad)
#define ALLOC_ALIGN_BUFFER_PAD(type, name, size, align, pad)		\
	char __##name[ROUND(PAD_SIZE((size) * sizeof(type), pad), align)  \
		      + (align - 1)];					\
									\
	type *name = (type *)ALIGN((uintptr_t)__##name, align)
#define ALLOC_ALIGN_BUFFER(type, name, size, align)		\
	ALLOC_ALIGN_BUFFER_PAD(type, name, size, align, 1)
#define ALLOC_CACHE_ALIGN_BUFFER_PAD(type, name, size, pad)		\
	ALLOC_ALIGN_BUFFER_PAD(type, name, size, ARCH_DMA_MINALIGN, pad)
#define ALLOC_CACHE_ALIGN_BUFFER(type, name, size)			\
	ALLOC_ALIGN_BUFFER(type, name, size, ARCH_DMA_MINALIGN)

#define DIV_ROUND_UP(n,d)	(((n) + (d) - 1) / (d))

#define ARRAY_SIZE(arr)		(sizeof(arr) / sizeof((arr)[0]))


struct dw_timer {
	u32 timer0load;		/* 0x00 */
	u32 timer0value;
	u32 timer0control;
	u32 timer0EOI;
	u32 timer0IntStatus;
};


void timer_init(void);
int sd_init(void);
int  sd_fs_read(void); // sd driver file system read
void us_delay(unsigned int usec);
void tus_delay(unsigned int tusec);
#endif //SD_COMMON_H_

