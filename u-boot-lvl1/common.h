#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include "spi_nand_flash.h"
#include "crc16_test.h"
#include "uart.h"

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
#define copy_addr 0x04e60000
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


bool copy_boot2_to_ram(unsigned int *src, unsigned char *dest, unsigned int *boot_ize);

#ifdef _READ_INTERFACE
volatile char read_arr_index = 1;
unsigned char (* nandflash_read_arr[])(unsigned int,unsigned int,unsigned char*,unsigned int) = {nandflash_read, nandflash_read};
#else
extern volatile char read_arr_index;
extern unsigned char (* nandflash_read_arr[])(unsigned int,unsigned int,unsigned char*,unsigned int);
#endif

#endif // _COMMMON_H
