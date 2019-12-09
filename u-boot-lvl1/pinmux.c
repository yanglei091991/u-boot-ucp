


#include  "pinmux.h"
#include  "gpio.h"

#if  0
void  test_pin_init(void)
{
    //unsigned int val;
    
    PINMUX_194 = 0;
    PINMUX_198 = 0;
    PINMUX_19C = 0;
    PINMUX_1A0 = 0;    
}

/*  /hold /wp */
void  spi1_holdwp_gpio_pin_init(void)
{
    unsigned int val,src;
    val = AP_GPIOA26|AP_GPIOA27;
    src = PINMUX_198 & 0xF0FFFFFF;
    
    PINMUX_198 = (val|src);    
}


/*  /hold /wp */
void  spi2_holdwp_gpio_pin_init(void)
{
    unsigned int val,src;
    val = AP_GPIOA28;
    src = PINMUX_198 & 0xCFFFFFFF;    
    PINMUX_198 = (val|src);  

    // AP_GPIOB15??
    val = AP_GPIOB15;
    src = PINMUX_1A0 & 0xFFFFFF3F;    
    PINMUX_1A0 = (val|src);     
    
}
#endif

static void spi_cs_delay(volatile unsigned int num)
{
	while(num--);
}

/*
pad69	SPI0_SSN -- not used
pad70	SPI0_CLK
pad71	SPI0_MISO
pad72	SPI0_MOSI
pad73   AP_GPIOB20 as spi0_cs, 
*/
void  spi0_pin_init(void)
{
    unsigned int val,src;
      
    val = AP_GPIOB20|SPI0_SSN |SPI0_CLK|SPI0_MISO |SPI0_MOSI;
    src = PINMUX_1A0 & 0xFC00FFFF;
    PINMUX_1A0 = (val|src);

    /* pad73  AP_GPIOB20 as output(spi0_cs) */ 
    gpio_swportb_ddr |= GPIO_Pin_20;     /* Data Direction: 1--output, 0--input */
    gpio_swportb_dr  |=  GPIO_Pin_20;    /* output level  */
    gpio_swportb_ctl =0;     
}
/* pad73   AP_GPIOB20 as spi0_cs */
void  spi0_ssn_gpio_set_value(unsigned char high)
{
     unsigned char  value;

     spi_cs_delay(SPI_CS_DELAY);
     
     value = gpio_swportb_dr;
     if(high)
       value |= GPIO_Pin_20;
     else
       value &= (~GPIO_Pin_20); 
     gpio_swportb_dr = value;
}


/* CARD_WPTR  CARD_DECT是第2功能,
   手册中是第3功能
*/
void  sd_detect_pin_init(void)
{
   unsigned int val;

   val = PINMUX_198 & (~0x00F00000);
   val |= 0x00500000;   
   PINMUX_198 = val;  
}


/*
pad27	SPI2_SSN
pad28	SPI2_CLK
pad29	SPI2_MISO
pad30	SPI2_MOSI
*/
#if  0 
void  spi2_pin_init(void)
{
    unsigned int val,src;
    
    val = SPI2_SSN |SPI2_CLK|SPI2_MISO |SPI2_MOSI;    
    src = PINMUX_194 & 0xF00FFFFF;
    PINMUX_194 = (val|src);
}


/* Pad66-- LED0   AP_GPIOB17 */
/* Pad73-- LED1   AP_GPIOB20 */
/* Pad74-- LED2   AP_GPIOB21 */
void  LED_gpio_pin_init(void)
{
    unsigned int val,src;
#if  0    
    val = AP_GPIOB17|AP_GPIOB20|AP_GPIOB21;
    src = PINMUX_1A0 & 0xF0FFF3FF;    
#else
    val = AP_GPIOB19;
    src = PINMUX_1A0 & 0xFFFF3FFF; 
#endif
    PINMUX_1A0 = (val|src);      
}

void  pinmux_init(void)
{

    sd_detect_pin_init();   
    spi2_ssn_gpio_init();
}

#endif

/* config SPI2_SSN in GPIO's output */
/* pad61	SPI2_SSN pin --AP_GPIOB12 */
void  spi2_ssn_gpio_init(void)
{
    unsigned int src;
       
    src = PINMUX_1A0& 0xFFFFFFFC;
    src |= SPI2_SSN_GPIO;
    PINMUX_1A0 = src;

    gpio_swportb_ddr |= GPIO_Pin_12;     /* Data Direction: 1--output, 0--input */
    gpio_swportb_dr  |=  GPIO_Pin_12;    /* output level  */
    gpio_swportb_ctl =0;
}

//spi2_ssn_gpio_set_value(1)
//spi2_ssn_gpio_set_value(0)
/* pad61	SPI2_SSN pin --AP_GPIOB12 */
void  spi2_ssn_gpio_set_value(unsigned char high)
{
     unsigned char  value;

     spi_cs_delay(SPI_CS_DELAY);
     
     value = gpio_swportb_dr;
     if(high)
       value |= GPIO_Pin_12;
     else
       value &= (~GPIO_Pin_12); 
     gpio_swportb_dr = value;
}









