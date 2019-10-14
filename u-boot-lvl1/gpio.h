#ifndef _GPIO_H_

#define _GPIO_H_

/**********************************************************************************************/
/***********************************		GPIO寄存器定义		*******************************/
/**********************************************************************************************/


#define GPIOS_PER_PORT		32

#if  0
#define   GPIOADDR_BASE   0x42050000
#else
#define   GPIOADDR_BASE   0x02118000

#endif

#define   gpio_swporta_dr      (*(volatile unsigned int *)(GPIOADDR_BASE+0x000)) //GPIO 
#define   gpio_swporta_ddr    (*(volatile unsigned int  *)(GPIOADDR_BASE+0x004)) //GPIO 
#define   gpio_swporta_ctl     (*(volatile unsigned int *)(GPIOADDR_BASE+0x008)) //GPIO 
#define   gpio_swportb_dr     (*(volatile unsigned int *)(GPIOADDR_BASE+0x00C)) //GPIO 
#define   gpio_swportb_ddr    (*(volatile unsigned int *)(GPIOADDR_BASE+0x010)) //GPIO 
#define   gpio_swportb_ctl     (*(volatile unsigned int *)(GPIOADDR_BASE+0x014)) //GPIO 
#define   gpio_swportc_dr     (*(volatile unsigned int *)(GPIOADDR_BASE+0x018)) //GPIO 
#define   gpio_swportc_ddr    (*(volatile unsigned int *)(GPIOADDR_BASE+0x01C)) //GPIO 
#define   gpio_swportc_ctl     (*(volatile unsigned int *)(GPIOADDR_BASE+0x020)) //GPIO 
#define   gpio_swportd_dr     (*(volatile unsigned int *)(GPIOADDR_BASE+0x024)) //GPIO 
#define   gpio_swportd_ddr    (*(volatile unsigned int *)(GPIOADDR_BASE+0x028)) //GPIO 
#define   gpio_swportd_ctl     (*(volatile unsigned int *)(GPIOADDR_BASE+0x02C)) //GPIO 
#define   gpio_inten                (*(volatile unsigned int *)(GPIOADDR_BASE+0x030)) //GPIO 
#define   gpio_intmask           (*(volatile unsigned int *)(GPIOADDR_BASE+0x034)) //GPIO 
#define   gpio_inttype_level   (*(volatile unsigned int *)(GPIOADDR_BASE+0x038)) //GPIO 
#define   gpio_int_polarity     (*(volatile unsigned int *)(GPIOADDR_BASE+0x03C)) //GPIO 
#define   gpio_intstatus         (*(volatile unsigned int *)(GPIOADDR_BASE+0x040)) //GPIO 
#define   gpio_raw_intstatus  (*(volatile unsigned int *)(GPIOADDR_BASE+0x044)) //GPIO 
#define   gpio_debounce        (*(volatile unsigned int *)(GPIOADDR_BASE+0x048)) //GPIO 
#define   gpio_porta_eoi        (*(volatile unsigned int *)(GPIOADDR_BASE+0x04C)) //GPIO 
#define   gpio_ext_porta        (*(volatile unsigned int *)(GPIOADDR_BASE+0x050)) //GPIO 
#define   gpio_ext_portb        (*(volatile unsigned int *)(GPIOADDR_BASE+0x054)) //GPIO 
#define   gpio_ext_portc        (*(volatile unsigned int *)(GPIOADDR_BASE+0x058)) //GPIO 
#define   gpio_ext_portd        (*(volatile unsigned int *)(GPIOADDR_BASE+0x05C)) //GPIO 
#define   gpio_ls_sync           (*(volatile unsigned int *)(GPIOADDR_BASE+0x060)) //GPIO 
#define   gpio_id_code           (*(volatile unsigned int *)(GPIOADDR_BASE+0x064)) //GPIO 
 
#define   gpio_ver_id_code    (*(volatile unsigned int *)(GPIOADDR_BASE+0x06C)) //GPIO 
#define   gpio_config_reg1    (*(volatile unsigned int *)(GPIOADDR_BASE+0x070)) //GPIO 
#define   gpio_config_reg2    (*(volatile unsigned int *)(GPIOADDR_BASE+0x074)) //GPIO
/** endof GPIO寄存器定义 **/

/********		GPIO IP参数配置		*********/
#define GPIOA_WIDTH						8
#define GPIOB_WIDTH						8
#define GPIOC_WIDTH						32
#define GPIOD_WIDTH						32

/*  GPIOB  gpio[32--63]
   gpio[43]       output  --> AD9361--CTRL_IN3
   gpio[44]       output  --> AD9361--EN_AGC   -- /HOLD
   gpio[45]--> AD9361--SYNC_IN   -- /WP
   gpio[46]--> AD9361--RESETB    -- LED0
*/

#define   GPIO_SPI_CS_PIN           GPIO_Pin_11      /* gpio[43]--CTRL_IN3  */
#define   GPIO_SPI_HOLD_PIN      GPIO_Pin_12      /* gpio[44]--EN_AGC  */
#define   GPIO_SPI_WP_PIN          GPIO_Pin_13     /* gpio[45]--SYNC_IN  */
#define   GPIO_LED0_PIN               GPIO_Pin_17     /* AP_GPIOB17 */
#define   GPIO_LED1_PIN               GPIO_Pin_20     /* AP_GPIOB20 */
#define   GPIO_LED2_PIN               GPIO_Pin_21     /* AP_GPIOB21 */



