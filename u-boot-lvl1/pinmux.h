



#define   PINMUX_BASE      0x020d8000

#define   PINMUX_190      (*(volatile unsigned int *)(PINMUX_BASE+0x190))   
#define   PINMUX_194      (*(volatile unsigned int *)(PINMUX_BASE+0x194))   /*(Pad30- Pad17)*/
#define   PINMUX_198      (*(volatile unsigned int *)(PINMUX_BASE+0x198))
#define   PINMUX_19C      (*(volatile unsigned int *)(PINMUX_BASE+0x19c))
#define   PINMUX_1A0      (*(volatile unsigned int *)(PINMUX_BASE+0x1a0))


/* 偏移地址：0x194(Pad30-Pad17) */
/* SPI2--  第二功能 */
#define    SPI2_SSN      (0x1<<20)   /* pad27	SPI2_SSN */
#define    SPI2_CLK      (0x1<<22)   /* pad28	SPI2_CLK */
#define    SPI2_MISO    (0x1<<24)   /* pad29	SPI2_MISO  */
#define    SPI2_MOSI    (0x1<<26)   /* pad30	SPI2_MOSI */



/* 偏移地址：0x1A0(Pad75-Pad61) */
#define   AP_GPIOB15   (0x3<<6)    /* Pad64 */
#define   AP_GPIOB16   (0x3<<8)    /* Pad65 */
#define   AP_GPIOB17   (0x3<<10)   /* Pad66--LED0 */
#define   AP_GPIOB19   (0x3<<14)   /* Pad68--LED0 */
#define   AP_GPIOB20   (0x3<<24)    /* Pad73-- LED1 */
#define   AP_GPIOB21   (0x3<<26)    /* Pad74-- LED2 */




/* SPI0--  第二功能 */
#define    SPI0_SSN      (0x1<<16)   /* pad69   SPI0_SSN */
#define    SPI0_CLK      (0x1<<18)   /* pad70   SPI0_CLK */
#define    SPI0_MISO    (0x1<<20)   /* pad71   SPI0_MISO */
#define    SPI0_MOSI    (0x1<<22)   /* pad72   SPI0_MOSI */



/* 偏移地址：0x198(Pad45-Pad31) */
#define   AP_GPIOA26   (0x3<<24)    /* Pad43 */
#define   AP_GPIOA27   (0x3<<26)    /* Pad44 */
#define   AP_GPIOA28   (0x3<<28)    /* Pad45 */





/****************************************/
/* CRG--- */
/****************************************/
#define   CRG_BASE     0x03670000
#define   DDR_ENABLE   0x60







