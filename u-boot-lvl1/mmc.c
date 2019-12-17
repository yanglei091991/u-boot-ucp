// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2008, Freescale Semiconductor, Inc
 * Andy Fleming
 *
 * Based vaguely on the Linux code
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errno.h"
#include "mmc.h"
#include "sd_common.h"



static int mmc_set_signal_voltage(struct mmc *mmc, uint signal_voltage);
static int mmc_power_cycle(struct mmc *mmc);
static int mmc_select_mode_and_width(struct mmc *mmc, uint card_caps);


void Uart_Printf(unsigned char *string);
unsigned int sd_detect(void);

int board_mmc_getwp(struct mmc *mmc)
{
	return -1;
}


int mmc_getwp(struct mmc *mmc)
{
	int wp;

	wp = board_mmc_getwp(mmc);

	if (wp < 0) {
		if (mmc->cfg->ops->getwp)
			wp = mmc->cfg->ops->getwp(mmc);
		else
			wp = 0;
	}

	return wp;
}

int board_mmc_getcd(struct mmc *mmc)
{
	return 1;
}

const char *mmc_mode_name(enum bus_mode mode)
{
	static const char *const names[] = {
	      [MMC_LEGACY]	= "MMC legacy",
	      [SD_LEGACY]	= "SD Legacy",
	      [MMC_HS]		= "MMC High Speed (26MHz)",
	      [SD_HS]		= "SD High Speed (50MHz)",
	      [UHS_SDR12]	= "UHS SDR12 (25MHz)",
	      [UHS_SDR25]	= "UHS SDR25 (50MHz)",
	      [UHS_SDR50]	= "UHS SDR50 (100MHz)",
	      [UHS_SDR104]	= "UHS SDR104 (208MHz)",
	      [UHS_DDR50]	= "UHS DDR50 (50MHz)",
	      [MMC_HS_52]	= "MMC High Speed (52MHz)",
	      [MMC_DDR_52]	= "MMC DDR52 (52MHz)",
	      [MMC_HS_200]	= "HS200 (200MHz)",
	      [MMC_HS_400]	= "HS400 (200MHz)",
	};

	if (mode >= MMC_MODES_END)
		return "Unknown mode";
	else
		return names[mode];
}

static uint mmc_mode2freq(struct mmc *mmc, enum bus_mode mode)
{
	static const int freqs[] = {
	      [MMC_LEGACY]	= 25000000,
	      [SD_LEGACY]	= 25000000,
	      [MMC_HS]		= 26000000,
	      [SD_HS]		= 50000000,
	      [MMC_HS_52]	= 52000000,
	      [MMC_DDR_52]	= 52000000,
	      [UHS_SDR12]	= 25000000,
	      [UHS_SDR25]	= 50000000,
	      [UHS_SDR50]	= 100000000,
	      [UHS_DDR50]	= 50000000,
	      [UHS_SDR104]	= 208000000,
	      [MMC_HS_200]	= 200000000,
	      [MMC_HS_400]	= 200000000,
	};

	if (mode == MMC_LEGACY)
		return mmc->legacy_speed;
	else if (mode >= MMC_MODES_END)
		return 0;
	else
		return freqs[mode];
}

/* 根据SD卡种类选择总线模式  */
static int mmc_select_mode(struct mmc *mmc, enum bus_mode mode)
{
	mmc->selected_mode = mode;

	/* 根据SD卡种类选择传输速度, DDR mode */
	/* mode = MMC_LEGACY,	tran_speed= 25M  
	   mode = SD_LEGACY ,	tran_speed= 25M    */
	mmc->tran_speed = mmc_mode2freq(mmc, mode);
	mmc->ddr_mode = mmc_is_mode_ddr(mode);

	return 0;
}

int mmc_send_cmd(struct mmc *mmc, struct mmc_cmd *cmd, struct mmc_data *data)
{
	int ret;

	ret = mmc->cfg->ops->send_cmd(mmc, cmd, data);

	return ret;
}


int mmc_send_status(struct mmc *mmc, int timeout)
{
	struct mmc_cmd cmd;
	int err, retries = 5;

	cmd.cmdidx = MMC_CMD_SEND_STATUS;
	cmd.resp_type = MMC_RSP_R1;
	if (!mmc_host_is_spi(mmc))
		cmd.cmdarg = mmc->rca << 16;

	while (1) {
		err = mmc_send_cmd(mmc, &cmd, NULL);
		if (!err) {
			if ((cmd.response[0] & MMC_STATUS_RDY_FOR_DATA) &&
			    (cmd.response[0] & MMC_STATUS_CURR_STATE) !=
			     MMC_STATE_PRG)
				break;

			if (cmd.response[0] & MMC_STATUS_MASK) {

				return -ECOMM;
			}
		} else if (--retries < 0)
			return err;

		if (timeout-- <= 0)
			break;

		us_delay(1000);
	}

	mmc_trace_state(mmc, &cmd);
	if (timeout <= 0) {
		return -ETIMEDOUT;
	}

	return 0;
}

int mmc_set_blocklen(struct mmc *mmc, int len)
{
	struct mmc_cmd cmd;
	int err;

	if (mmc->ddr_mode)
		return 0;

	cmd.cmdidx = MMC_CMD_SET_BLOCKLEN;
	cmd.resp_type = MMC_RSP_R1;
	cmd.cmdarg = len;

	err = mmc_send_cmd(mmc, &cmd, NULL);

#ifdef CONFIG_MMC_QUIRKS
	if (err && (mmc->quirks & MMC_QUIRK_RETRY_SET_BLOCKLEN)) {
		int retries = 4;
		/*
		 * It has been seen that SET_BLOCKLEN may fail on the first
		 * attempt, let's try a few more time
		 */
		do {
			err = mmc_send_cmd(mmc, &cmd, NULL);
			if (!err)
				break;
		} while (retries--);
	}
#endif

	return err;
}

