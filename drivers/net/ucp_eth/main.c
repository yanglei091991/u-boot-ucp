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
extern unsigned char designware_i2c_test(void);
extern unsigned char designware_i2c_test1(void);
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
  unsigned char  i;
  unsigned char  ret;
//  if(__data_start != data_load_start)
//  {
//    copy_data_to_ram(data_load_start,
//                     __data_start,
//                    (unsigned int)data_size);
//  }

// init interface 
  drv_gpio_init();
  spi_nand_flash_init();
  boot_uart_init();


  //test
//  ret = designware_i2c_test();
//  designware_i2c_test1();
  gmac_test();
  boot_gpio_set_value(GPIO_LED0_PIN, 1);
  for(i=0;i<100;i++)
    Uart_Printf("UART init success,UART init success\n\r");
  
 // add read_id() select read_interface of the manufacturers
//  volatile int read_arr_index = 0;

  unsigned int *src = (unsigned int*)nandflash_startAddr;
  unsigned char *dest = (unsigned char*)0x60000000;
  unsigned int len = 0x100000;
  unsigned int boot_size = 0;

  if(copy_boot2_to_ram(src,dest,&boot_size) == false)
  {
    return 1;  
  }
  return 0;
/*
  unsigned short src_file_crc = crc16((unsigned char*)src, len);
  unsigned short dest_file_crc = crc16(dest, len);
  if(src_file_crc != dest_file_crc)
    return 1;
  else
    return 0;
*/
}
