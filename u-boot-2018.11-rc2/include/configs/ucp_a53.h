#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_BOARD_POSTCLK_INIT

#define CONFIG_SYS_BOOTM_LEN	(64<<20)
#define CONFIG_SYS_BOOTMAPSZ    0x10000000
#define CONFIG_SYS_BOOT_GET_CMDLINE
#define CONFIG_SYS_BOOT_GET_KBD

#include <linux/sizes.h>
#define CONFIG_SYS_TIMER_COUNTER 0x031d0004
#define CONFIG_SYS_TIMER_COUNTS_DOWN

#define CONFIG_SYS_DCACHE_OFF
#define CONFIG_SYS_ICACHE_OFF
#define CONFIG_SYS_L2CACHE_OFF

/* Boot options */
//???
//#define CONFIG_LOADADDR		0x40000000

//???
#define CONFIG_SYS_LOAD_ADDR	0x20000000

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
//#define IRAM_BASE_ADDR      			0x10000000
//#define IRAM_SIZE                       0x04000000
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
#define CONFIG_SYS_NS16550_CLK		50000000   /* 41200000 */
#define CONFIG_SYS_NS16550_COM1   0x02108000 /* 0x50920000, Base EVM has UART0 */ /*Match MaPU chip*/
#define CONFIG_BAUDRATE		115200
#define CONFIG_SYS_BAUDRATE_TABLE  \
    {300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400}
#define CONFIG_SYS_NS16550_MEM32

/* Physical Memory Map */

#define UCP_DDR_BASE                0x20000000
#define CONFIG_SYS_SDRAM_BASE		UCP_DDR_BASE
//#define PHYS_SDRAM_SIZE             (0x10000000 * 4) /* 256MB * 4 */
//#define CONFIG_SYS_DRAM_SIZE        PHYS_SDRAM_SIZE
//#define CONFIG_SYS_SDRAM_SIZE       PHYS_SDRAM_SIZE 
//#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR

// TODO
#define UCP_RAM_BASE 0x4e60000
#define CONFIG_SYS_INIT_RAM_SIZE	(0x80000 * 3)
#define CONFIG_SYS_INIT_SP_OFFSET   (CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR		(UCP_RAM_BASE + CONFIG_SYS_INIT_SP_OFFSET)

//#define CONFIG_SYS_MEMTEST_START	UCP_DDR_BASE
//#define CONFIG_SYS_MEMTEST_END	    (UCP_DDR_BASE + PHYS_SDRAM_SIZE)


/* Environment organization */
//#define CONFIG_ENV_IS_IN_FLASH		0
#define CONFIG_ENV_OFFSET		(6 * 64 * 1024)
#define CONFIG_ENV_SIZE			(8 * 1024)
//#define CONFIG_SYS_MMC_ENV_DEV		1

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 20 * 1024 * 1024)


#define CONFIG_CMDLINE_EDITING		1
/*
 * Ethernet
 */
//#define CONFIG_MAPU_GMAC_BASE 0x036a0000
#define CONFIG_IPADDR    169.254.21.201
#define CONFIG_NETMASK   255.255.255.0
#define CONFIG_SERVERIP   169.254.21.176
#define CONFIG_GATEWAYIP   169.254.21.176
#define CONFIG_MII    /* expose smi ove miiphy interface */
#define CONFIG_CMD_MII
#define CONFIG_SYS_FAULT_ECHO_LINK_DOWN /* detect link using phy */
#define CONFIG_PHY_ADDR 1
#define CONFIG_DW_ALTDESCRIPTOR
/*-----------------------------------------------------------------------
 * Networking Configuration
 */
#define CONFIG_RGMII
#define CONFIG_PHY_MARVELL
#define CONFIG_SYS_RX_ETH_BUFFER	8
#define CONFIG_NET_RETRY_COUNT		20
#define CONFIG_ARP_TIMEOUT		5000 /* millisec */

#define MEM_LAYOUT_ENV_SETTINGS \
	"bootm_size=0x20000000\0" \
    "bootm_low=0x30000000\0" \
    "ethaddr=b2:77:62:76:f9:ee\0"

#define CONFIG_EXTRA_ENV_SETTINGS \
	MEM_LAYOUT_ENV_SETTINGS \
    "bootargs=console=ttyS0,115200n8 rdinit=/linuxrc\0"

//#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM_1				UCP_DDR_BASE
#define PHYS_SDRAM_1_SIZE		(0x10000000 * 2)

//#define CONFIG_FS_EXT4
//#define CONFIG_EXT4_WRITE
//#define CONFIG_CMD_EXT4
//#define CONFIG_CMD_EXT4_WRITE
#define CONFIG_CMD_FS_GENERIC

#if 0
/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME

 /*
  * Handover flattened device tree (dtb file) to Linux kernel
  */

 	"importbootenv= "					\
 		"env import -t -r ${uenvaddr} ${filesize};\0"	\
 								\
	"tftploadenv=tftp ${uenvaddr} ${uenvfile} \0"		\
	"tftploadscr=tftp ${uenvaddr} ${scriptfile} \0"		\
	"tftploadub=tftp ${loadaddr} ${ubootfile} \0"		\
								\
	"mmcloadenv=fatload mmc 0 ${uenvaddr} ${uenvfile}\0"	\
	"mmcloadscr=fatload mmc 0 ${uenvaddr} ${scriptfile}\0"	\
	"mmcloadub=fatload mmc 0 ${loadaddr} ${ubootfile}\0"	\
								\
	"loadbootenv=run mmcloadenv\0"				\
	"loadbootscr=run mmcloadscr\0"				\
	"loadbootenv=run mmcloadenv || run tftploadenv\0"	\
	"loadbootscr=run mmcloadscr || run tftploadscr\0"	\
 	"bootcmd_root= "					\
 		"if run loadbootenv; then "			\
 			"echo Loaded environment ${uenvfile}; "
#endif


#if 0

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
