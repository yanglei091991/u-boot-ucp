// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2009
 * Vipin Kumar, ST Micoelectronics, vipin.kumar@st.com.
 */

#include "types.h"
#include "errno.h"

#include "designware_i2c.h"

#define writel(b,addr) ((*(volatile u32 *) (addr)) = (b))
#define readl(addr)		(*(volatile u32 *) (addr))
/*i2c 模块的基地址*/
#define I2C_BASE 0x020f0000
#define       CONFIG_SYS_I2C_SLAVE    0xfe
void udelay(unsigned long usec)/*25M 2us*/
{
	while(usec--);
}
void mdelay(unsigned long msec)
{
        udelay(500 * msec);
}


static int dw_i2c_enable(struct i2c_regs *i2c_base, bool enable)
{
	u32 ena = enable ? IC_ENABLE_0B : 0;
	int timeout = 100;

	do {
		writel(ena, &i2c_base->ic_enable);
		if ((readl(&i2c_base->ic_enable_status) & IC_ENABLE_0B) == ena)
			return 0;

		/*
		 * Wait 10 times the signaling period of the highest I2C
		 * transfer supported by the driver (for 400KHz this is
		 * 25us) as described in the DesignWare I2C databook.
		 */
		udelay(25);
	} while (timeout--);

	return -ETIMEDOUT;
}

/*
 * i2c_set_bus_speed - Set the i2c speed
 * @speed:	required i2c speed
 *
 * Set the i2c speed.
 */
 
static unsigned int __dw_i2c_set_bus_speed(struct i2c_regs *i2c_base)
{
	unsigned int cntl;
	unsigned int hcnt, lcnt;
	
	/* to set speed cltr must be disabled */
	dw_i2c_enable(i2c_base, false);

	cntl = (readl(&i2c_base->ic_con) & (~IC_CON_SPD_MSK));

	cntl |= IC_CON_SPD_SS;

	hcnt = (IC_CLK * MIN_SS_SCL_HIGHTIME) / NANO_TO_MICRO;
	lcnt = (IC_CLK * MIN_SS_SCL_LOWTIME) / NANO_TO_MICRO;

	writel(hcnt, &i2c_base->ic_ss_scl_hcnt);
	writel(lcnt, &i2c_base->ic_ss_scl_lcnt);

	writel(cntl, &i2c_base->ic_con);



	/* Enable back i2c now speed set */
	dw_i2c_enable(i2c_base, true);

	return 0;
}

/*
 * i2c_setaddress - Sets the target slave address
 * @i2c_addr:	target i2c address
 *
 * Sets the target slave address.
 */
static void i2c_setaddress(struct i2c_regs *i2c_base, unsigned int i2c_addr)
{
	/* Disable i2c */
	dw_i2c_enable(i2c_base, false);

	writel(i2c_addr, &i2c_base->ic_tar);

	/* Enable i2c */
	dw_i2c_enable(i2c_base, true);
}

/*
 * i2c_flush_rxfifo - Flushes the i2c RX FIFO
 *
 * Flushes the i2c RX FIFO
 */
static void i2c_flush_rxfifo(struct i2c_regs *i2c_base)
{
	while (readl(&i2c_base->ic_status) & IC_STATUS_RFNE)
		readl(&i2c_base->ic_cmd_data);
}

/*
 * i2c_wait_for_bb - Waits for bus busy
 *
 * Waits for bus busy
 */
static int i2c_wait_for_bb(struct i2c_regs *i2c_base)
{
	while ((readl(&i2c_base->ic_status) & IC_STATUS_MA) ||
	       !(readl(&i2c_base->ic_status) & IC_STATUS_TFE)) {
	}

	return 0;
}

static int i2c_xfer_init(struct i2c_regs *i2c_base, uchar chip, uint addr,
			 int alen)
{
	i2c_wait_for_bb(i2c_base);


	i2c_setaddress(i2c_base, chip);
	while (alen) {
		alen--;
		/* high byte address going out first */
		writel((addr >> (alen * 8)) & 0xff,
		       &i2c_base->ic_cmd_data);
	}
	return 0;
}

static int i2c_xfer_finish(struct i2c_regs *i2c_base)
{
	
	while (1) {
		if ((readl(&i2c_base->ic_raw_intr_stat) & IC_STOP_DET)) {
			readl(&i2c_base->ic_clr_stop_det);
			break;
		}
	}

	i2c_wait_for_bb(i2c_base);


	i2c_flush_rxfifo(i2c_base);

	return 0;
}

/*
 * i2c_read - Read from i2c memory
 * @chip:	target i2c address
 * @addr:	address to read from
 * @alen:
 * @buffer:	buffer for read data
 * @len:	no of bytes to be read
 *
 * Read from i2c memory.
 */
static int __dw_i2c_read(struct i2c_regs *i2c_base, u8 dev, uint addr,
			 int alen, u8 *buffer, int len)
{
	unsigned int active = 0;

	i2c_xfer_init(i2c_base, dev, addr, alen);

	while (len) {
		if (!active) {
			/*
			 * Avoid writing to ic_cmd_data multiple times
			 * in case this loop spins too quickly and the
			 * ic_status RFNE bit isn't set after the first
			 * write. Subsequent writes to ic_cmd_data can
			 * trigger spurious i2c transfer.
			 */
			if (len == 1)
				writel(IC_CMD | IC_STOP, &i2c_base->ic_cmd_data);
			else
				writel(IC_CMD, &i2c_base->ic_cmd_data);
			active = 1;
		}

		if (readl(&i2c_base->ic_status) & IC_STATUS_RFNE) {
			*buffer++ = (uchar)readl(&i2c_base->ic_cmd_data);
			len--;
			active = 0;
		}
	}

	return i2c_xfer_finish(i2c_base);
}

