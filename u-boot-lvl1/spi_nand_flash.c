/*
 * 

 */

#include <string.h>
#include "spi.h"
#include "spi_nand_flash.h"
#include "gpio.h"
#include "sd_common.h"
#include "pinmux.h"

//#define NAND_SPI_ER_STATUS_P_FAIL       (1 << 3)		//写入失败标记
//#define NAND_SPI_ER_STATUS_E_FAIL       (1 << 2)		//擦除失败标记
//#define NAND_SPI_ER_STATUS_WEL          (1 << 1)		//允许写入标记
//#define NAND_SPI_ER_STATUS_OIP          (1 << 0)		//设备忙碌标记

#define    FIFO_LEN    16
 //
//unsigned int gNandFlashType = GD5F2GQ4RB;  
unsigned int  gNandFlashType;
unsigned char  gFlashSize;
unsigned char  gRxDat[2048+128];

#if 0
void drv_delay(volatile unsigned int num)
{

	while(num--);
}
#endif

void  Rx_FIFO_empty(void)
{
	 unsigned int  readDR, i=0;

	 while(SR & (Rx_FIFO_NO_EMPTY|Rx_FIFO_FULL))
	 {
	    readDR = DR;
	    i++;
      if (i>Rx_FIFO_CNT)  
      	  break;
	 }	 		
}


unsigned char rt_spi_send_then_recv(unsigned char *send_buf,
								unsigned int tx_len,
								unsigned char *recv_buf,
								unsigned int rx_len)
{
    unsigned int total, tByte=0,rByte=0;
    unsigned char  *pRxdat;
    unsigned int i;

    total = rx_len+tx_len;
    pRxdat = gRxDat;

#ifdef  SOC_PRJ 
      /* SOC use spio0, spi0_cs =0  */
     spi0_ssn_gpio_set_value(0); 
#else
    /* fpga test use fpga SPI2, spi2_cs =0 */
    spi2_ssn_gpio_set_value(0);
#endif
    
    while( Tx_FIFO_EMPTY != (SR & Tx_FIFO_EMPTY));
    Rx_FIFO_empty();  /* 接收FIFO读空 */
    
    while((tByte<total)||(rByte<total))
    {
           while (( Tx_FIFO_NO_FULL == (SR & Tx_FIFO_NO_FULL))&&(tByte< total))
           //if(( Tx_FIFO_NO_FULL == (SR & Tx_FIFO_NO_FULL))&&(tByte< total))
           {
                 if(tByte< tx_len)
                     DR = (unsigned int)(*send_buf);
                 else
                     DR = 0;
                 send_buf++;
                 tByte++;
           }
  
           if(( Rx_FIFO_NO_EMPTY == (SR & Rx_FIFO_NO_EMPTY))&&(rByte< total))
           {
                *pRxdat = (unsigned char)DR;
                 pRxdat++;
                 rByte++;
           }

      }

#ifdef  SOC_PRJ 
      /* SOC use spio0, spi0_cs =1  */
     spi0_ssn_gpio_set_value(1); 
#else
    /* fpga test use fpga SPI2, spi2_cs =1 */
    spi2_ssn_gpio_set_value(1);
#endif

#if  0
	if(rx_len)
	   memcpy(recv_buf, &gRxDat[tx_len], rx_len);
#else
	 if(rx_len)
	{
		for(i=0;i<rx_len;i++)
			recv_buf[i] = gRxDat[tx_len+i];
	}
#endif

	return 0;
}

void spi_init(void)
{
    RSVD_2 = 4;

	/* diaable  SSI */
	SSIENR = 0x0;		
	/*
	 * TMOD: 00--Transmit & Receive
	 * SCPOL=0,   
	 * SCPH=0, 
	 * FRF=0,   00 –- Motorola SPI
	 */
	//CTRLR0 = 0x07;      /* DFS=0x7, Data Frame size=8bit  */
	CTRLR0 = 0xC7;    
	
	/* Fssi_clk=50MHZ, Fclk_out = Fssi_clk/16 */
	BAUDR = SPI_BAUDR;          /*  50MHZ/200=2.5M, 50MHZ/200=250k */

	//TXFTLR = 0;
	//RXFTLR = 0;
	/*  */
	IMR = 0x3f;
	SR = 0x0;
	SER = 0x1;
	/* DW_apb_ssi */
	SSIENR = 0x1;
}



