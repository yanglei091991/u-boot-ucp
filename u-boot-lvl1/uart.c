


#include "uart.h"

#pragma GCC push_options
#pragma GCC optimize ("O0")

#define    DRV_OK                     0x0
#define    WAIT_TIMEOUT        0x1
#define    ECC_ERROR               0x2
#define    PARA_ERROR            0x3
#define    ERASE_ERROR          0x4
#define    PROM_ERROR           0x5

//volatile unsigned int *uart0_addr=(volatile unsigned int *) UART_BASE_0;
struct mapu_uart *uart0_addr =(struct mapu_uart *)UART_BASE_0;

/* 串口初始化 */
void   boot_uart_init(void)
{
  int baud_divisor=UART0_CLK/16/UART0_BAUDRATE;
  
	(uart0_addr->reg1).ier = 0x0; //Interrupt Enable Register
  uart0_addr->lcr = UART_LCR_BKSE | UART_LCRVAL;
  (uart0_addr->reg0).dll = 0x0;
  (uart0_addr->reg1).dlh = 0x0;
  uart0_addr->lcr = UART_LCRVAL;
//  __uart0->mcr = UART_MCRVAL;
	(uart0_addr->reg2).fcr = UART_FCRVAL;
	
	uart0_addr->lcr = UART_LCR_BKSE | UART_LCRVAL;
  (uart0_addr->reg0).dll = baud_divisor & 0xff;
  (uart0_addr->reg1).dlh = (baud_divisor >> 8) & 0xff;
  uart0_addr->lcr = UART_LCRVAL;

}

/* 串口输出一个8bit字符 */
void sendchar(unsigned char *ch)
{
	unsigned int send_ch;
	
	  while ((uart0_addr->lsr & UART_LSR_THRE) == 0);

	  send_ch = *ch;
	  uart0_addr->reg0.thr = send_ch;
}



#if  0
unsigned char receive_char(void)
{
  volatile int ch = '0';
  
	while ((uart0_addr->lsr & UART_LSR_DR) == 0) {
	}
	
	ch = uart0_addr->reg0.rbr;
	return (char)ch;
}
#endif

/* 串口输出一个字符串
  Uart_Printf("UART init success\n\r");
*/
void Uart_Printf(unsigned char *string)
{
	unsigned char *buf;
	buf =string;
	do{
		sendchar(buf);
		buf++;
	}while(*buf!='\0');
}

void  print_hex(unsigned char hex)
{
   char    out[5];
   
      out[0] = 48 + hex / 16;
      out[1] = 48 + hex % 16;
      if (out[0] > 57) out[0] += 7;
      if (out[1] > 57) out[1] += 7;
	  out[2]= '\n';
	  out[3]= '\r';
	  out[4]= '\0';
	  Uart_Printf(out);
}


#pragma GCC pop_options



