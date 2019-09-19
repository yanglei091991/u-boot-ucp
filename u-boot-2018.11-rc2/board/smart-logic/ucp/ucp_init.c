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
#include <asm/mach-types.h>

#ifdef CONFIG_MMC
#include <common.h>
#include <dwmmc.h>
#include <malloc.h>

#define SDIO_BASE	0x02050000	
#endif

#define _READ_INTERFACE
#include "copy_image.h"

DECLARE_GLOBAL_DATA_PTR;
#define CONFIG_SYS_TIMER_COUNTER 0x031d0004
static struct systimer *systimer_base = (struct systimer *)0x031d0000;

 void ucp_timer_init(void)
{
	/*
	 * Set Timer0 to be:
	 *   Enabled, free running, no interrupt, user-mode
	 */
	writel(SYSTIMER_RELOAD, &systimer_base->timer0load);
	writel(5, &systimer_base->timer0control);
}

int dram_init_banksize(void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size =
			get_ram_size((long *)PHYS_SDRAM_1, PHYS_SDRAM_1_SIZE);
    return 0;
}

int dram_init(void)
{
	gd->ram_size =
		get_ram_size((long *)PHYS_SDRAM_1, PHYS_SDRAM_1_SIZE);
    dram_init_banksize();
	return 0;
}

int board_init(void)
{
	gd->bd->bi_boot_params = PHYS_SDRAM_1+ 0xb000000;
	gd->bd->bi_arch_number = MACH_TYPE_UCP;
//    ucp_ddr_init();
	ucp_timer_init();

//	unsigned int *src = (unsigned int*)(int)(2048*6); // nand flash image addr
//	unsigned char *dest = (unsigned char*)0x20000000; // ddr image addr
//
//	if(copy_image_dts_to_ram(src, dest) == false)
//	{
//	return false;  
//	}
//	src = (unsigned int*)(int)(2048*7); // nand flash dts addr
//	dest = (unsigned char*)0x28000000; // ddr dts addr
//	if(copy_image_dts_to_ram(src, dest) == false)
//	{
//	return false;  
//	}

	return 0;
}

int board_mmc_init(bd_t *bis)
{
	struct dwmci_host *host = NULL;

	host = malloc(sizeof(struct dwmci_host));
	if (!host) {
		printf("dwmci_host malloc fail!\n");
		return 1;
	}

	memset(host, 0, sizeof(struct dwmci_host));
	host->name = "Synopsys Mobile storage";
	host->ioaddr = (void *)SDIO_BASE;
	host->buswidth = 4;
	host->dev_index = 0;
	host->bus_hz = 50000000;
//	host->bus_hz = 4000000;

//	add_dwmci(host, host->bus_hz, 400000);
	add_dwmci(host, 1000000, 400000);
//    printf("400k Hz!\n");

	return 0;
}

int board_mmc_getcd(struct mmc *mmc)
{
	struct dwmci_host *host = mmc->priv;

	return !(dwmci_readl(host, DWMCI_CDETECT) & 1);
}