//读特征字寄存器
//unsigned char reg  要读出的寄存器地址
//unsigned char *data   读出设置寄存器值
unsigned char spi_nand_get_feature(unsigned char reg, unsigned char *data)
{
	unsigned char txbuf[2];
	unsigned char rxbuf;


    txbuf[0] = SPI_NAND_GET_FEATURE_CMD;
    txbuf[1] = reg;
    rt_spi_send_then_recv(txbuf, 2, &rxbuf, 1);
    *data = rxbuf;
    return 0;
}

//读特征字寄存器状态位
//unsigned char *data  返回状态寄存器C0H的值
unsigned char nandflash_busy_wait(unsigned char *data)
{
    int i;
    for (i = 0; i < CHECK_NUM; i++)
    {
        spi_nand_get_feature(0xC0, data);
        if (!(*data & NAND_SPI_ER_STATUS_OIP))
            break;
    }

    if  (i < CHECK_NUM) 
    	return  DRV_OK;
    else 
    	return  WAIT_TIMEOUT;
}


//读取NANDFLASH的ID号
//unsigned char *rxiD   返回的NADNFLASH ID
unsigned char nandflash_readid(unsigned char *RxID)
{
	  unsigned char txbuf[3];
    txbuf[0] = SPI_NAND_READ_ID_CMD;
    txbuf[1] = 0;
    
    rt_spi_send_then_recv(txbuf,2, RxID,2);
    return 0;
}

//设置NANDFLASH锁定参数
unsigned char nandflash_unlock(unsigned char tx_lock)
{
	unsigned char txbuf[3];
    txbuf[0] = SPI_NAND_SET_FEATURE_CMD;
    txbuf[1] = 0xA0;
    txbuf[2] = tx_lock;
    rt_spi_send_then_recv(txbuf,3,txbuf,0);
    return 0;
}

unsigned char  nandflash_read_ecc(void)
{
    unsigned char  eccs;
    	
    spi_nand_get_feature(STAT_STATUS, &eccs);
    eccs  &= 0x30;    
    if (0x20==eccs)
    {
         return ECC_FAILED;
    }

    if (0x0==eccs)
    {
         return ECC_OK;
    }    
    
    return ECC_OK;
}

/*
     src_addr--- flash addr,  
          2Gbit --   src_row_addr = Row<16:0>,  src_col_addr = Col<11:0>=0-2047
          1Gbit --   src_row_addr = Row<15:0>,  src_col_addr = Col<11:0>=0-2047

          Row<16:0> = Row<16:6>  --block addr
                            + Row<5:0>    --page addr
                           
     dst_addr 
     
*/
unsigned char nandflash_read(unsigned int         src_row_addr,
                                                      unsigned int         src_col_addr,
                                                      unsigned char     *dst_addr,
                                                      unsigned int         data_len)
{
     unsigned int  totalBytes=0,nBytes, t_col_addr;
     unsigned int  page, block;
     
     if ((0==data_len)||(src_col_addr>(PAGE_SIZE-1)))
     	    return  PARA_ERROR;

     if ((src_col_addr+data_len) <= PAGE_SIZE)
     	{
           if (DRV_OK != nandflash_readpage(src_row_addr, dst_addr, src_col_addr,   data_len))
              {
                return  ECC_ERROR;
             }
       }
     else
     	{
		    while(totalBytes < data_len )
		    {
            if (0==totalBytes)
               {
                    if (DRV_OK !=  nandflash_readpage(src_row_addr, (unsigned char *)(dst_addr+totalBytes), src_col_addr,   PAGE_SIZE-src_col_addr))
                   {
                      return  ECC_ERROR;
                   }                  
                  totalBytes += 2048-src_col_addr;
               }
		    else
		     {
		    	nBytes = m_min((data_len-totalBytes),PAGE_SIZE);
                if (DRV_OK != nandflash_readpage(src_row_addr, (unsigned char *)(dst_addr+totalBytes), 0,   nBytes))                 
                {
                  return  ECC_ERROR;
                }  
		    	totalBytes += nBytes;
		    }
		    	   
		    page = (src_row_addr & 0x3F);
		    block = (src_row_addr & 0x1FFC0)>>6;             
            block += (page+1)/PAGE_NUM;
            page = (page  +1)& 0x3F;              
            src_row_addr = (block<<6) |page ;
		    }
     	}

    return  DRV_OK;
}