int mmc_read_blocks(struct mmc *mmc, void *dst, unsigned int start,
			   unsigned int blkcnt)
{
	struct mmc_cmd cmd;
	struct mmc_data data;

	if (blkcnt > 1)
		cmd.cmdidx = MMC_CMD_READ_MULTIPLE_BLOCK;
	else
		cmd.cmdidx = MMC_CMD_READ_SINGLE_BLOCK;

	if (mmc->high_capacity)
		cmd.cmdarg = start;
	else
		cmd.cmdarg = start * mmc->read_bl_len;

	cmd.resp_type = MMC_RSP_R1;

	data.dest = dst;
	data.blocks = blkcnt;
	data.blocksize = mmc->read_bl_len;
	data.flags = MMC_DATA_READ;

	if (mmc_send_cmd(mmc, &cmd, &data))
		return 0;

	if (blkcnt > 1) {
		cmd.cmdidx = MMC_CMD_STOP_TRANSMISSION;
		cmd.cmdarg = 0;
		cmd.resp_type = MMC_RSP_R1b;
		if (mmc_send_cmd(mmc, &cmd, NULL)) {
			return 0;
		}
	}

	return blkcnt;
}



static int mmc_go_idle(struct mmc *mmc)
{
	struct mmc_cmd cmd;
	int err;

	us_delay(1000);

	cmd.cmdidx = MMC_CMD_GO_IDLE_STATE;
	cmd.cmdarg = 0;
	cmd.resp_type = MMC_RSP_NONE;

	err = mmc_send_cmd(mmc, &cmd, NULL);

	if (err)
		return err;

	us_delay(2000);

	return 0;
}

static int sd_send_op_cond(struct mmc *mmc, bool uhs_en)
{
	int timeout = 1000;
	int err;
	struct mmc_cmd cmd;

	while (1) {
		cmd.cmdidx = MMC_CMD_APP_CMD;
		cmd.resp_type = MMC_RSP_R1;
		cmd.cmdarg = 0;

		err = mmc_send_cmd(mmc, &cmd, NULL);

		if (err)
			return err;

		cmd.cmdidx = SD_CMD_APP_SEND_OP_COND;
		cmd.resp_type = MMC_RSP_R3;

		/*
		 * Most cards do not answer if some reserved bits
		 * in the ocr are set. However, Some controller
		 * can set bit 7 (reserved for low voltages), but
		 * how to manage low voltages SD card is not yet
		 * specified.
		 */
		cmd.cmdarg = mmc_host_is_spi(mmc) ? 0 :
			(mmc->cfg->voltages & 0xff8000);

		if (mmc->version == SD_VERSION_2)
			cmd.cmdarg |= OCR_HCS;

		if (uhs_en)
			cmd.cmdarg |= OCR_S18R;

		err = mmc_send_cmd(mmc, &cmd, NULL);

		if (err)
			return err;

		if (cmd.response[0] & OCR_BUSY)
			break;

		if (timeout-- <= 0)
			return -EOPNOTSUPP;

		us_delay(1000);
	}

	if (mmc->version != SD_VERSION_2)
		mmc->version = SD_VERSION_1_0;

	mmc->ocr = cmd.response[0];
	mmc->high_capacity = ((mmc->ocr & OCR_HCS) == OCR_HCS);
	mmc->rca = 0;

	return 0;
}

static int mmc_send_op_cond_iter(struct mmc *mmc, int use_arg)
{
	struct mmc_cmd cmd;
	int err;

	cmd.cmdidx = MMC_CMD_SEND_OP_COND;
	cmd.resp_type = MMC_RSP_R3;
	cmd.cmdarg = 0;
	if (use_arg && !mmc_host_is_spi(mmc))
		cmd.cmdarg = OCR_HCS |
			(mmc->cfg->voltages &
			(mmc->ocr & OCR_VOLTAGE_MASK)) |
			(mmc->ocr & OCR_ACCESS_MODE);

	err = mmc_send_cmd(mmc, &cmd, NULL);
	if (err)
		return err;
	mmc->ocr = cmd.response[0];
	return 0;
}

static int mmc_send_op_cond(struct mmc *mmc)
{
	int err, i;

	/* Some cards seem to need this */
	mmc_go_idle(mmc);

 	/* Asking to the card its capabilities */
	for (i = 0; i < 2; i++) {
		err = mmc_send_op_cond_iter(mmc, i != 0);
		if (err)
			return err;

		/* exit if not busy (flag seems to be inverted) */
		if (mmc->ocr & OCR_BUSY)
			break;
	}
	mmc->op_cond_pending = 1;
	return 0;
}

