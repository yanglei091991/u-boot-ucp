#ifndef UART_H
#define UART_H

#include "drv_common.h"

#define UART_BASE_0      0x02108000      /* UART 0 */
#define UART_BASE_1      0x02110000      /* UART 1 */


#define UART0_CLK            SYS_CLK
#define UART0_BAUDRATE    115200
//#define UART0_BAUDRATE    19200



#define UART_LCRVAL  UART_LCR_8N1		    /* 8 data, 1 stop, no parity */
#define UART_FCRVAL  (UART_FCR_FIFO_EN |UART_FCR_RXSR |	UART_FCR_TXSR)		/* Clear & enable FIFOs */
#define  UART_NUM     10

#define   M_LEN_10K   (10*1024)

struct mapu_uart { 
  union{ 
   volatile unsigned rbr; 			// Addressbyte 0 RBR = Receive Buffer   Reg. 
   volatile unsigned thr;	      // Addressbyte 0 THR = Transmit Holding Reg. 
   volatile unsigned dll;       // Addressbyte 0 DLL = Divisor Latch (LS) 
  }reg0; 
 
  union{ 
   volatile unsigned dlh;       // Addressbyte 1 IER = Interrupt Enable Reg. 
   volatile unsigned ier;       // Addressbyte 1 DLM = Divisor Latch (MS)    
  }reg1; 
 
  union{ 
   volatile unsigned iir; 			// Addressbyte 2 IIR = Interrupt Ident  Reg. 
   volatile unsigned fcr;       // Addressbyte 2 FCR = FIFO Control     Reg. 
  }reg2; 
 
  volatile unsigned lcr;		  	// Addressbyte 3 LCR = Line Control     Reg. 
  volatile unsigned mcr;		 		// Addressbyte 4 MCR = Modem Control    Reg. 
  volatile unsigned lsr;		  	// Addressbyte 5 LSR = Line Status      Reg. 
  volatile unsigned msr;        // Addressbyte 6 MSR = Modem Status     Reg. 
  volatile unsigned scr;		  	// Addressbyte 7 SCR = Scratch          reg.    
  volatile unsigned lpdll;
  volatile unsigned lpdlh;
  unsigned char reserved0[8];
  union{ 
    volatile unsigned srbr; 		// Addressbyte 2 IIR = Interrupt Ident  Reg. 
    volatile unsigned sthr;     // Addressbyte 2 FCR = FIFO Control     Reg. 
  }sreg0;
  unsigned char reserved1[0x3c];
  volatile unsigned far;
  volatile unsigned tfr;
  volatile unsigned rfw;
  volatile unsigned usr;
  volatile unsigned tfl;
  volatile unsigned rfl;
  volatile unsigned srr;
  volatile unsigned srts;
  volatile unsigned sbcr;
  volatile unsigned sdmam;
  volatile unsigned srt;
  volatile unsigned stet;
  volatile unsigned htx;
  volatile unsigned dmasa;
  unsigned char reserved2[0x48];
  volatile unsigned cpr;
  volatile unsigned ucv;
  volatile unsigned ctr;
};


/*
 * These are the definitions for the FIFO Control Register
 */
#define UART_FCR_FIFO_EN	0x01 /* Fifo enable */
#define UART_FCR_CLEAR_RCVR	0x02 /* Clear the RCVR FIFO */
#define UART_FCR_CLEAR_XMIT	0x04 /* Clear the XMIT FIFO */
#define UART_FCR_DMA_SELECT	0x08 /* For DMA applications */
#define UART_FCR_TX_EMPTY_TRIGGER_MASK 0x30 /* TX Empty Trigger */
#define UART_FCR_TX_EMPTY_TRIGGER_EMPTY	0x00 /* Mask for trigger FIFO empty */
#define UART_FCR_TX_EMPTY_TRIGGER_TWOCHAR	0x10 /* Mask for trigger 2 char in FIFO */
#define UART_FCR_TX_EMPTY_TRIGGER_QUARTER	0x20 /* Mask for trigger FIFO 1/4 full */
#define UART_FCR_TX_EMPTY_TRIGGER_HALFFULL	0x30 /* Mask for trigger set at 14 */
#define UART_FCR_RX_TRIGGER_MASK	0xC0 /* Mask for the FIFO trigger range */
#define UART_FCR_RX_TRIGGER_ONECHAR	0x00 /* Mask for trigger set at 1 */
#define UART_FCR_RX_TRIGGER_QUARTERFULL	0x40 /* Mask for trigger set at 4 */
#define UART_FCR_RX_TRIGGER_HALFFULL	0x80 /* Mask for trigger set at 8 */
#define UART_FCR_RX_TRIGGER_ALMOSTFULL	0xC0 /* Mask for trigger set at 14 */