/* *
* @brief从闪存芯片读取一个页面(2048byte)
* @param       page:   page index=0-(2^17-1), RA<16:0>,    24bit addr, 高7bit是0
* @param       *data:  读取数据存放指针
* @param       data_addr:  读flash的地址,     0--2175, A11-A0  有效
* @param       data_len:    读取数据的长度1--2175
* @return       
 */
unsigned char nandflash_readpage(unsigned int                 page,
                                   unsigned char                *data,
                                   unsigned int                data_addr,
                                   unsigned int                data_len)
{
		unsigned char txbuf[5], stat;
		/* Wait等待 */
		nandflash_busy_wait(&stat);
		if (stat & NAND_SPI_ER_STATUS_OIP)
    	  return   WAIT_TIMEOUT;//程度忙退出
			  
		txbuf[0]=SPI_NAND_READ_TO_CACHE_CMD;		//设置13H读取一个页面数据到缓存中
		txbuf[1]=page>>16;							/*  24bit address中的高8bit是0 ？  */
		txbuf[2]=page>>8;             /*  24bit address中的低16bit有效  */
		txbuf[3]=page;
		rt_spi_send_then_recv(txbuf,4,txbuf,0);				//发送读取页面

        //delay tRD=80us
        us_delay(80);
    
		/* Wait等待 */
		nandflash_busy_wait(&stat);
		if (stat & NAND_SPI_ER_STATUS_OIP) 
    	  return WAIT_TIMEOUT;//读取失败退出

   if (nandflash_read_ecc()==ECC_FAILED)
   	{
         return  ECC_ERROR;
    }
    
	txbuf[0]=SPI_NAND_READ_FROM_CACHE2_CMD;
	txbuf[1]=data_addr>>8;
	txbuf[2]=data_addr;
	txbuf[3]=0x00;
	rt_spi_send_then_recv(txbuf,4,data,data_len);
    us_delay(5);
    return  DRV_OK;

}

#if  0
/* WP pin = high level */
void  nandflash_WP_high(void)
{
      boot_gpio_set_value(GPIO_SPI_WP_PIN, 1);

}

/* HOLD pin --output high level  */
void  nandflash_HOLD_high(void)
{
      boot_gpio_set_value(GPIO_SPI_HOLD_PIN, 1);

}
#endif

void nandflash_reset(void)
{
     unsigned char  txbuf[2],val;
     unsigned int  i; 
     
    /* nandflash WP/HOLD pin, must high level*/
	  
    txbuf[0] = SPI_NAND_RESET_CMD;
    rt_spi_send_then_recv(txbuf,1, txbuf,0);

    /* about 500us */
    us_delay(500);
    
    for (i = 0; i < CHECK_NUM; i++)
    {
        us_delay(10);
        spi_nand_get_feature(STAT_STATUS, &val);
        
        if (!(val & NAND_SPI_ER_STATUS_OIP))
            break;
    }  
    
}



int spi_nand_flash_init(void)
{
	   unsigned char rxbuf[4];

       /* SOC use spio0, fpga test use SPI2 */
	   spi_init();	   
	   us_delay(100);
	   nandflash_reset();
	   nandflash_readid(rxbuf);                   //读出NAND FLASH ID号
	   gNandFlashType=(rxbuf[0]<<8)+rxbuf[1];

	   switch   (gNandFlashType)
	   	{
           case   GD5F2GQ4RB:
                     gFlashSize = FLASH_2G_BIT;
                     break;
                     
           case   GD5F1GQ4RB:
                     gFlashSize = FLASH_1G_BIT;
                     break;                     

           default:  
           	           //print error
           	          break;

	   }

	   //nandflash_unlock(0);		//解除锁定

	return 0;
}