static int mmc_complete_op_cond(struct mmc *mmc)
{
	struct mmc_cmd cmd;
	int timeout = 1000;
	ulong start;
	int err;

	mmc->op_cond_pending = 0;
	if (!(mmc->ocr & OCR_BUSY)) {
		/* Some cards seem to need this */
		mmc_go_idle(mmc);

		start = get_timer(0);
		while (1) {
			err = mmc_send_op_cond_iter(mmc, 1);
			if (err)
				return err;
			if (mmc->ocr & OCR_BUSY)
				break;
			if (get_timer(start) > timeout)
				return -EOPNOTSUPP;
			us_delay(100);
		}
	}

	mmc->version = MMC_VERSION_UNKNOWN;

	mmc->high_capacity = ((mmc->ocr & OCR_HCS) == OCR_HCS);
	mmc->rca = 1;

	return 0;
}


static int mmc_send_ext_csd(struct mmc *mmc, u8 *ext_csd)
{
	struct mmc_cmd cmd;
	struct mmc_data data;
	int err;

	/* Get the Card Status Register */
	cmd.cmdidx = MMC_CMD_SEND_EXT_CSD;
	cmd.resp_type = MMC_RSP_R1;
	cmd.cmdarg = 0;

	data.dest = (char *)ext_csd;
	data.blocks = 1;
	data.blocksize = MMC_MAX_BLOCK_LEN;
	data.flags = MMC_DATA_READ;

	err = mmc_send_cmd(mmc, &cmd, &data);

	return err;
}

int mmc_switch(struct mmc *mmc, u8 set, u8 index, u8 value)
{
	struct mmc_cmd cmd;
	int timeout = 1000;
	int retries = 3;
	int ret;

	cmd.cmdidx = MMC_CMD_SWITCH;
	cmd.resp_type = MMC_RSP_R1b;
	cmd.cmdarg = (MMC_SWITCH_MODE_WRITE_BYTE << 24) |
				 (index << 16) |
				 (value << 8);

	while (retries > 0) {
		ret = mmc_send_cmd(mmc, &cmd, NULL);

		/* Waiting for the ready status */
		if (!ret) {
			ret = mmc_send_status(mmc, timeout);
			return ret;
		}

		retries--;
	}

	return ret;

}


static int mmc_set_card_speed(struct mmc *mmc, enum bus_mode mode)
{
	int err;
	int speed_bits;

	ALLOC_CACHE_ALIGN_BUFFER(u8, test_csd, MMC_MAX_BLOCK_LEN);

	switch (mode) {
	case MMC_HS:
	case MMC_HS_52:
	case MMC_DDR_52:
		speed_bits = EXT_CSD_TIMING_HS;
		break;
	case MMC_LEGACY:
		speed_bits = EXT_CSD_TIMING_LEGACY;
		break;
	default:
		return -EINVAL;
	}
	err = mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_HS_TIMING,
			 speed_bits);
	if (err)
		return err;

	if ((mode == MMC_HS) || (mode == MMC_HS_52)) {
		/* Now check to see that it worked */
		err = mmc_send_ext_csd(mmc, test_csd);
		if (err)
			return err;

		/* No high-speed support */
		if (!test_csd[EXT_CSD_HS_TIMING])
			return -ENOTSUPP;
	}

	return 0;
}

static int mmc_get_capabilities(struct mmc *mmc)
{
	u8 *ext_csd = mmc->ext_csd;
	char cardtype;

	mmc->card_caps = MMC_MODE_1BIT | MMC_CAP(MMC_LEGACY);

	if (mmc_host_is_spi(mmc))
		return 0;

	/* Only version 4 supports high-speed */
	if (mmc->version < MMC_VERSION_4)
		return 0;

	if (!ext_csd) {
		return -ENOTSUPP;
	}

	mmc->card_caps |= MMC_MODE_4BIT | MMC_MODE_8BIT;

	cardtype = ext_csd[EXT_CSD_CARD_TYPE];
	mmc->cardtype = cardtype;

	if (cardtype & EXT_CSD_CARD_TYPE_52) {
		if (cardtype & EXT_CSD_CARD_TYPE_DDR_52)
			mmc->card_caps |= MMC_MODE_DDR_52MHz;
		mmc->card_caps |= MMC_MODE_HS_52MHz;
	}
	if (cardtype & EXT_CSD_CARD_TYPE_26)
		mmc->card_caps |= MMC_MODE_HS;

	return 0;
}


static int mmc_set_capacity(struct mmc *mmc, int part_num)
{
	switch (part_num) {
	case 0:
		mmc->capacity = mmc->capacity_user;
		break;
	case 1:
	case 2:
		mmc->capacity = mmc->capacity_boot;
		break;
	case 3:
		mmc->capacity = mmc->capacity_rpmb;
		break;
	case 4:
	case 5:
	case 6:
	case 7:
		mmc->capacity = mmc->capacity_gp[part_num - 4];
		break;
	default:
		return -1;
	}

	return 0;
}

static inline int mmc_boot_part_access_chk(struct mmc *mmc,
					   unsigned int part_num)
{
	return 0;
}

int mmc_switch_part(struct mmc *mmc, unsigned int part_num)
{
	int ret;

	ret = mmc_boot_part_access_chk(mmc, part_num);
	if (ret)
		return ret;

	ret = mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_PART_CONF,
			 (mmc->part_config & ~PART_ACCESS_MASK)
			 | (part_num & PART_ACCESS_MASK));

	/*
	 * Set the capacity if the switch succeeded or was intended
	 * to return to representing the raw device.
	 */
	if ((ret == 0) || ((ret == -ENODEV) && (part_num == 0))) {
		ret = mmc_set_capacity(mmc, part_num);
		//mmc_get_blk_desc(mmc)->hwpart = part_num;
	}

	return ret;
}

