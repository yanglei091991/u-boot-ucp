#include "boot_read_mode.h"
#include "sd_common.h"
#include "uart.h"

void  print_hex(unsigned char hex);

void  output_boot_cfg(void)
{
    unsigned  int  boot_cfg;
    unsigned  char cboot_cfg;
    
    boot_cfg  = A53_M3_REMAP&(BOOT_CFG_SYNC|BOOT_CTL_SYNC4|BOOT_CTL_SYNC5);
    cboot_cfg = (unsigned char)boot_cfg;
    Uart_Printf("BOOT_CFG=0x");
    print_hex(cboot_cfg);
    
}


/* internal ROM BOOT */
void  read_uboot_mode(void)
{
    unsigned  int  boot_cfg;
    
    output_boot_cfg();
    boot_cfg = A53_M3_REMAP;
    if(boot_cfg&BOOT_CTL_SYNC4)
    { /* uboot from SPI0 flash */

      /* init spi, read uboot from spi flash */

      /* check boot success or not */
	  sd_fs_read();
    }
    else
    { /* uboot from SDIO */
      /* init sdio, read uboot from sd card */     
       sd_fs_read();

      /* check boot success or not */
      
    }
          
}









