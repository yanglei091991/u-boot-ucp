#include "boot_read_mode.h"
#include "sd_common.h"
#include "spi_nandflash_common.h"
#include "pinmux.h"


#include "uart.h"

unsigned int gPrtFlg=0;      /* UART print flag, off=0, on=1 */

#ifdef  UART
void  print_boot_cfg(void)
{
    unsigned  int  boot_cfg;

    boot_cfg = A53_M3_REMAP;
    if(boot_cfg&BOOT_CFG_SYNC)
      {
        Uart_Printf("BOOT1 from external GPMC! \n\r");
        if(boot_cfg&BOOT_CTL_SYNC5)
        {
            Uart_Printf("--from nor flash! \n\r");
        }
        else
        {
            Uart_Printf("--from SRAM! \n\r");
        }
      }
    else
    {
        Uart_Printf("BOOT1 from On-Chip ROM! \n\r");  
    }  
}
#endif 

/* internal ROM BOOT */
unsigned char  read_uboot_mode(void)
{
    unsigned int  boot_cfg;
    unsigned int *src = (unsigned int*)nandflash_startAddr;
    unsigned char *dest = (unsigned char*)copy_addr;
   
#ifdef  UART
    print_boot_cfg();
#endif    
    boot_cfg = A53_M3_REMAP;
    if((boot_cfg&(BOOT_CTL_SYNC5|BOOT_CFG_SYNC)) == BOOT_CTL_SYNC5)
    {
       gPrtFlg= 0x5a5a5a5a;
    }    
    
    if(boot_cfg&BOOT_CTL_SYNC4)
    { /* uboot from SPI0 nand flash */
    
      /* SOC use spio0, spi0 must be pinmux init; */
      spi0_pin_init();
      
#ifdef  UART   
      Uart_Printf("U-BOOT from SPI nand! \n\r");
#endif    

      /* init spi and read spi flash id */
      if(spi_nand_flash_init() == false)
      { 
        if(gPrtFlg)
          Uart_Printf("SPI flash id error! \n\r");       
        //return false;          
      }
      
      /* read uboot from spi flash */
	  if(copy_boot2_to_ram(src,dest) == false)
      { 
        if(gPrtFlg)
          Uart_Printf("BOOT1 copy U-BOOT from SPI flash Failed! \n\r");        
        return false;  
      } 	  

#ifdef  UART   
          Uart_Printf("BOOT1 copy U-BOOT from SPI flash ok! \n\r");
#endif 	  
    }
    else
    { /* uboot from SDIO */  
    
#ifdef  UART
        Uart_Printf("U-BOOT from SD card! \n\r");
#endif
        /* init sdio, read uboot from sd card */     
       if(sd_fs_read() == false)
       { 
        if(gPrtFlg)   
          Uart_Printf("BOOT1 copy U-BOOT from SD Failed! \n\r");       
        return false;  
       }
#ifdef  UART   
          Uart_Printf("BOOT1 copy U-BOOT from SD ok! \n\r");
#endif 	  
      
    }
    return true;   
}