int mmc_getcd(struct mmc *mmc)
{
	int cd;

	cd = board_mmc_getcd(mmc);
	return cd;
}

/* SD卡速度切换 */
static int sd_switch(struct mmc *mmc, int mode, int group, u8 value, u8 *resp)
{
	struct mmc_cmd cmd;
	struct mmc_data data;

	/* Switch the frequency */
	cmd.cmdidx = SD_CMD_SWITCH_FUNC;
	cmd.resp_type = MMC_RSP_R1;
	cmd.cmdarg = (mode << 31) | 0xffffff;
	cmd.cmdarg &= ~(0xf << (group * 4));
	cmd.cmdarg |= value << (group * 4);

	data.dest = (char *)resp;
	data.blocksize = 64;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;

	return mmc_send_cmd(mmc, &cmd, &data);
}
/* 读SCR 寄存器, 并check是否支持速度切换 */
static int sd_get_capabilities(struct mmc *mmc)
{
	int err;
	struct mmc_cmd cmd;
	//ALLOC_CACHE_ALIGN_BUFFER(__be32, scr, 2);
	//ALLOC_CACHE_ALIGN_BUFFER(__be32, switch_status, 16);

	ALLOC_CACHE_ALIGN_BUFFER(u32, scr, 2);
	ALLOC_CACHE_ALIGN_BUFFER(u32, switch_status, 16);

	
	struct mmc_data data;
	int timeout;

	mmc->card_caps = MMC_MODE_1BIT | MMC_CAP(SD_LEGACY);

	/* Read the SCR to find out if this card supports higher speeds */
	cmd.cmdidx = MMC_CMD_APP_CMD;
	cmd.resp_type = MMC_RSP_R1;
	cmd.cmdarg = mmc->rca << 16;

	err = mmc_send_cmd(mmc, &cmd, NULL);

	if (err)
		return err;

	cmd.cmdidx = SD_CMD_APP_SEND_SCR;
	cmd.resp_type = MMC_RSP_R1;
	cmd.cmdarg = 0;

	timeout = 3;

retry_scr:
	data.dest = (char *)scr;
	data.blocksize = 8;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;

	err = mmc_send_cmd(mmc, &cmd, &data);

	if (err) {
		if (timeout--)
			goto retry_scr;

		return err;
	}

	//mmc->scr[0] = __be32_to_cpu(scr[0]);
	//mmc->scr[1] = __be32_to_cpu(scr[1]);   uswap_32
	mmc->scr[0] = uswap_32(scr[0]);
	mmc->scr[1] = uswap_32(scr[1]);
	
	switch ((mmc->scr[0] >> 24) & 0xf) {
	case 0:
		mmc->version = SD_VERSION_1_0;
		break;
	case 1:
		mmc->version = SD_VERSION_1_10;
		break;
	case 2:
		mmc->version = SD_VERSION_2;
		if ((mmc->scr[0] >> 15) & 0x1)
			mmc->version = SD_VERSION_3; 
		break;
	default:
		mmc->version = SD_VERSION_1_0;
		break;
	}

	if (mmc->scr[0] & SD_DATA_4BIT)
		mmc->card_caps |= MMC_MODE_4BIT;

	/* Version 1.0 doesn't support switching */
	if (mmc->version == SD_VERSION_1_0)
		return 0;

	timeout = 4;
	while (timeout--) {
		err = sd_switch(mmc, SD_SWITCH_CHECK, 0, 1,
				(u8 *)switch_status);

		if (err)
			return err;

		/* The high-speed function is busy.  Try again */
		//if (!(__be32_to_cpu(switch_status[7]) & SD_HIGHSPEED_BUSY))
		if (!(uswap_32(switch_status[7]) & SD_HIGHSPEED_BUSY))
			break;
	}

	/* If high-speed isn't supported, we return */
	//if (__be32_to_cpu(switch_status[3]) & SD_HIGHSPEED_SUPPORTED)
	if (uswap_32(switch_status[3]) & SD_HIGHSPEED_SUPPORTED)
		mmc->card_caps |= MMC_CAP(SD_HS);

	return 0;
}

static int sd_set_card_speed(struct mmc *mmc, enum bus_mode mode)
{
	int err;

	ALLOC_CACHE_ALIGN_BUFFER(uint, switch_status, 16);
	int speed;

	switch (mode) {
	case SD_LEGACY:
		speed = UHS_SDR12_BUS_SPEED;
		break;
	case SD_HS:
		speed = HIGH_SPEED_BUS_SPEED;
		break;
	default:
		return -EINVAL;
	}

	err = sd_switch(mmc, SD_SWITCH_SWITCH, 0, speed, (u8 *)switch_status);
	if (err)
		return err;

	if (((uswap_32(switch_status[4]) >> 24) & 0xF) != speed)
		return -ENOTSUPP;

	return 0;
}

static int sd_select_bus_width(struct mmc *mmc, int w)
{
	int err;
	struct mmc_cmd cmd;

	if ((w != 4) && (w != 1))
		return -EINVAL;

	cmd.cmdidx = MMC_CMD_APP_CMD;
	cmd.resp_type = MMC_RSP_R1;
	cmd.cmdarg = mmc->rca << 16;

	err = mmc_send_cmd(mmc, &cmd, NULL);
	if (err)
		return err;

	cmd.cmdidx = SD_CMD_APP_SET_BUS_WIDTH;
	cmd.resp_type = MMC_RSP_R1;
	if (w == 4)
		cmd.cmdarg = 2;
	else if (w == 1)
		cmd.cmdarg = 0;
	err = mmc_send_cmd(mmc, &cmd, NULL);
	if (err)
		return err;

	return 0;
}



