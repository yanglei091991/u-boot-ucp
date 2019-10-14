


#include  "pinmux.h"

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

/*
pad69	SPI0_SSN
pad70	SPI0_CLK
pad71	SPI0_MISO
pad72	SPI0_MOSI
*/
void  spi0_pin_init(void)
{
    unsigned int val,src;
    
    val = SPI0_SSN |SPI0_CLK|SPI0_MISO |SPI0_MOSI;    
    src = PINMUX_1A0 & 0xFF00FFFF;
    PINMUX_1A0 = (val|src);
}
#endif

/*
pad27	SPI2_SSN
pad28	SPI2_CLK
pad29	SPI2_MISO
pad30	SPI2_MOSI
*/
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

    //spi1_gpio_pin_init();
    //spi2_gpio_pin_init();
    //rs485_gpio_pin_init();	
    //spi0_pin_init();
    spi2_pin_init();
    LED_gpio_pin_init();

}








