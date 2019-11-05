#include "boot_read_mode.h"
#include "sd_common.h"
#include "uart.h"
#include "common.h"
#include "pinmux.h"

void  print_boot_cfg(void)
{
    unsigned  int  boot_cfg;

    boot_cfg = A53_M3_REMAP;
    if(boot_cfg&BOOT_CFG_SYNC)
      {
        Uart_Printf("BOOT1 GPMC! \n\r");
        if(boot_cfg&BOOT_CTL_SYNC5)
           Uart_Printf("--from nor flash! \n\r");
      }
    else
      Uart_Printf("BOOT1 ROM! \n\r");
       
}


/* internal ROM BOOT */
unsigned char  read_uboot_mode(void)
{
    unsigned int  boot_cfg;
    unsigned int *src = (unsigned int*)nandflash_startAddr;
    unsigned char *dest = (unsigned char*)copy_addr;
    unsigned int boot_size = 0;

    print_boot_cfg();
    boot_cfg = A53_M3_REMAP;    
    if(boot_cfg&BOOT_CTL_SYNC4)
    { /* uboot from SPI0 flash */
    
      /* spi0复用, 测试代码注掉, 正式代码打开 */
      //spi0_pin_init();      
      
      Uart_Printf("BOOT2 SPI nand! \n\r");
      
      /* init spi, read uboot from spi flash */
      /* 正式代码用SPI0, 测试代码用SPI2 */
      spi_nand_flash_init();
      
      /* check boot success or not */
	  if(copy_boot2_to_ram(src,dest,&boot_size) == false)
      {
        return false;  
      }
    }
    else
    { /* uboot from SDIO */
       Uart_Printf("BOOT2 SD card! \n\r");
      /* init sdio, read uboot from sd card */     
       sd_fs_read();

      /* check boot success or not */
      
    }
    return true;   
}