/* frequency bases */
/* divided by 10 to be nice to platforms without floating point */
static const int fbase[] = {
	10000,       /* 10k */
	100000,      /* 100k */
	1000000,     /* 1M */
	10000000,    /* 10M */
};

/* Multiplier values for TRAN_SPEED.  Multiplied by 10 to be nice
 * to platforms without floating point.
 */
static const u8 multipliers[] = {
	0,	/* reserved */
	10,
	12,
	13,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	70,
	80,
};

static inline int bus_width(uint cap)
{
	if (cap == MMC_MODE_8BIT)
		return 8;
	if (cap == MMC_MODE_4BIT)
		return 4;
	if (cap == MMC_MODE_1BIT)
		return 1;
	return 0;
}

/*
  MMC_CLK_DISABLE =1
  MMC_CLK_ENABLE  =0
*/
int mmc_set_clock(struct mmc *mmc, uint clock, bool disable)
{
	if (!disable) {
		if (clock > mmc->cfg->f_max)
			clock = mmc->cfg->f_max;

		if (clock < mmc->cfg->f_min)
			clock = mmc->cfg->f_min;
	}

	mmc->clock = clock;
	mmc->clk_disable = disable;

	return dwmci_set_ios(mmc);
}

static int mmc_set_bus_width(struct mmc *mmc, uint width)
{
	mmc->bus_width = width;

	return dwmci_set_ios(mmc);
}


struct mode_width_tuning {
	enum bus_mode mode;
	uint widths;
};

static inline int mmc_set_signal_voltage(struct mmc *mmc, uint signal_voltage)
{
	return 0;
}


static const struct mode_width_tuning sd_modes_by_pref[] = {
	{
		.mode = SD_HS,
		.widths = MMC_MODE_4BIT | MMC_MODE_1BIT,
	},
	
	{
		.mode = SD_LEGACY,
		.widths = MMC_MODE_4BIT | MMC_MODE_1BIT,
	}
};

#define for_each_sd_mode_by_pref(caps, mwt) \
	for (mwt = sd_modes_by_pref;\
	     mwt < sd_modes_by_pref + ARRAY_SIZE(sd_modes_by_pref);\
	     mwt++) \
		if (caps & MMC_CAP(mwt->mode))

/* 配置sd card和host的总线宽度和速度 */
static int sd_select_mode_and_width(struct mmc *mmc, uint card_caps)
{
	int err;
	uint widths[] = {MMC_MODE_4BIT, MMC_MODE_1BIT};
	const struct mode_width_tuning *mwt;	
	bool uhs_en = false;
	uint caps;

	/* Restrict card's capabilities by what the host can do */
	caps = card_caps & mmc->host_caps;

	if (!uhs_en)
		caps &= ~UHS_CAPS;

	for_each_sd_mode_by_pref(caps, mwt) {
		uint *w;

		for (w = widths; w < widths + ARRAY_SIZE(widths); w++) {
			if (*w & caps & mwt->widths) {

				/* configure the bus width (card + host) */
				err = sd_select_bus_width(mmc, bus_width(*w));
				if (err)
					goto error;
				mmc_set_bus_width(mmc, bus_width(*w));

				/* configure the bus mode (card) */
				err = sd_set_card_speed(mmc, mwt->mode);
				if (err)
					goto error;

				/* configure the bus mode (host) */
				mmc_select_mode(mmc, mwt->mode);
				mmc_set_clock(mmc, mmc->tran_speed,
						MMC_CLK_ENABLE);

				if (!err)
					return 0;

error:
				/* revert to a safer bus speed */
				mmc_select_mode(mmc, SD_LEGACY);
				mmc_set_clock(mmc, mmc->tran_speed,
						MMC_CLK_ENABLE);
			}
		}
	}

	return -ENOTSUPP;
}

/*
 * read the compare the part of ext csd that is constant.
 * This can be used to check that the transfer is working
 * as expected.
 */
static int mmc_read_and_compare_ext_csd(struct mmc *mmc)
{
	int err;
	const u8 *ext_csd = mmc->ext_csd;
	ALLOC_CACHE_ALIGN_BUFFER(u8, test_csd, MMC_MAX_BLOCK_LEN);

	if (mmc->version < MMC_VERSION_4)
		return 0;

	err = mmc_send_ext_csd(mmc, test_csd);
	if (err)
		return err;

	/* Only compare read only fields */
	if (ext_csd[EXT_CSD_PARTITIONING_SUPPORT]
		== test_csd[EXT_CSD_PARTITIONING_SUPPORT] &&
	    ext_csd[EXT_CSD_HC_WP_GRP_SIZE]
		== test_csd[EXT_CSD_HC_WP_GRP_SIZE] &&
	    ext_csd[EXT_CSD_REV]
		== test_csd[EXT_CSD_REV] &&
	    ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE]
		== test_csd[EXT_CSD_HC_ERASE_GRP_SIZE] &&
	    memcmp(&ext_csd[EXT_CSD_SEC_CNT],
		   &test_csd[EXT_CSD_SEC_CNT], 4) == 0)
		return 0;

	return -EBADMSG;
}


static inline int mmc_set_lowest_voltage(struct mmc *mmc, enum bus_mode mode,
					 uint32_t allowed_mask)
{
	return 0;
}


