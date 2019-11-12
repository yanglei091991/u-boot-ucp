// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2010-2011 Freescale Semiconductor, Inc.
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/clock.h>
#include <linux/errno.h>
#include <mmc.h>
#include <miiphy.h>
#include <netdev.h>
#include <asm/arch-armv7/systimer.h>
#include <asm/mach-types.h>
#include "ucp_ddr_dccm.h"
#include "ucp_ddr_iccm.h"

#ifdef CONFIG_MMC
#include <common.h>
#include <dwmmc.h>
#include <malloc.h>

#define SDIO_BASE	0x02050000	
#endif

#define DCCM_BASE_ADDR 0x020c0000
#define ICCM_BASE_ADDR 0x020d0000

DECLARE_GLOBAL_DATA_PTR;
#define CONFIG_SYS_TIMER_COUNTER 0x031d0004
static struct systimer *systimer_base = (struct systimer *)0x031d0000;

void  spi2_ssn_gpio_init(void);

void copy_ddr_ref(void)
{
    memcpy((int*)DCCM_BASE_ADDR, dccm_arr, sizeof(dccm_arr));
    memcpy((int*)ICCM_BASE_ADDR, iccm_arr, sizeof(iccm_arr));
}

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
	return 0;
}

int board_init(void)
{
	gd->bd->bi_boot_params = PHYS_SDRAM_1+ 0xb000000;
	gd->bd->bi_arch_number = MACH_TYPE_UCP;
	ucp_timer_init();
    spi2_ssn_gpio_init();
    copy_ddr_ref();
//    ddr_init();

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
	host->buswidth = 1;
	host->dev_index = 0;
    host->fifo_mode = 0;
    host->fifoth_val = MSIZE(0x2) | RX_WMARK(0x100 / 2 - 1) | TX_WMARK(0x100 / 2);
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

#define   PINMUX_BASE      0x020e0000
#define   GPIOADDR_BASE    0x02118000

#define   SPI2_SSN_GPIO    (0x3)   /* pad61	SPI2_SSN_GPIO */
#define   PINMUX_1A0       (*(volatile unsigned int *)(PINMUX_BASE+0x1a0))

#define   gpio_swportb_dr     (*(volatile unsigned int *)(GPIOADDR_BASE+0x00C)) //GPIO 
#define   gpio_swportb_ddr    (*(volatile unsigned int *)(GPIOADDR_BASE+0x010)) //GPIO 
#define   gpio_swportb_ctl    (*(volatile unsigned int *)(GPIOADDR_BASE+0x014)) //GPIO
#define   GPIO_Pin_12         (0x00001000)  /*!< Pin 12 selected */

/* pad61	SPI2_SSN pin CP_GPIOB12 */
void  spi2_ssn_gpio_init(void)
{
    unsigned int val,src;
    
    val = SPI2_SSN_GPIO;    
    src = PINMUX_1A0& 0xFFFFFFFC;
    PINMUX_1A0 = (val|src);

    gpio_swportb_ddr |= GPIO_Pin_12;     /* Data Direction: 1--output, 0--input */
    gpio_swportb_dr =  GPIO_Pin_12;      /* output level  */
    gpio_swportb_ctl =0;
}

//spi2_ssn_gpio_set_value(1)
//spi2_ssn_gpio_set_value(0)
void  spi2_ssn_gpio_set_value(unsigned char high)
{
     unsigned char  value;
     value = gpio_swportb_dr;
     if(high)
       value |= GPIO_Pin_12;
     else
       value &= (~GPIO_Pin_12); 
     gpio_swportb_dr = value;
}

