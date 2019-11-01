#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <unistd.h>

#define _READ_INTERFACE
#include "uart.h"
#include "gpio.h"
#include "common.h"
//#include "crc16_test.h"
#include "ddr_test.h"
#include "config_pll.h"
#include "sd_common.h"
#include "boot_read_mode.h"

extern char __bss_start__[], __bss_end__[];
extern void __libc_init_array(void);
extern void __libc_fini_array(void);

void copy_data_to_ram(unsigned char *src,
                      unsigned char *dest, unsigned int len)
{
  memcpy(dest,src,(size_t)len);
}

void config_pll()
{
    // config pll clock_t
    PLL1_CONFIG0 = (2 << 12) + (2 << 15) + 80; // 400MHz
    PLL3_CONFIG0 = (3 << 12) + (1 << 15) + 75; // 500MHz
    // pll1 enable
    PLL1_CTRL |= 1;
    // PLL3 enable
    PLL3_CTRL |= 1;
    // wait pll1 and pll3 locked
    while((PLL_SEL_CTRL & (BIT12 | BIT14)) != (BIT12 | BIT14));
    // switch xtal to pll
    PLL_SEL_CTRL |= 0x400;
    PLL_SEL_CTRL |= 0x100;
    // clear status
    PLL_SEL_CTRL = PLL_SEL_CTRL & (~BIT16);
    // enable sdio clk to 50M
    SDIOCLK_CTRL = 1 + (9 << 13) + BIT18; // 50MHz
}

//volatile char read_arr_index = 1;
//unsigned char (* nandflash_read_arr[])(unsigned int,unsigned int,unsigned char*,unsigned int) = {nandflash_read, nandflash_read};

int main()
{
//    int val = ddr_test();
//    if(val != 0)
//        return 1;
//       printf("ddr write and read err");

  // copy data segment from rom to share mem 5
  extern unsigned char data_load_start[];
  extern unsigned char __data_start[];
  extern unsigned int  data_size[];
  if(__data_start != data_load_start)
  {
    copy_data_to_ram(data_load_start,
                     __data_start,
                    (unsigned int)data_size);
  }

// config pll clock
//   config_pll();

// init interface 
#if  0
  pinmux_init();
  drv_gpio_init();

  drv_led0_on();
  drv_led0_off();  

#endif
  boot_uart_init();
  Uart_Printf("UART init success! \n\r");

  read_uboot_mode();
//  add read_id() select read_interface of the manufacturers
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