static const struct mode_width_tuning mmc_modes_by_pref[] = {
	{
		.mode = MMC_DDR_52,
		.widths = MMC_MODE_8BIT | MMC_MODE_4BIT,
	},
	{
		.mode = MMC_HS_52,
		.widths = MMC_MODE_8BIT | MMC_MODE_4BIT | MMC_MODE_1BIT,
	},
	{
		.mode = MMC_HS,
		.widths = MMC_MODE_8BIT | MMC_MODE_4BIT | MMC_MODE_1BIT,
	},
	{
		.mode = MMC_LEGACY,
		.widths = MMC_MODE_8BIT | MMC_MODE_4BIT | MMC_MODE_1BIT,
	}
};

#define for_each_mmc_mode_by_pref(caps, mwt) \
	for (mwt = mmc_modes_by_pref;\
	    mwt < mmc_modes_by_pref + ARRAY_SIZE(mmc_modes_by_pref);\
	    mwt++) \
		if (caps & MMC_CAP(mwt->mode))

static const struct ext_csd_bus_width {
	uint cap;
	bool is_ddr;
	uint ext_csd_bits;
} ext_csd_bus_width[] = {
	{MMC_MODE_8BIT, true, EXT_CSD_DDR_BUS_WIDTH_8},
	{MMC_MODE_4BIT, true, EXT_CSD_DDR_BUS_WIDTH_4},
	{MMC_MODE_8BIT, false, EXT_CSD_BUS_WIDTH_8},
	{MMC_MODE_4BIT, false, EXT_CSD_BUS_WIDTH_4},
	{MMC_MODE_1BIT, false, EXT_CSD_BUS_WIDTH_1},
};

static int mmc_select_hs400(struct mmc *mmc)
{
	return -ENOTSUPP;
}


#define for_each_supported_width(caps, ddr, ecbv) \
	for (ecbv = ext_csd_bus_width;\
	    ecbv < ext_csd_bus_width + ARRAY_SIZE(ext_csd_bus_width);\
	    ecbv++) \
		if ((ddr == ecbv->is_ddr) && (caps & ecbv->cap))

static int mmc_select_mode_and_width(struct mmc *mmc, uint card_caps)
{
	int err;
	const struct mode_width_tuning *mwt;
	const struct ext_csd_bus_width *ecbw;

	/* Restrict card's capabilities by what the host can do */
	card_caps &= mmc->host_caps;

	/* Only version 4 of MMC supports wider bus widths */
	if (mmc->version < MMC_VERSION_4)
		return 0;

	if (!mmc->ext_csd) {
		return -ENOTSUPP;
	}

	mmc_set_clock(mmc, mmc->legacy_speed, MMC_CLK_ENABLE);

	for_each_mmc_mode_by_pref(card_caps, mwt) {
		for_each_supported_width(card_caps & mwt->widths,
					 mmc_is_mode_ddr(mwt->mode), ecbw) {
			enum mmc_voltage old_voltage;

			old_voltage = mmc->signal_voltage;
			err = mmc_set_lowest_voltage(mmc, mwt->mode,
						     MMC_ALL_SIGNAL_VOLTAGE);
			if (err)
				continue;

			/* configure the bus width (card + host) */
			err = mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL,
				    EXT_CSD_BUS_WIDTH,
				    ecbw->ext_csd_bits & ~EXT_CSD_DDR_FLAG);
			if (err)
				goto error;
			mmc_set_bus_width(mmc, bus_width(ecbw->cap));

			if (mwt->mode == MMC_HS_400) {
				err = mmc_select_hs400(mmc);
				if (err) {
					goto error;
				}
			} else {
				/* configure the bus speed (card) */
				err = mmc_set_card_speed(mmc, mwt->mode);
				if (err)
					goto error;

				/*
				 * configure the bus width AND the ddr mode
				 * (card). The host side will be taken care
				 * of in the next step
				 */
				if (ecbw->ext_csd_bits & EXT_CSD_DDR_FLAG) {
					err = mmc_switch(mmc,
							 EXT_CSD_CMD_SET_NORMAL,
							 EXT_CSD_BUS_WIDTH,
							 ecbw->ext_csd_bits);
					if (err)
						goto error;
				}

				/* configure the bus mode (host) */
				mmc_select_mode(mmc, mwt->mode);
				mmc_set_clock(mmc, mmc->tran_speed,
					      MMC_CLK_ENABLE);
			}

			/* do a transfer to check the configuration */
			err = mmc_read_and_compare_ext_csd(mmc);
			if (!err)
				return 0;
error:
			mmc_set_signal_voltage(mmc, old_voltage);
			/* if an error occured, revert to a safer bus mode */
			mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL,
				   EXT_CSD_BUS_WIDTH, EXT_CSD_BUS_WIDTH_1);
			mmc_select_mode(mmc, MMC_LEGACY);
			mmc_set_bus_width(mmc, 1);
		}
	}

	return -ENOTSUPP;
}

