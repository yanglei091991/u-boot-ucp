


#include "gpio.h"


/* led_con(LED0_ON|LED1_ON|LED2_ON) */
void  led_con(unsigned int led)
{
     unsigned int  value;
     value = gpio_swporta_dr;
     value &= ~(GPIO_Pin_19|GPIO_Pin_20|GPIO_Pin_21);
	 value |= led;
     gpio_swporta_dr = value;
}

void  led_gpio_init(void)
{ 
    gpio_swporta_ddr = GPIO_Pin_19|GPIO_Pin_20|GPIO_Pin_21;  /* Data Direction: 1--output, 0--input */
    gpio_swporta_dr  = 0;       /*  output high */
    gpio_swporta_ctl = 0;

}




