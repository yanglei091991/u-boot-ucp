#include <stdint.h>
#include <string.h>
#include "gpio.h"
#include "config_pll.h"
#include "sd_common.h"
#include "boot_read_mode.h"
#include "pinmux.h"

#ifdef  UART
#include "uart.h"
#endif

#ifdef SOC_CLK_CFG
   /* soc config clk */
   unsigned int gSysClk = 100000000;     /* 100MHz */
   unsigned int gUART0_BAUDRATE = 115200;
   unsigned int gSpiClk = 1000000;       /* 1MHz */
   unsigned int gSdioClk = 10000000;     /* 10MHz */
#else
#if SYS_CLK_50M 
   unsigned int gSysClk = 50000000;      /* 50MHz */
   unsigned int gUART0_BAUDRATE =115200;
   unsigned int gSpiClk = 250000;
   unsigned int gSdioClk = 10000000;     /* 10MHz, actually 50/6=8.33M */
#else
   unsigned int gSysClk = 10000000;     /* 10MHz */
   unsigned int gUART0_BAUDRATE =19200;
   unsigned int gSpiClk = 100000;
   unsigned int gSdioClk = 2500000;    /* 2.5MHz */
#endif
#endif

void copy_data_to_ram(unsigned char *src,
                      unsigned char *dest, unsigned int len)
{
  memcpy(dest,src,(size_t)len);
}

/* used XTAL(20MHz/2=10MHz) as A53/UART/SPI/SDIO/timer clcok */
void  xtal_clk_cfg(void)
{
    APHCLK_CTRL     = (1 << 13)+1;
    CPHCLK_CTRL     = (1 << 13)+1;
    APSUB0PCLK_CTRL = (1 << 13)+1;
    APSUB1PCLK_CTRL = (1 << 13)+1;
    APSUB2PCLK_CTRL = (1 << 13)+1;
    CPAHBCLK_CTRL   = (1 << 13)+1;
    CPAPBCLK_CTRL   = (1 << 13)+1;
    TIMER00CLK_CTRL = (1 << 13)+1;
    TIMER01CLK_CTRL = (1 << 13)+1;
    TIMER02CLK_CTRL = (1 << 13)+1;
    TIMER03CLK_CTRL = (1 << 13)+1;
    UART0CLK_CTRL   = (1 << 13)+1;
    UART1CLK_CTRL   = (1 << 13)+1;
    UART2CLK_CTRL   = (1 << 13)+1;
    UART3CLK_CTRL   = (1 << 13)+1;
    SSI0CLK_CTRL    = (1 << 13)+1;
    SSI1CLK_CTRL    = (1 << 13)+1;
    SSI2CLK_CTRL    = (1 << 13)+1;
    SSI3CLK_CTRL    = (1 << 13)+1;
 
    SDIOCLK_CTRL = 1 + (1 << 13); /* 10MHz */
    gSysClk =10000000;       /* 10MHz */
	gUART0_BAUDRATE =19200;
	gSpiClk = 100000;        /* 100K */
	gSdioClk = 2500000;
	
    /* PLL1/PLL3 used xtal clock */
    //PLL_SEL_CTRL &= (~0x500);
}

unsigned int config_pll(void)
{
    unsigned int count=0;
    
    // config pll clock_t
    PLL1_CONFIG0 = (3 << 12) + (1 << 15) + 120;  /* 800MHz */
    PLL3_CONFIG0 = (3 << 12) + (1 << 15) + 150;  /* 1000MHz */
    // pll1 enable,bus
    PLL1_CTRL |= 1;
    // PLL3 enable, A53
    PLL3_CTRL |= 1;
    
    // add delay(50us);
    bpll_tus_delay(5);
    // wait pll1 and pll3 locked
    while((PLL_SEL_CTRL & (BIT12 | BIT14)) != (BIT12 | BIT14))
    {
      // add delay(1s);
      bpll_tus_delay(10);   /* 100us */
      count++;
      if((count>=10000)&&((PLL_SEL_CTRL & (BIT12 | BIT14)) != (BIT12 | BIT14)))
      {
         return false;
      }
    }
    
    // switch xtal to pll
    PLL_SEL_CTRL |= 0x400;
    PLL_SEL_CTRL |= 0x100;
    // clear status
    PLL_SEL_CTRL = PLL_SEL_CTRL & (~BIT16);
    // enable sdio clk to 100M
    SDIOCLK_CTRL = 1 + (9 << 13) + BIT18; /* 100MHz */

    return true;
}

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
#ifdef  SOC_PLL_CFG
   if(config_pll()==false)
      xtal_clk_cfg();
#endif

#ifdef  UART
  boot_uart_init();
#endif  

  if(read_uboot_mode() == false) return 1;
 
  return 0;
}