static int mmc_startup(struct mmc *mmc)
{
	int err, i;
	uint mult, freq;
	u64 cmult, csize;
	struct mmc_cmd cmd;
	struct blk_desc *bdesc;

	/* Put the Card in Identify Mode */
	//cmd.cmdidx = mmc_host_is_spi(mmc) ? MMC_CMD_SEND_CID :
	//	MMC_CMD_ALL_SEND_CID; /* cmd not supported in spi */
	cmd.cmdidx = MMC_CMD_ALL_SEND_CID;
	cmd.resp_type = MMC_RSP_R2;
	cmd.cmdarg = 0;

	err = mmc_send_cmd(mmc, &cmd, NULL);

#ifdef CONFIG_MMC_QUIRKS
	if (err && (mmc->quirks & MMC_QUIRK_RETRY_SEND_CID)) {
		int retries = 4;
		/*
		 * It has been seen that SEND_CID may fail on the first
		 * attempt, let's try a few more time
		 */
		do {
			err = mmc_send_cmd(mmc, &cmd, NULL);
			if (!err)
				break;
		} while (retries--);
	}
#endif

	if (err)
		return err;

	memcpy(mmc->cid, cmd.response, 16);

	/*
	 * For MMC cards, set the Relative Address.
	 * For SD cards, get the Relatvie Address.
	 * This also puts the cards into Standby State
	 */
	if (!mmc_host_is_spi(mmc)) { /* cmd not supported in spi */
		cmd.cmdidx = SD_CMD_SEND_RELATIVE_ADDR;
		cmd.cmdarg = mmc->rca << 16;
		cmd.resp_type = MMC_RSP_R6;

		err = mmc_send_cmd(mmc, &cmd, NULL);

		if (err)
			return err;

		if (IS_SD(mmc))
			mmc->rca = (cmd.response[0] >> 16) & 0xffff;
	}

	/* Get the Card-Specific Data */
	cmd.cmdidx = MMC_CMD_SEND_CSD;
	cmd.resp_type = MMC_RSP_R2;
	cmd.cmdarg = mmc->rca << 16;

	err = mmc_send_cmd(mmc, &cmd, NULL);

	if (err)
		return err;

	mmc->csd[0] = cmd.response[0];
	mmc->csd[1] = cmd.response[1];
	mmc->csd[2] = cmd.response[2];
	mmc->csd[3] = cmd.response[3];

	/* divide frequency by 10, since the mults are 10x bigger */
	freq = fbase[(cmd.response[0] & 0x7)];
	mult = multipliers[((cmd.response[0] >> 3) & 0xf)];

	mmc->legacy_speed = freq * mult;
	mmc_select_mode(mmc, MMC_LEGACY);

	mmc->dsr_imp = ((cmd.response[1] >> 12) & 0x1);
	mmc->read_bl_len = 1 << ((cmd.response[1] >> 16) & 0xf);

#ifdef 	MMC_WRITE
//#if CONFIG_IS_ENABLED(MMC_WRITE)
	if (IS_SD(mmc))
		mmc->write_bl_len = mmc->read_bl_len;
	else
		mmc->write_bl_len = 1 << ((cmd.response[3] >> 22) & 0xf);
#endif

	if (mmc->high_capacity) {/* 高容量卡 > 2GB */
		csize = (mmc->csd[1] & 0x3f) << 16
			| (mmc->csd[2] & 0xffff0000) >> 16;
		cmult = 8;
	} else { /* 低容量卡 <= 2GB, C_SIZE=12bit */
		csize = (mmc->csd[1] & 0x3ff) << 2
			| (mmc->csd[2] & 0xc0000000) >> 30;
		cmult = (mmc->csd[2] & 0x00038000) >> 15;
	}

	mmc->capacity_user = (csize + 1) << (cmult + 2);
	mmc->capacity_user *= mmc->read_bl_len;
	mmc->capacity_boot = 0;
	mmc->capacity_rpmb = 0;
	for (i = 0; i < 4; i++)
		mmc->capacity_gp[i] = 0;

	if (mmc->read_bl_len > MMC_MAX_BLOCK_LEN)
		mmc->read_bl_len = MMC_MAX_BLOCK_LEN;

//#if CONFIG_IS_ENABLED(MMC_WRITE)
#ifdef 	MMC_WRITE
	if (mmc->write_bl_len > MMC_MAX_BLOCK_LEN)
		mmc->write_bl_len = MMC_MAX_BLOCK_LEN;
#endif

    /* 配置DSR寄存器 */
	if ((mmc->dsr_imp) && (0xffffffff != mmc->dsr)) {
		cmd.cmdidx = MMC_CMD_SET_DSR;
		cmd.cmdarg = (mmc->dsr & 0xffff) << 16;
		cmd.resp_type = MMC_RSP_NONE;
		
		//if (mmc_send_cmd(mmc, &cmd, NULL))
		//	debug("MMC: SET_DSR failed\n");
		mmc_send_cmd(mmc, &cmd, NULL);	
	}

	/* Select the card, and put it into Transfer Mode */
	if (!mmc_host_is_spi(mmc)) { /* cmd not supported in spi */
		cmd.cmdidx = MMC_CMD_SELECT_CARD;
		cmd.resp_type = MMC_RSP_R1;
		cmd.cmdarg = mmc->rca << 16;
		err = mmc_send_cmd(mmc, &cmd, NULL);

		if (err)
			return err;
	}

	/*
	 * For SD, its erase group is always one sector
	 */
#ifdef 	MMC_WRITE	 
	mmc->erase_grp_size = 1;
#endif
	mmc->part_config = MMCPART_NOAVAILABLE;

#if 0
/* MMC卡版本大于4.0的startup,利用了ext_csd */
	err = mmc_startup_v4(mmc);
	if (err)
		return err;
#endif

#if  0
    /* 配置结构体中的卡容量mmc->capacity */
	err = mmc_set_capacity(mmc, mmc_get_blk_desc(mmc)->hwpart);
	if (err)
		return err;
#endif

   mmc->capacity = mmc->capacity_user;

	if (IS_SD(mmc)) 
		{
		err = sd_get_capabilities(mmc);
		if (err)
			return err;		
		err = sd_select_mode_and_width(mmc, mmc->card_caps);
	} 

	if (err)
		return err;

	mmc->best_mode = mmc->selected_mode;

	/* Fix the block length for DDR mode */
	if (mmc->ddr_mode) {
		mmc->read_bl_len = MMC_MAX_BLOCK_LEN;
#ifdef 	MMC_WRITE		
//#if CONFIG_IS_ENABLED(MMC_WRITE)
		mmc->write_bl_len = MMC_MAX_BLOCK_LEN;
#endif
	}

	return 0;
}

