/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2013, NVIDIA CORPORATION.  All rights reserved.
 */

#ifndef __UCP_COMMON_H
#define __UCP_COMMON_H
#define CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_BOARD_POSTCLK_INIT

#define CONFIG_SYS_BOOTM_LEN	0x1000000

#include <linux/sizes.h>
#define CONFIG_SYS_TIMER_COUNTER 0x031d0004
#define CONFIG_SYS_TIMER_COUNTS_DOWN
/* Boot options */
#define CONFIG_LOADADDR		0x00000000
#define CONFIG_SYS_LOAD_ADDR	CONFIG_LOADADDR

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/* Miscellaneous configurable options */
#define CONFIG_SYS_CBSIZE	512
#define CONFIG_SYS_MAXARGS	32

/* MMC */
#define CONFIG_BOUNCE_BUFFER

// yanglei
#define IRAM_BASE_ADDR      			0x10000000
#define IRAM_SIZE                       0x00100000
//#define ROMCP_ARB_BASE_ADDR             0x00000000
//#define ROMCP_ARB_END_ADDR              0x000FFFFF
#define MMDC0_ARB_BASE_ADDR             0x20000000
#define MMDC0_ARB_END_ADDR              0x7FFFFFFF

// u-boot size
#define CONFIG_SYS_MONITOR_BASE CONFIG_SYS_FLASH_BASE
#define CONFIG_SYS_FLASH_BASE 0x00000000


/* NS16550 Serial Configuration */
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_CONS_INDEX		1
#define CONFIG_SYS_NS16550_CLK		25000000   /* 41200000 */
#define CONFIG_SYS_NS16550_COM1   0x02108000 /* 0x50920000, Base EVM has UART0 */ /*Match MaPU chip*/
#define CONFIG_BAUDRATE		115200
#define CONFIG_SYS_BAUDRATE_TABLE  \
    {300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400}
#define CONFIG_SYS_NS16550_MEM32

#endif
