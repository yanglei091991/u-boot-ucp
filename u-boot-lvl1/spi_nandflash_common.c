#include "spi_nandflash_common.h"

int read_arr_index = 0;
unsigned char (* nandflash_read_arr[])(unsigned int,unsigned int,unsigned char*,unsigned int) = {nandflash_read};

bool copy_boot2_to_ram(unsigned int *src, unsigned char *dest)
{
  unsigned int rowAddr = ((unsigned int)src&0x1FFFF800)>>11;
  unsigned int colAddr = (unsigned int)src&0x7FF;
//  unsigned char *SM5_Addr = (unsigned char*)0x020ceff0; // SM5 Addr store nandflash head info
  unsigned char SM5_Addr[32] = {0}; 
//  unsigned int len = 0x800; // 2k
  if(nandflash_read_arr[read_arr_index](rowAddr, colAddr, SM5_Addr, sizeof(SM5_Addr)) != 0)
  {
#ifdef UART
      Uart_Printf("spi read head nand error! \n\r");
#endif 
      return false;
  }

  NandFlash_Head nand_head;
  volatile unsigned short int *pNandHead = (volatile unsigned short int*)SM5_Addr;
  nand_head.op_type = (*pNandHead)|(*(pNandHead + 1))<<16;
  pNandHead = pNandHead + 2;
  nand_head.byte_size = (*pNandHead)|(*(pNandHead + 1))<<16;
  pNandHead = pNandHead + 2;
  nand_head.crc = (*pNandHead)|(*(pNandHead + 1))<<16;
  pNandHead = pNandHead + 2;
  nand_head.head_end = (*pNandHead)|(*(pNandHead + 1))<<16;
  pNandHead = pNandHead + 2;

  if(nand_head.op_type != boot2)
  {
    return false;
  }

  if(nand_head.byte_size >= 0x100000)
  {
#ifdef  UART
        Uart_Printf("u-boot.bin file more than 1M! \n\r");
#endif
        return false;
  }

  unsigned char *tmp_dest = dest;
  unsigned int srcAddr;
  int i;
  for(i = 0; i < nand_head.byte_size/Block_Size; i++)
  {
    srcAddr = (unsigned int)(*(pNandHead + i));
    rowAddr = (unsigned int)srcAddr << 6;
    colAddr = 0x0;
    if(nandflash_read_arr[read_arr_index](rowAddr, colAddr, tmp_dest, Block_Size) != 0)
    {
#ifdef UART
        Uart_Printf("spi read block nand error! \n\r");
#endif
        return false;
    }
    tmp_dest = tmp_dest + Block_Size;
  }

  if((nand_head.byte_size%Block_Size) != 0)
  {    
    srcAddr = (unsigned int)(*(pNandHead + nand_head.byte_size/Block_Size));
    rowAddr = (unsigned int)srcAddr << 6;
    colAddr = 0x0;
    if(nandflash_read_arr[read_arr_index](rowAddr, colAddr, tmp_dest, nand_head.byte_size%Block_Size) != 0)
    {
#ifdef UART    
        Uart_Printf("spi read remainder block nand error! \n\r");
#endif
        return false;
    }
  }

  unsigned int dest_file_crc = crc32(dest, nand_head.byte_size);
  if(nand_head.crc != dest_file_crc)
    return false;
  
  return true;
}
