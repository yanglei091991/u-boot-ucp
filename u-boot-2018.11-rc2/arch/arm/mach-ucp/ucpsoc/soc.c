#include <common.h>
#include <linux/errno.h>
#include <asm/io.h>
#include <asm/bootm.h>
#include <stdbool.h>
#include <dm.h>
#include <mmc.h>


/* yanglei start */
//__weak struct serial_device *default_serial_console(void)
//{
//	return NULL;
//}

int print_cpuinfo(void)
{
	return 0;
}

void __attribute__((weak)) reset_cpu(ulong addr)
{
}

ulong get_tbclk(void)
{
  //return 0;
  return  50000000;// timer
}

int board_postclk_init(void)
{
	return 0;
}
/* yanglei end */
