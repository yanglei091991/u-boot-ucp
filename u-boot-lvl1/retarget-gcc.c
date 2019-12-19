//-----------------------------------------------------------------------------
// The confidential and proprietary information contained in this file may
// only be used by a person authorised under and to the extent permitted
// by a subsisting licensing agreement from ARM Limited.
//
//            (C) COPYRIGHT 2010-2014 ARM Limited.
//                ALL RIGHTS RESERVED
//
// This entire notice must be reproduced on all copies of this file
// and copies of this file may only be made by a person if such person is
// permitted to do so under the terms of a subsisting license agreement
// from ARM Limited.
//
//      SVN Information
//
//      Checked In          : $Date: 2014-07-02 16:52:21 +0100 (Wed, 02 Jul 2014) $
//
//      Revision            : $Revision: 283836 $
//
//      Release Information : CORTEXA53-r0p4-00rel1
//
//------------------------------------------------------------------------------
// Description:
//   Library re-target file for C-based test code
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//extern char __bss_start__[], __bss_end__[];
extern void __libc_init_array(void);
extern void __libc_fini_array(void);

unsigned char output_char(unsigned char c)
{
    //volatile int *tube = (volatile int *) 0xfc000000;
    volatile int *uart0_addr = (volatile int *) 0x02108000;

    while((uart0_addr[0x14/4]&0x20)==0);
      uart0_addr[0x0/4]=c;
    return(c);
}
// Redirect output (from printf etc) to the tube.
// This redirects all streams to the tube.
int _write(int fh, char *buf, int count)
{
  int i = 0;

  while (i < count)
    output_char(buf[i++]);

  return count;
}

// On exit write CTRL-D (EOT character) to the validation tube
// which causes the simulation to terminate
void _exit(int c)
{

  // Loop forever until the simulator terminates
  while (1);
}

void init_libc(void)
{
    // Zero the BSS
//    size_t bss_size = __bss_end__ - __bss_start__;
//    memset(__bss_start__, 0, bss_size);
    /* atexit(__libc_fini_array);*/
    __libc_init_array();
}

extern int main(int argc, char **argv);

int _arm_start()
{
    init_libc();
   if( main(0, NULL) == 1)
        exit(1);
//    exit(main(0, NULL));
}

