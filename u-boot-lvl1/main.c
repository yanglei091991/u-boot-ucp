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
//#include "common.h"
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

unsigned int config_pll(void)
{
    unsigned int count=0;
    
    // config pll clock_t
    PLL1_CONFIG0 = (2 << 12) + (2 << 15) + 80; // 400MHz
    PLL3_CONFIG0 = (3 << 12) + (1 << 15) + 75; // 500MHz
    // pll1 enable
    PLL1_CTRL |= 1;
    // PLL3 enable
    PLL3_CTRL |= 1;
    
    // add delay(50us);
    tus_delay(5);
    // wait pll1 and pll3 locked
    while((PLL_SEL_CTRL & (BIT12 | BIT14)) != (BIT12 | BIT14))
    {
      // add delay(1s);
      tus_delay(10);   /* 100us */
      count++;
      if((count>=10000)&&((PLL_SEL_CTRL & (BIT12 | BIT14)) != (BIT12 | BIT14)))
      {
         //exit(1);
         return false;
      }
    }
    
    // switch xtal to pll
    PLL_SEL_CTRL |= 0x400;
    PLL_SEL_CTRL |= 0x100;
    // clear status
    PLL_SEL_CTRL = PLL_SEL_CTRL & (~BIT16);
    // enable sdio clk to 50M
    SDIOCLK_CTRL = 1 + (9 << 13) + BIT18; // 50MHz

    return true;
}

//volatile char read_arr_index = 1;
//unsigned char (* nandflash_read_arr[])(unsigned int,unsigned int,unsigned char*,unsigned int) = {nandflash_read, nandflash_read};

int main()
{
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
#ifdef  SOC_PRJ
   config_pll();
#endif

// init interface 
#if  0
  pinmux_init();
  drv_gpio_init();

  drv_led0_on();
  drv_led0_off();  

#endif

  boot_uart_init();
#ifdef  UART
  Uart_Printf("UART init success! \n\r");
#endif  

  read_uboot_mode();
 
  return 0;
}
