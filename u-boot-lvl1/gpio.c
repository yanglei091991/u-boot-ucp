


#include "gpio.h"

#pragma GCC push_options
#pragma GCC optimize ("O0")



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


// gpiob_set_value(unsigned int pin_num, 0)
// gpiob_set_value(GPIO_LED0_PIN, 1)    
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



unsigned int boot_gpiob_read(void)
{
     unsigned int  value;
     value = gpio_swportb_dr;
     return  value;
}





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


#if   1    
/* gpio[32]--bit0, 
   gpio[32-39] input    <-- AD9361--CTRL_OUT0        
   gpio[40-43] output  --> AD9361--CTRL_IN0    --all 1
   gpio[44]       output  --> AD9361--EN_AGC   -- /HOLD
   gpio[45]--> AD9361--SYNC_IN   -- /WP
   gpio[46]--> AD9361--RESETB    -- LED0
   gpio[47]--> AD9361--TXNRX      -- 
   gpio[48]--> AD9361--ENABLE,    -- 
   0x0001FF00 
*/
    gpio_swportb_ddr = 0x0001FF00;     /* Data Direction: 1--output, 0--input */
    //gpio_swportb_dr =  0x0001FF00;      /*  */
    gpio_swportb_dr =  0x0001FF00;           /*   */
    gpio_swportb_ctl =0;
#endif

}

#pragma GCC pop_options