/* GPIO_Pin定义 */
#if(GPIOS_PER_PORT == 32)
	#define GPIO_Pin_0                 (0x00000001)  /*!< Pin 0 selected */
	#define GPIO_Pin_1                 (0x00000002)  /*!< Pin 1 selected */
	#define GPIO_Pin_2                 (0x00000004)  /*!< Pin 2 selected */
	#define GPIO_Pin_3                 (0x00000008)  /*!< Pin 3 selected */
	#define GPIO_Pin_4                 (0x00000010)  /*!< Pin 4 selected */
	#define GPIO_Pin_5                 (0x00000020)  /*!< Pin 5 selected */
	#define GPIO_Pin_6                 (0x00000040)  /*!< Pin 6 selected */
	#define GPIO_Pin_7                 (0x00000080)  /*!< Pin 7 selected */
	#define GPIO_Pin_8                 (0x00000100)  /*!< Pin 8 selected */
	#define GPIO_Pin_9                 (0x00000200)  /*!< Pin 9 selected */
	#define GPIO_Pin_10                (0x00000400)  /*!< Pin 10 selected */
	#define GPIO_Pin_11                (0x00000800)  /*!< Pin 11 selected */
	#define GPIO_Pin_12                (0x00001000)  /*!< Pin 12 selected */
	#define GPIO_Pin_13                (0x00002000)  /*!< Pin 13 selected */
	#define GPIO_Pin_14                (0x00004000)  /*!< Pin 14 selected */
	#define GPIO_Pin_15                (0x00008000)  /*!< Pin 15 selected */
	#define GPIO_Pin_16                (0x00010000)  /*!< Pin 16 selected */
	#define GPIO_Pin_17                (0x00020000)  /*!< Pin 17 selected */
	#define GPIO_Pin_18                (0x00040000)  /*!< Pin 18 selected */
	#define GPIO_Pin_19                (0x00080000)  /*!< Pin 19 selected */
	#define GPIO_Pin_20                (0x00100000)  /*!< Pin 20 selected */
	#define GPIO_Pin_21                (0x00200000)  /*!< Pin 21 selected */
	#define GPIO_Pin_22                (0x00400000)  /*!< Pin 22 selected */
	#define GPIO_Pin_23                (0x00800000)  /*!< Pin 23 selected */
	#define GPIO_Pin_24                (0x01000000)  /*!< Pin 24 selected */
	#define GPIO_Pin_25                (0x02000000)  /*!< Pin 25 selected */
	#define GPIO_Pin_26                (0x04000000)  /*!< Pin 26 selected */
	#define GPIO_Pin_27                (0x08000000)  /*!< Pin 27 selected */
	#define GPIO_Pin_28                (0x10000000)  /*!< Pin 28 selected */
	#define GPIO_Pin_29                (0x20000000)  /*!< Pin 29 selected */
	#define GPIO_Pin_30                (0x40000000)  /*!< Pin 30 selected */
	#define GPIO_Pin_31                (0x80000000)  /*!< Pin 31 selected */
	#define GPIO_Pin_All               (0xFFFFFFFF)  /*!< All pins selected */

#elif(GPIOS_PER_PORT == 16)
	#define GPIO_Pin_0                 (0x0001)  /*!< Pin 0 selected */
	#define GPIO_Pin_1                 (0x0002)  /*!< Pin 1 selected */
	#define GPIO_Pin_2                 (0x0004)  /*!< Pin 2 selected */
	#define GPIO_Pin_3                 (0x0008)  /*!< Pin 3 selected */
	#define GPIO_Pin_4                 (0x0010)  /*!< Pin 4 selected */
	#define GPIO_Pin_5                 (0x0020)  /*!< Pin 5 selected */
	#define GPIO_Pin_6                 (0x0040)  /*!< Pin 6 selected */
	#define GPIO_Pin_7                 (0x0080)  /*!< Pin 7 selected */
	#define GPIO_Pin_8                 (0x0100)  /*!< Pin 8 selected */
	#define GPIO_Pin_9                 (0x0200)  /*!< Pin 9 selected */
	#define GPIO_Pin_10                (0x0400)  /*!< Pin 10 selected */
	#define GPIO_Pin_11                (0x0800)  /*!< Pin 11 selected */
	#define GPIO_Pin_12                (0x1000)  /*!< Pin 12 selected */
	#define GPIO_Pin_13                (0x2000)  /*!< Pin 13 selected */
	#define GPIO_Pin_14                (0x4000)  /*!< Pin 14 selected */
	#define GPIO_Pin_15                (0x8000)  /*!< Pin 15 selected */
	#define GPIO_Pin_All               (0xFFFF)  /*!< All pins selected */	
#endif


/* GPIO主要函数声明 */
extern  void boot_gpio_set_value(unsigned int pin_num, unsigned char value);
void  drv_gpio_init(void);
void  drv_led0_on(void);
void  drv_led0_off(void);



#endif /*GPIO_H_*/