/* Send Interface Condition Command (CMD8) */
static int mmc_send_if_cond(struct mmc *mmc)
{
	struct mmc_cmd cmd;
	int err;

	cmd.cmdidx = SD_CMD_SEND_IF_COND;
	/* We set the bit if the host supports voltages between 2.7 and 3.6 V */
	cmd.cmdarg = ((mmc->cfg->voltages & 0xff8000) != 0) << 8 | 0xaa;
	cmd.resp_type = MMC_RSP_R7;

	err = mmc_send_cmd(mmc, &cmd, NULL);

	if (err)
		return err;

	if ((cmd.response[0] & 0xff) != 0xaa)
		return -EOPNOTSUPP;
	else
		mmc->version = SD_VERSION_2;

	return 0;
}


/*
 * put the host in the initial state:
 * - turn on Vdd (card power supply)
 * - configure the bus width and clock to minimal values
 */
static void mmc_set_initial_state(struct mmc *mmc)
{
	int err;
		
	/* mode = MMC_LEGACY,	tran_speed= 25M  
	   mode = SD_LEGACY ,	tran_speed= 25M    */
	//mmc_select_mode(mmc, MMC_LEGACY);
	mmc_select_mode(mmc, SD_LEGACY);
	mmc_set_bus_width(mmc, 1); 
	mmc_set_clock(mmc, 0, MMC_CLK_ENABLE);
}

static int mmc_power_on(struct mmc *mmc)
{
	return 0;
}

static int mmc_power_off(struct mmc *mmc)
{
	mmc_set_clock(mmc, 0, MMC_CLK_DISABLE);

	return 0;
}

static int mmc_power_cycle(struct mmc *mmc)
{
	int ret;

	ret = mmc_power_off(mmc);
	if (ret)
		return ret;
	/*
	 * SD spec recommends at least 1ms of delay. Let's wait for 2ms
	 * to be on the safer side.
	 */
	us_delay(2000);
	return 0;
}

int mmc_get_op_cond(struct mmc *mmc)
{
	bool uhs_en = supports_uhs(mmc->cfg->host_caps);
	int err;

	if (mmc->has_init)
		return 0;

#ifdef CONFIG_MMC_QUIRKS
	mmc->quirks = MMC_QUIRK_RETRY_SET_BLOCKLEN |
		      MMC_QUIRK_RETRY_SEND_CID;
#endif

	/* made sure it's not NULL earlier */
	/* call dwmci_init() */
	err = mmc->cfg->ops->init(mmc);
	if (err)
		return err;

	mmc->ddr_mode = 0;

retry:
	mmc_set_initial_state(mmc);

	/* Reset the Card */
	err = mmc_go_idle(mmc);

	if (err)
		return err;

    /* CMD0命令后, 内部分区复位0 */
	/* The internal partition reset to user partition(0) at every CMD0*/
	//mmc_get_blk_desc(mmc)->hwpart = 0;

	/* Test for SD version 2 */
	/* Send Interface Condition Command (CMD8) */
	err = mmc_send_if_cond(mmc);

	/* Now try to get the SD card's operating condition */
	/* read OCR reg (CMD55 + CMD41) */
	err = sd_send_op_cond(mmc, uhs_en);
	if (err && uhs_en) {
		uhs_en = false;
		mmc_power_cycle(mmc);
		goto retry;
	}

	return err;
}

int mmc_start_init(struct mmc *mmc)
{
	unsigned int no_card;
	int err = 0;

	/*
	 * all hosts are capable of 1 bit bus-width and able to use the legacy
	 * timings.
	 */
	mmc->host_caps = mmc->cfg->host_caps | MMC_CAP(SD_LEGACY) |
			 MMC_CAP(MMC_LEGACY) | MMC_MODE_1BIT;

#ifdef  MMC_CARD_DETECT

   no_card = sd_detect() == 1;
   if (no_card)
  {
#ifdef  UART
     Uart_Printf("SD card: no card present!\r\n");
#endif
	//return -ENOMEDIUM;
  }
 	
#endif

	err = mmc_get_op_cond(mmc);

	if (!err)
		mmc->init_in_progress = 1;

	return err;
}

static int mmc_complete_init(struct mmc *mmc)
{
	int err = 0;

	mmc->init_in_progress = 0;
	if (mmc->op_cond_pending)
		err = mmc_complete_op_cond(mmc);

	if (!err)
		err = mmc_startup(mmc);
	if (err)
		mmc->has_init = 0;
	else
		mmc->has_init = 1;
	return err;
}

int mmc_init(struct mmc *mmc)
{
	int err = 0;
	//ulong start;

	//start = get_timer(0);
	err = mmc_start_init(mmc);

	if (!err)
		err = mmc_complete_init(mmc);

	return err;
}

