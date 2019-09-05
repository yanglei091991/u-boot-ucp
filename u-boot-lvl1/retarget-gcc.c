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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <unistd.h>

extern char __bss_start__[], __bss_end__[];
extern void __libc_init_array(void);
extern void __libc_fini_array(void);

void initialise_monitor_handles(void) { }

int _close(int fh) { }
int _gettimeofday(struct timeval* tv,void* tz) { }
int _isatty(int fh) { }
int _lseek(int fh, off_t offset, int whence) { }
int _open(const char *path, int oflag, /* int mode */...) { return 1; }
int _read(int fh, unsigned char *buffer, int count) { }
int _rename(const char *old, const char *new ) { }
clock_t _times(struct tms *buf) { }
int _unlink(const char *name) { }
int _kill(int pid, int sig) { }
int _fstat(int fildes, struct stat *buf) { }

// Redirect output (from printf etc) to the tube.
// This redirects all streams to the tube.
int _write(int fh, char *buf, int count)
{
  int i = 0;

  while (i < count)
    ;

  return count;
}

// On exit write CTRL-D (EOT character) to the validation tube
// which causes the simulation to terminate
void _exit(int c)
{

  // Loop forever until the simulator terminates
  while (1);
}

caddr_t _sbrk_r ( struct _reent *r, int incr )
{
    extern   unsigned char  bottom_of_heap asm ("heap_base");
    register unsigned char* stack_pointer  asm ("sp");

    static unsigned char *heap_end;
    unsigned char        *prev_heap_end;

    if (heap_end == NULL)
        heap_end = &bottom_of_heap;

    prev_heap_end = heap_end;

    if (heap_end + incr > stack_pointer) {
        r->_errno = ENOMEM;

        return (caddr_t) -1;
    }

    heap_end += incr;

    return (caddr_t) prev_heap_end;
}


void init_libc(void)
{
    // Zero the BSS
    size_t bss_size = __bss_end__ - __bss_start__;
    memset(__bss_start__, 0, bss_size);
    /* atexit(__libc_fini_array);*/
    __libc_init_array();
}

extern int main(int argc, char **argv);

int _arm_start()
{
    init_libc();
    main(0, NULL);
//    exit(main(0, NULL));
}

