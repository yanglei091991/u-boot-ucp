#include "boot_read_mode.h"
#include "sd_common.h"
#include "spi_nandflash_common.h"
#include "pinmux.h"

#ifdef  UART
#include "uart.h"
#endif

void  print_boot_cfg(void)
{
    unsigned  int  boot_cfg;

    boot_cfg = A53_M3_REMAP;
    if(boot_cfg&BOOT_CFG_SYNC)
      {
#ifdef  UART
        Uart_Printf("BOOT1 GPMC! \n\r");
#endif
        if(boot_cfg&BOOT_CTL_SYNC5)
        {
#ifdef  UART
            Uart_Printf("--from nor flash! \n\r");
#endif 
        }
      }
    else
    {
#ifdef  UART
        Uart_Printf("BOOT1 ROM! \n\r");
#endif   
    }  
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
    
#ifdef  SOC_PRJ 
      /* SOC use spio0, spi0 must be pinmux init;fpga test use fpga SPI2 */
      spi0_pin_init();
#endif      
      
#ifdef  UART   
      Uart_Printf("BOOT2 SPI nand! \n\r");
#endif    

      /* init spi, read uboot from spi flash */
      spi_nand_flash_init();
      
      /* check boot success or not */
	  if(copy_boot2_to_ram(src,dest,&boot_size) == false)
      {
#ifdef  UART   
          Uart_Printf("BOOT1 copy boot2 from SPI flash Failed! \n\r");
#endif        
        return false;  
      }

#ifdef  UART   
          Uart_Printf("BOOT1 copy boot2 from SPI flash ok! \n\r");
#endif 	  
    }
    else
    { /* uboot from SDIO */
#ifdef  UART
        Uart_Printf("BOOT2 SD card! \n\r");
#endif
        /* init sdio, read uboot from sd card */     
       if(sd_fs_read() == false)
       {
       
#ifdef  UART   
          Uart_Printf("BOOT1 copy boot2 from SD Failed! \n\r");
#endif        
        return false;  
       }

#ifdef  UART   
          Uart_Printf("BOOT1 copy boot2 from SD ok! \n\r");
#endif 	  
      
    }
    return true;   
}


