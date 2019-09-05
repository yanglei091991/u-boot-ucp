#include "copy_image.h"

bool copy_image_dts_to_ram(unsigned int *src, unsigned char *dest)
{
  unsigned int rowAddr = ((unsigned int)src&0x1FFFF800)>>11;
  unsigned int colAddr = (unsigned int)src&0x7FF;
//  unsigned char *SM5_Addr = (unsigned char*)0x020ceff0; // SM5 Addr store nandflash head info
  unsigned char SM5_Addr[16] = {0}; 
//  unsigned int len = 0x800; // 2k
  nandflash_read_arr[read_arr_index](rowAddr, colAddr, SM5_Addr, head_len);

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

  unsigned char *tmp_dest = dest;
  unsigned int srcAddr;
  for(int i = 0; i < nand_head.byte_size/Block_Size; i++)
  {
    srcAddr = (unsigned int)(*(pNandHead + i));
    rowAddr = (unsigned int)srcAddr << 6;
    colAddr = 0x0;
    nandflash_read_arr[read_arr_index](rowAddr, colAddr, tmp_dest, Block_Size);
    tmp_dest = tmp_dest + Block_Size;
  }

  if((nand_head.byte_size%Block_Size) != 0)
  {    
    srcAddr = (unsigned int)(*(pNandHead + nand_head.byte_size/Block_Size));
    rowAddr = (unsigned int)srcAddr << 6;
    colAddr = 0x0;
    nandflash_read_arr[read_arr_index](rowAddr, colAddr, tmp_dest, nand_head.byte_size%Block_Size);
  }

  unsigned int dest_file_crc = CRC32((char*)dest, nand_head.byte_size);
  if(nand_head.crc != dest_file_crc)
    return false;
  
  return true;
}