/*
 * i2c_write - Write to i2c memory
 * @chip:	target i2c address
 * @addr:	address to read from
 * @alen:
 * @buffer:	buffer for read data
 * @len:	no of bytes to be read
 *
 * Write to i2c memory.
 */
static int __dw_i2c_write(struct i2c_regs *i2c_base, u8 dev, uint addr,
			  int alen, u8 *buffer, int len)
{
	int nb = len;

	i2c_xfer_init(i2c_base, dev, addr, alen);


	while (len) {
		if (readl(&i2c_base->ic_status) & IC_STATUS_TFNF) {
			if (--len == 0) {
				writel(*buffer | IC_STOP,
				       &i2c_base->ic_cmd_data);
			} else {
				writel(*buffer, &i2c_base->ic_cmd_data);
			}
			buffer++;

		}
	}

	return i2c_xfer_finish(i2c_base);
}

/*
 * __dw_i2c_init - Init function
 * @speed:	required i2c speed
 * @slaveaddr:	slave address for the device
 *
 * Initialization function.
 */
static int __dw_i2c_init(struct i2c_regs *i2c_base)
{
	int ret;

	/* Disable i2c */
	ret = dw_i2c_enable(i2c_base, false);
	if (ret)
		return ret;

	writel(IC_CON_SD | IC_CON_RE | IC_CON_SPD_FS | IC_CON_MM,
	       &i2c_base->ic_con);
	writel(IC_RX_TL, &i2c_base->ic_rx_tl);
	writel(IC_TX_TL, &i2c_base->ic_tx_tl);
	writel(IC_STOP_DET, &i2c_base->ic_intr_mask);
	__dw_i2c_set_bus_speed(i2c_base);
	writel(CONFIG_SYS_I2C_SLAVE, &i2c_base->ic_sar);

	/* Enable i2c */
	ret = dw_i2c_enable(i2c_base, true);
	if (ret)
		return ret;

	return 0;
}


u8 designware_i2c_test(void)
{
	u8 dev;
	short unsigned int  addr;
	int alen;
	/*写一个字节，内容为0x55*/
	u8 tx_buffer=0x77;
	/*读一个字节*/
	u8 rx_buffer=0;
	/*写一个字节，长度为1*/
	int len =1;

	/*1010 A2 A17 A16 W  :A2=0(接地) A17=0 A16=0 W=0, 故为0x60*/
	dev = 0x53; 
	/*对0 地址写*/
	addr = 0x0000;
	/*一共有18位用作标识地址，其中A17 A16划入Device Address Byte ，剩下2个字节划入 First Word Address Byte
	与 Second Word Address Byte*/
	alen = 2;

	__dw_i2c_init((struct i2c_regs *)I2C_BASE);
	
	while(1)
	{
		tx_buffer++;
		
		__dw_i2c_write((struct i2c_regs *)I2C_BASE, dev,  addr, alen, &tx_buffer, 1);
		mdelay(5);
		__dw_i2c_read((struct i2c_regs *)I2C_BASE, dev, addr, alen, &rx_buffer, 1);
		addr++;
		if((rx_buffer != tx_buffer) || (65535 == addr))
		{
			return -1;	
		}
	}
	return 0;
}


void testfromeda(struct i2c_regs *i2c_base)
{
	u32 tmp;
	
//	I2C_IC_ENABLE=0;
	writel(0, &i2c_base->ic_enable);
//	I2C_IC_CON=(bit6|bit5|bit4|bit2|bit1|bit0)|I2C_IC_CON)&0xffeb;
	tmp = readl(&i2c_base->ic_con);
	tmp |= IC_CON_SD |IC_CON_RE| IC_CON_10BITADDRMASTER |IC_CON_SPD_FS|IC_CON_SPD_SS|IC_CON_MM;
	tmp &=0xffeb;
	writel(tmp, &i2c_base->ic_con);
	
	writel(200, &i2c_base->ic_ss_scl_hcnt);
	writel(235, &i2c_base->ic_ss_scl_lcnt);

//	I2C_IC_RESET=0x1e;
	writel(0x1e, &i2c_base->ic_sda_hold);
	
//	I2C_IC_TAR=0xf;
	writel(0x0f, &i2c_base->ic_tar);
	
//	I2C_IC_RX_TL=0xf;
	writel(0xf, &i2c_base->ic_rx_tl);
//	I2C_IC_TX_TL=0x13;
	writel(0x13, &i2c_base->ic_tx_tl);
//	I2C_IC_DMA_CR=0;
	
//	I2C_IC_ENABLE =1;
	writel(1, &i2c_base->ic_enable);
	
//	I2C_IC_DATA_CMD =0x1;
	writel(0x1, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0x2, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0x3, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0x4, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0x5, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0x6, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0x7, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0x8, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0x9, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0xa, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0xb, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0xc, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0xd, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0xe, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0xf, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0x10, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0x11, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0x12, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0x13|IC_STOP, &i2c_base->ic_cmd_data);
while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);
	writel(0x14, &i2c_base->ic_cmd_data);

//	while((I2C_IC_RAW_INTR_STA & bit4)==1);
//	while ((readl(&i2c_base->ic_raw_intr_stat) & IC_TX_EMPTY)==0);



//	while(I2C_IC_STATUS & bit2 ==0);
	while ((readl(&i2c_base->ic_status) & IC_STATUS_TFE == 0));
//	while(I2C_IC_STATUS &bit5 !=0);
	while ((readl(&i2c_base->ic_status) & IC_STATUS_MA != 0));
	

}

u8 designware_i2c_test1(void)
{
	designware_i2c_test();
}