#define UART_FCR_RXSR		0x02 /* Receiver soft reset */
#define UART_FCR_TXSR		0x04 /* Transmitter soft reset */

/*
 * These are the definitions for the Modem Control Register
 */
#define UART_MCR_DTR	0x01		/* DTR   */
#define UART_MCR_RTS	0x02		/* RTS   */
#define UART_MCR_OUT1	0x04		/* Out 1 */
#define UART_MCR_OUT2	0x08		/* Out 2 */
#define UART_MCR_LOOP	0x10		/* Enable loopback test mode */

#define UART_MCR_AFCE 0x20    /* Auto Flow Control Enable */
#define UART_MCR_SIRE 0x40    /* SIR Mode Enable */

//#define UART_MCR_DMA_EN	0x04
//#define UART_MCR_TX_DFR	0x08

/*
 * These are the definitions for the Line Control Register
 *
 * Note: if the word length is 5 bits (UART_LCR_WLEN5), then setting
 * UART_LCR_STOP will select 1.5 stop bits, not 2 stop bits.
 */
#define UART_LCR_WLS_MSK 0x03		/* character length select mask */
#define UART_LCR_WLS_5	0x00		/* 5 bit character length */
#define UART_LCR_WLS_6	0x01		/* 6 bit character length */
#define UART_LCR_WLS_7	0x02		/* 7 bit character length */
#define UART_LCR_WLS_8	0x03		/* 8 bit character length */
#define UART_LCR_STB	0x04		/* # stop Bits, off=1, on=1.5 or 2) */
#define UART_LCR_PEN	0x08		/* Parity eneble */
#define UART_LCR_EPS	0x10		/* Even Parity Select */
#define UART_LCR_STKP	0x20		/* Stick Parity */
#define UART_LCR_SBRK	0x40		/* Set Break */
#define UART_LCR_BKSE	0x80		/* Bank select enable */
#define UART_LCR_DLAB	0x80		/* Divisor latch access bit */

/* useful defaults for LCR */
#define UART_LCR_8N1	0x03

/*
 * These are the definitions for the Line Status Register
 */
#define UART_LSR_DR	0x01		/* Data ready */
#define UART_LSR_OE	0x02		/* Overrun */
#define UART_LSR_PE	0x04		/* Parity error */
#define UART_LSR_FE	0x08		/* Framing error */
#define UART_LSR_BI	0x10		/* Break */
#define UART_LSR_THRE	0x20		/* Xmit holding register empty */
#define UART_LSR_TEMT	0x40		/* Xmitter empty */
#define UART_LSR_ERR	0x80		/* Error */

#define UART_MSR_DCD	0x80		/* Data Carrier Detect */
#define UART_MSR_RI	0x40		/* Ring Indicator */
#define UART_MSR_DSR	0x20		/* Data Set Ready */
#define UART_MSR_CTS	0x10		/* Clear to Send */
#define UART_MSR_DDCD	0x08		/* Delta DCD */
#define UART_MSR_TERI	0x04		/* Trailing edge ring indicator */
#define UART_MSR_DDSR	0x02		/* Delta DSR */
#define UART_MSR_DCTS	0x01		/* Delta CTS */

/*
 * These are the definitions for the Interrupt Identification Register
 */
#define UART_IIR_NO_INT	0x01	/* No interrupts pending */
#define UART_IIR_ID	0x06	/* Mask for the interrupt ID */

#define UART_IIR_MSI	   0x00	/* Modem status interrupt */
#define UART_IIR_THRI	 0x02	/* Transmitter holding register empty */
#define UART_IIR_RDI	   0x04	/* Receiver data interrupt */
#define UART_IIR_RLSI	 0x06	/* Receiver line status interrupt */

/*
 * These are the definitions for the Interrupt Enable Register
 */
#define UART_IER_PTIME 0x80 /* Programmable THRE Interrupt Mode Enable */
#define UART_IER_MSI	 0x08	/* Enable Modem status interrupt */
#define UART_IER_EDSSI	UART_IER_MSI
#define UART_IER_RLSI	 0x04	/* Enable receiver line status interrupt */
#define UART_IER_ELSI    UART_IER_RLSI
#define UART_IER_THRI	 0x02	/* Enable Transmitter holding register int. */
#define UART_IER_ETBEI UART_IER_THRI
#define UART_IER_RDI	 0x01	/* Enable receiver data interrupt */
#define UART_IER_ERBFI UART_IER_RDI

void   boot_uart_init(void);
void Uart_Printf(unsigned char *string);

#endif

