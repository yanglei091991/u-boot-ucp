
#include "ddr_test.h"

unsigned int memfill32( unsigned int dest, unsigned int len, unsigned int val )
{
    unsigned int *addr;
    unsigned int *start = (unsigned int *)dest; 
    unsigned int *end = (unsigned int*)(start + len);
    unsigned int errorcount = 0;
 
    /* Write Pattern */
    for ( addr = start; addr < end; addr++)
    {
        *addr = val;
    }
 
    /* Read Pattern */
    for ( addr = start; addr < end; addr++)
    {
        if ( *addr != val )
        {
            errorcount++;
            break;
        }
    }
 
    return errorcount;
}

int ddr_test()
{
   unsigned int ddr_base = 0x10000000;       // DDR memory
   unsigned int ddr_size = 0x00100000;       // 1 MB
//   memfill32( ddr_base, ddr_size, 0x10000000);
//   memfill32( ddr_base*2, ddr_size, 0x20000000 );
//   memfill32( ddr_base*3, ddr_size, 0x30000000 );
//   memfill32( ddr_base*4, ddr_size, 0x40000000 );



    if ( memfill32( ddr_base, ddr_size, 0xFFFFFFFF ) )
        return 1;
 
    if ( memfill32( ddr_base * 2, ddr_size, 0xFFFFFFFF ) )
        return 2;
 
    if ( memfill32( ddr_base * 3, ddr_size, 0xFFFFFFFF ) )
        return 3;
 
    if ( memfill32( ddr_base * 4, ddr_size, 0xFFFFFFFF ) )
        return 4;
    return 0;
}

//int main()
//{
//    if(ddr_test() != 0)
//        printf(" ddr write and read err");
//
//    return 0;
//}






