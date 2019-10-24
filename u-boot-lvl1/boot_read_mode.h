#ifndef BOOT_READ_MODE_H
#define BOOT_READ_MODE_H

//SYSCFG
#define SYSCFG_BASE_ADDR       0x03690000
#define A53_M3_REMAP           (*((volatile unsigned int *)(SYSCFG_BASE_ADDR + 0x00*4)))
#define A53CORE0_VRBA          (*((volatile unsigned int *)(SYSCFG_BASE_ADDR + 0x01*4)))
#define A53CORE1_VRBA          (*((volatile unsigned int *)(SYSCFG_BASE_ADDR + 0x02*4)))
#define HSIO_MODE_SEL          (*((volatile unsigned int *)(SYSCFG_BASE_ADDR + 0x03*4)))
#define I2C_CFG                (*((volatile unsigned int *)(SYSCFG_BASE_ADDR + 0x04*4)))
#define UART_CFG               (*((volatile unsigned int *)(SYSCFG_BASE_ADDR + 0x05*4)))
#define TIMER_CFG              (*((volatile unsigned int *)(SYSCFG_BASE_ADDR + 0x06*4)))
#define GPIO_CFG               (*((volatile unsigned int *)(SYSCFG_BASE_ADDR + 0x07*4)))
#define RTC_CFG                (*((volatile unsigned int *)(SYSCFG_BASE_ADDR + 0x08*4)))
#define WDT_CFG                (*((volatile unsigned int *)(SYSCFG_BASE_ADDR + 0x09*4)))
#define SM5_CFG                (*((volatile unsigned int *)(SYSCFG_BASE_ADDR + 0x0a*4)))
#define A53_CNTVAL_L           (*((volatile unsigned int *)(SYSCFG_BASE_ADDR + 0x0b*4)))
#define A53_CNTVAL_H           (*((volatile unsigned int *)(SYSCFG_BASE_ADDR + 0x0c*4)))
#define A53_CNTCLKEN           (*((volatile unsigned int *)(SYSCFG_BASE_ADDR + 0x0d*4)))
#define GIC400_USER            (*((volatile unsigned int *)(SYSCFG_BASE_ADDR + 0x0e*4)))
#define GPMC_CFG               (*((volatile unsigned int *)(SYSCFG_BASE_ADDR + 0x0f*4)))

#define     BIT0                    (0x1<<0ul)
#define     BIT1                    (0x1<<1ul)
#define     BIT2                    (0x1<<2ul)
#define     BIT3                    (0x1<<3ul)
#define     BIT4                    (0x1<<4ul)
#define     BIT5                    (0x1<<5ul)
#define     BIT6                    (0x1<<6ul)
#define     BIT7                    (0x1<<7ul)
#define     BIT8                    (0x1<<8ul)
#define     BIT9                    (0x1<<9ul)
#define     BIT10                   (0x1<<10ul)
#define     BIT11                   (0x1<<11ul)
#define     BIT12                   (0x1<<12ul)
#define     BIT13                   (0x1<<13ul)
#define     BIT14                   (0x1<<14ul)
#define     BIT15                   (0x1<<15ul)
#define     BIT16                   (0x1<<16ul)
#define     BIT17                   (0x1<<17ul)
#define     BIT18                   (0x1<<18ul)
#define     BIT19                   (0x1<<19ul)
#define     BIT20                   (0x1<<20ul)
#define     BIT21                   (0x1<<21ul)
#define     BIT22                   (0x1<<22ul)
#define     BIT23                   (0x1<<23ul)
#define     BIT24                   (0x1<<24ul)
#define     BIT25                   (0x1<<25ul)
#define     BIT26                   (0x1<<26ul)
#define     BIT27                   (0x1<<27ul)
#define     BIT28                   (0x1<<28ul)
#define     BIT29                   (0x1<<29ul)
#define     BIT30                   (0x1<<30ul)
#define     BIT31                   (0x1<<31ul)


#define  BOOT_CFG_SYNC    BIT3
#define  BOOT_CTL_SYNC4   BIT4
#define  BOOT_CTL_SYNC5   BIT5

#define IS_ROM_BOOT    0  
#define IS_ROM_GPMC    1

void  read_uboot_mode(void);

#endif // BOOT_READ_MODE_H
