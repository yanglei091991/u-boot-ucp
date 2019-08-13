// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2010-2011 Freescale Semiconductor, Inc.
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/clock.h>
#include <asm/arch/func_lib.h>
#include <linux/errno.h>
#include <mmc.h>
#include <miiphy.h>
#include <netdev.h>
#include <asm/arch-armv7/systimer.h>

DECLARE_GLOBAL_DATA_PTR;
#define CONFIG_SYS_TIMER_COUNTER 0x031d0004
static struct systimer *systimer_base = (struct systimer *)0x031d0000;

 void mapu_timer_init(void)
{
	/*
	 * Set Timer0 to be:
	 *   Enabled, free running, no interrupt, user-mode
	 */
	writel(SYSTIMER_RELOAD, &systimer_base->timer0load);
	writel(5, &systimer_base->timer0control);
}


int dram_init(void)
{
	return 0;
}

int board_init(void)
{
//    ucp_ddr_init();
	mapu_timer_init();
	return 0;
}
