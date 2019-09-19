#include "common.h"

bool copy_boot2_to_ram(unsigned int *src, unsigned char *dest, unsigned int *boot_size)
{
  unsigned int rowAddr = ((unsigned int)src&0x1FFFF800)>>11;
  unsigned int colAddr = (unsigned int)src&0x7FF;
  unsigned char *SM5_Addr = (unsigned char*)0xa0000; // SM5 Addr store nandflash head info
  unsigned int len = 0x800; // 2k
  int i;
  nandflash_read_arr[read_arr_index](rowAddr, colAddr, SM5_Addr, len);

  NandFlash_Head nand_head;
  volatile unsigned short int *pNandHead = (volatile unsigned short int*)SM5_Addr;
  nand_head.op_type = (*pNandHead)|(*(pNandHead + 1))<<16;
  pNandHead = pNandHead + 2;
  nand_head.byte_size = (*pNandHead)|(*(pNandHead + 1))<<16;
  *boot_size = nand_head.byte_size;
  pNandHead = pNandHead + 2;
  nand_head.crc = (*pNandHead)|(*(pNandHead + 1))<<16;
  pNandHead = pNandHead + 2;
  nand_head.head_end = (*pNandHead)|(*(pNandHead + 1))<<16;
  pNandHead = pNandHead + 2;

  if(nand_head.op_type != boot2)
  {
    return false;
  }
  unsigned char *tmp_dest = dest;
  unsigned int srcAddr;
  for(i = 0; i < nand_head.byte_size/Block_Size; i++)
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

  unsigned int dest_file_crc = crc32(dest, nand_head.byte_size);
  if(nand_head.crc != dest_file_crc)
    return false;
  
  return true;
}
/*
void clear_bss(void)
{
	extern int __bss_start__, __bss_end__;
	int *p = &__bss_start__;
	
	for (; p < &__bss_end__; p++)
		*p = 0;
}
*/
/*void init_ram(unsigned char *start, unsigned char *end)*/
/*{*/
	/*unsigned char *p = start;*/
	
	/*for (; p < end; p++)*/
		/**p = 0;*/
/*}*/

/*void copy_data_to_ram(unsigned char *src, unsigned char *dest, unsigned int len)*/
/*{*/
  /*int i = 0;*/
  /*for (; i < len; i++)*/
  /*{*/
    /**dest = *src;*/
  /*}*/
/*}*/
