#ifndef _COPY_IMAGE_H
#define _COPY_IMAGE_H

#include <stdio.h>
#include <stdbool.h>
#include "spi_nand_flash.h"
#include "crc16_test.h"

#define page 2048
enum{
uboot_page = 0x4,
ddr_page,
image_page,
image_dts
};
#define nandflash_startAddr  (page * uboot_page)
#define Block_Size 0x20000 // 128KB
#define head_len 0x800 // 2k
#define copy_addr 0x10800000
enum{
boot2 = 0,
ddr,
OS_Image,
device_tree
};

typedef struct{
unsigned int op_type;
unsigned int byte_size;
unsigned int crc;
unsigned int head_end;
}NandFlash_Head;

bool copy_image_dts_to_ram(unsigned int *src, unsigned char *dest);

#ifdef _READ_INTERFACE
volatile int read_arr_index = 1;
unsigned char (* nandflash_read_arr[])(unsigned int,unsigned int,unsigned char*,unsigned int) = {nandflash_read, nandflash_read};
#else
extern volatile int read_arr_index;
extern unsigned char (* nandflash_read_arr[])(unsigned int,unsigned int,unsigned char*,unsigned int);
#endif

#endif // _COPY_IMAGE_H
