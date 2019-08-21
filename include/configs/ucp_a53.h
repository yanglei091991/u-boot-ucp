#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_BOARD_POSTCLK_INIT

#define CONFIG_SYS_BOOTM_LEN	0x1000000

#include <linux/sizes.h>
#define CONFIG_SYS_TIMER_COUNTER 0x031d0004
#define CONFIG_SYS_TIMER_COUNTS_DOWN

/* Boot options */
//???
#define CONFIG_LOADADDR		0x40000000
//???
#define CONFIG_SYS_LOAD_ADDR	CONFIG_LOADADDR

/* allow to overwrite serial and ethaddr */
//???
#define CONFIG_ENV_OVERWRITE

/* Miscellaneous configurable options */
//???
#define CONFIG_SYS_CBSIZE	512
//???
#define CONFIG_SYS_MAXARGS	32

/* MMC */
#define CONFIG_BOUNCE_BUFFER

// yanglei
#define IRAM_BASE_ADDR      			0x10000000
#define IRAM_SIZE                       0x00100000
//#define ROMCP_ARB_BASE_ADDR             0x00000000
//#define ROMCP_ARB_END_ADDR              0x000FFFFF

// u-boot size
//???
#if 0
#define CONFIG_SYS_MONITOR_BASE CONFIG_SYS_FLASH_BASE
#define CONFIG_SYS_FLASH_BASE 0x00000000
#endif


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

/* Physical Memory Map */

#define CONFIG_SYS_SDRAM_BASE		0x20000000
#define PHYS_SDRAM_SIZE             (0x4FFFFFFF - CONFIG_SYS_SDRAM_BASE)
//#define PHYS_SDRAM_SIZE             (0x7FFFFFFF - CONFIG_SYS_SDRAM_BASE)
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* Environment organization */
#define CONFIG_ENV_OFFSET		(6 * 64 * 1024)
#define CONFIG_ENV_SIZE			(8 * 1024)
//#define CONFIG_SYS_MMC_ENV_DEV		1

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 2 * 1024 * 1024)


#if 0


#define CONFIG_ARP_TIMEOUT	200UL

/* MMC Configs */
#define CONFIG_SYS_FSL_ESDHC_ADDR	USDHC4_BASE_ADDR
#define CONFIG_SYS_FSL_USDHC_NUM	2

#define IMX_FEC_BASE			ENET_BASE_ADDR
#define	CONFIG_FEC_XCV_TYPE		RGMII

#define CONFIG_EXTRA_ENV_SETTINGS \
	"script=boot.scr\0" \
	"image=zImage\0" \
	"console=ttymxc3\0" \
	"fdt_file=imx6q-arm2.dtb\0" \
	"fdt_addr=0x18000000\0" \
	"fdt_high=0xffffffff\0" \
	"initrd_high=0xffffffff\0" \
	"boot_fdt=try\0" \
	"ip_dyn=yes\0" \
	"mmcdev=1\0" \
	"mmcpart=1\0" \
	"mmcroot=/dev/mmcblk0p2 rootwait rw\0" \
	"mmcargs=setenv bootargs console=${console},${baudrate} " \
		"root=${mmcroot}\0" \
	"loadbootscript=" \
		"fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${script};\0" \
	"bootscript=echo Running bootscript from mmc ...; " \
		"source\0" \
	"loadimage=fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${image}\0" \
	"loadfdt=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0" \
	"mmcboot=echo Booting from mmc ...; " \
		"run mmcargs; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if run loadfdt; then " \
				"bootz ${loadaddr} - ${fdt_addr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootz; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootz; " \
		"fi;\0" \
	"netargs=setenv bootargs console=${console},${baudrate} " \
		"root=/dev/nfs " \
		"ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp\0" \
	"netboot=echo Booting from net ...; " \
		"run netargs; " \
		"if test ${ip_dyn} = yes; then " \
			"setenv get_cmd dhcp; " \
		"else " \
			"setenv get_cmd tftp; " \
		"fi; " \
		"${get_cmd} ${image}; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if ${get_cmd} ${fdt_addr} ${fdt_file}; then " \
				"bootz ${loadaddr} - ${fdt_addr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootz; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootz; " \
		"fi;\0"

#define CONFIG_BOOTCOMMAND \
	"mmc dev ${mmcdev};" \
	"mmc dev ${mmcdev}; if mmc rescan; then " \
		"if run loadbootscript; then " \
			"run bootscript; " \
		"else " \
			"if run loadimage; then " \
				"run mmcboot; " \
			"else run netboot; " \
			"fi; " \
		"fi; " \
	"else run netboot; fi"

/* Miscellaneous configurable options */
#define CONFIG_SYS_MEMTEST_START	0x10000000
#define CONFIG_SYS_MEMTEST_END		0x10010000
#endif


#endif				/* __CONFIG_H */
