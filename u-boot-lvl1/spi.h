#ifndef __SPI_H__
#define __SPI_H__

//#include "ALL_INC.h"

/* SPI接口连接的从机设备个数 */
//#define SSI_NUM_SLAVES 1

/* Tx FIFO和Rx FIFO深度 */
//#define SSI_TX_FIFO_DEPTH	8
//#define SSI_RX_FIFO_DEPTH	8
/*Tx FIFO和Rx FIFO地址总线宽度 : log2(SSI_TX_FIFO_DEPTH)*/
//#define TX_ABW	3
//#define Rx_ABW	3


//Tx FIFO为空
#define Tx_FIFO_EMPTY	      (0x1<<2) 
#define Tx_FIFO_NO_FULL	  (0x1<<1)   /* Transmit FIFO Not Full */

//Rx FIFO为满
#define Rx_FIFO_FULL	            (0x1<<4)
#define Rx_FIFO_NO_EMPTY	   (0x1<<3)

#define Rx_FIFO_CNT   (16)
#define Tx_FIFO_CNT   (16)

//忙状态
#define SSI_BUSY	(0x1<<0)

/* SPI寄存器地址定义
SPI0	  0x020f8000
SPI1	  0x02100000
SPI2	  0x04a00000
SPI3	  0x04a10000
*/
/* SOC use spio0, fpga test use fpga SPI2 */
#ifdef  SOC_PRJ
#define SPI_BASE    0x020f8000      /* SPI0 */
#else
#define SPI_BASE    0x04a00000      /* SPI2 */
#endif

#define CTRLR0 	   (*(volatile unsigned int *)(SPI_BASE+0x00))
#define CTRLR1 	   (*(volatile unsigned int *)(SPI_BASE+0x04))
#define SSIENR 	   (*(volatile unsigned int *)(SPI_BASE+0x08))
#define MWCR       (*(volatile unsigned int *)(SPI_BASE+0x0C))
#define SER        (*(volatile unsigned int *)(SPI_BASE+0x10))
#define BAUDR      (*(volatile unsigned int *)(SPI_BASE+0x14))
#define TXFTLR     (*(volatile unsigned int *)(SPI_BASE+0x18))
#define RXFTLR     (*(volatile unsigned int *)(SPI_BASE+0x1C))
#define TXFLR      (*(volatile unsigned int *)(SPI_BASE+0x20)) 
#define RXFLR      (*(volatile unsigned int *)(SPI_BASE+0x24))
#define SR         (*(volatile unsigned int *)(SPI_BASE+0x28))
#define IMR        (*(volatile unsigned int *)(SPI_BASE+0x2c))
#define ISR        (*(volatile unsigned int *)(SPI_BASE+0x30))
#define RISR       (*(volatile unsigned int *)(SPI_BASE+0x34))
#define TXOICR     (*(volatile unsigned int *)(SPI_BASE+0x38))
#define RXOICR     (*(volatile unsigned int *)(SPI_BASE+0x3c))
#define RXUICR     (*(volatile unsigned int *)(SPI_BASE+0x40))
#define MSTICR     (*(volatile unsigned int *)(SPI_BASE+0x44))
#define ICR        (*(volatile unsigned int *)(SPI_BASE+0x48))
#define DMACR      (*(volatile unsigned int *)(SPI_BASE+0x4c)) 
#define DMATDLR    (*(volatile unsigned int *)(SPI_BASE+0x50))
#define DMARDLR    (*(volatile unsigned int *)(SPI_BASE+0x54))
#define IDR        (*(volatile unsigned int *)(SPI_BASE+0x58))
#define SSI_COMP_VERSION     (*(volatile unsigned int *)(SPI_BASE+0x5c))
#define DR         (*(volatile unsigned int *)(SPI_BASE+0x60))
#define RX_SAMPLE_DLY        (*(volatile unsigned int *)(SPI_BASE+0xf0))
#define RSVD_0     (*(volatile unsigned int *)(SPI_BASE+0xf4))
#define RSVD_1     (*(volatile unsigned int *)(SPI_BASE+0xf8))
#define RSVD_2     (*(volatile unsigned int *)(SPI_BASE+0xfc))


#define  SPI_WRITE     0x8000
#define  SPI_READ       0x0000

#define  SPI_ERROR       0x0
#define  SPI_OK              0x1

#define  PAGE_SIZE        2048
#define  ROW_1GBIT_SIZE        1024
#define  ROW_2GBIT_SIZE        2048
#define  COL_SIZE          64
#define  PAGE_NUM          64

/***********************   SPI 函数声明     ***********************/
void SPI1_Init(void);
//void SPI_Send(unsigned char dat);
//void SPI_Send(unsigned short dat);
//void SPI_write(_uint16_ reg_addr,_uint16_ reg_data);
//unsigned int SPI_Receive(void);
void SPI1_SetSpeed(unsigned char SpeedSet);
unsigned char SPI1_ReadWriteByte(unsigned char);
#endif /*SPI_H_*/
