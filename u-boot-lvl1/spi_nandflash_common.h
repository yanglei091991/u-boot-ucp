#ifndef SPI_NANDFLASH_COMMON_H
#define SPI_NANDFLASH_COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include "spi_nand_flash.h"
#include "crc32.h"
#include "uart.h"

enum{
uboot_page = 0x4,
image_page,
image_dts
};

enum{
boot2 = 0,
OS_Image,
device_tree
};

#define page 2048
#define nandflash_startAddr  (page * uboot_page) // nandflash store uboot.bin addr
#define Block_Size 0x20000 // 128KB
#define head_len 0x800 // 2k
#define copy_addr 0x04e60000    // uboot store addr on SM0-3

typedef struct{
unsigned int op_type;
unsigned int byte_size;
unsigned int crc;
unsigned int head_end;
}NandFlash_Head;


bool copy_boot2_to_ram(unsigned int *src, unsigned char *dest, unsigned int *boot_ize);

// define function point arr support mang manufacturer spi nand flash driver
extern int read_arr_index;
extern unsigned char (* nandflash_read_arr[])(unsigned int,unsigned int,unsigned char*,unsigned int);

#endif // SPI_NANDFLASH_COMMON_H
