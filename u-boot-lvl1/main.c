//******************** (C) COPYRIGHT 2015 HED *************************************
//* File Name          : demo_002_n.c
//* Author             : lijian
//* Date First Issued  : 2015-01-16
//* Description        : Common C functions for C98CAY1MS
// ------------------------------------------------------------
// Modification History:
// Version    Date       Author    Modification Description
// V0.01     2015-01-16  lijian
//*********************************************************************************/

#define _READ_INTERFACE

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <unistd.h>

#include "uart.h"
#include "gpio.h"
#include "common.h"
//#include "crc16_test.h"

extern char __bss_start__[], __bss_end__[];
extern void __libc_init_array(void);
extern void __libc_fini_array(void);

void copy_data_to_ram(unsigned char *src,
                      unsigned char *dest, unsigned int len)
{
  memcpy(dest,src,(size_t)len);
  /*int i = 0;*/
  /*for (; i < len; i++)*/
  /*{*/
    /**dest = *src;*/
    /*dest++;*/
    /*src++;*/
  /*}*/
}

//volatile char read_arr_index = 1;
//unsigned char (* nandflash_read_arr[])(unsigned int,unsigned int,unsigned char*,unsigned int) = {nandflash_read, nandflash_read};

int main()
{
  extern unsigned char data_load_start[];
  extern unsigned char __data_start[];
  extern unsigned int  data_size[];
//  if(__data_start != data_load_start)
//  {
//    copy_data_to_ram(data_load_start,
//                     __data_start,
//                    (unsigned int)data_size);
//  }

// init interface 
//  spi_nand_flash_init();
//  boot_uart_init();
//  drv_gpio_init();

 // add read_id() select read_interface of the manufacturers
//  volatile int read_arr_index = 0;

  unsigned int *src = (unsigned int*)nandflash_startAddr;
  unsigned char *dest = (unsigned char*)copy_addr;
  unsigned int boot_size = 0;

//  if(copy_boot2_to_ram(src,dest,&boot_size) == false)
//  {
//    return 1;  
//  }
  return 0;
}
