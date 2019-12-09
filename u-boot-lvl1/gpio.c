


#include "gpio.h"



#if  0
void    spi0_cs_high(void)
{
    unsigned int  val;    
    
    val = gpio_swportb_dr;
    val |= GPIO_SPI_CS_PIN;
    gpio_swportb_dr = val;
}

void    spi0_cs_low(void)
{
    unsigned int  val;    
    
    val = gpio_swportb_dr;
    val &= ~GPIO_SPI_CS_PIN;
    gpio_swportb_dr = val;

}
#endif

// gpiob_set_value(unsigned int pin_num, 0)
// boot_gpio_set_value(GPIO_LED0_PIN, 1)    
void boot_gpio_set_value(unsigned int pin_num, unsigned char value)
{
    unsigned int  val;    
    val = gpio_swportb_dr;
    
    if(value)
    	{
	val |= pin_num;
      }
    else
    	{
         val &= ~pin_num;
    }
    gpio_swportb_dr = val;
}


/* Pad66-- LED0   AP_GPIOB17 */
/* Pad73-- LED1   AP_GPIOB20 */
/* Pad74-- LED2   AP_GPIOB21 */
void  drv_led0_on(void)
{
     unsigned int  value;
     value = gpio_swportb_dr;
     value  |= GPIO_Pin_19; 
     gpio_swportb_dr = value;
}

void  drv_led0_off(void)
{
     unsigned int  value;
     value = gpio_swportb_dr;
     value  &= (~GPIO_Pin_19); 
     gpio_swportb_dr = value;
}

#if  0
void  drv_led1_on(void)
{
     unsigned int  value;
     value = gpio_swportb_dr;
     value  |= GPIO_Pin_20; 
     gpio_swportb_dr = value;
}

void  drv_led1_off(void)
{
     unsigned int  value;
     value = gpio_swportb_dr;
     value  &= (~GPIO_Pin_20); 
     gpio_swportb_dr = value;
}

void  drv_led2_on(void)
{
     unsigned int  value;
     value = gpio_swportb_dr;
     value  |= GPIO_Pin_21; 
     gpio_swportb_dr = value;
}

void  drv_led2_off(void)
{
     unsigned int  value;
     value = gpio_swportb_dr;
     value  &= (~GPIO_Pin_21); 
     gpio_swportb_dr = value;
}
#endif

/* GPIO define from  A53 */
void  drv_gpio_init(void)
{
#if   0  
    /*gpio[0-12]   input,  GPIO0ิฺตอฮป
        gpio[13-20]  output  0x001FE000, GPIO_LED_0-7 */
    gpio_swporta_ddr = 0x001FE000;       /* Data Direction: 1--output, 0--input */
    gpio_swporta_dr   = 0x001FE000;       /*  output high */
    gpio_swporta_ctl   = 0;
#endif

/* Pad66-- LED0   AP_GPIOB17 */
/* Pad73-- LED1   AP_GPIOB20 */
/* Pad74-- LED2   AP_GPIOB21 */
    gpio_swportb_ddr = GPIO_Pin_19;     /* Data Direction: 1--output, 0--input */
    gpio_swportb_dr =  0;           /* output level  */
    gpio_swportb_ctl =0;



}





