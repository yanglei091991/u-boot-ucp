// SPDX-License-Identifier: GPL-2.0+
/*
 * Marvell PHY drivers
 *
 * Copyright 2010-2011 Freescale Semiconductor, Inc.
 * author Andy Fleming
 */
#include "types.h"
#include "mdio.h"
#include "mii.h"
#include "errno.h"
#include <common.h>

#define PHY_ANEG_TIMEOUT	8000	/* PHY needs a longer aneg time */

#define PHY_AUTONEGOTIATE_TIMEOUT 5000

#define MII_MARVELL_PHY_PAGE		22

/* 88E1011 PHY Status Register */
#define MIIM_88E1xxx_PHY_STATUS		0x11
#define MIIM_88E1xxx_PHYSTAT_SPEED	0xc000
#define MIIM_88E1xxx_PHYSTAT_GBIT	0x8000
#define MIIM_88E1xxx_PHYSTAT_100	0x4000
#define MIIM_88E1xxx_PHYSTAT_DUPLEX	0x2000
#define MIIM_88E1xxx_PHYSTAT_SPDDONE	0x0800
#define MIIM_88E1xxx_PHYSTAT_LINK	0x0400

#define MIIM_88E1xxx_PHY_SCR		0x10
#define MIIM_88E1xxx_PHY_MDI_X_AUTO	0x0060

/* 88E1111 PHY LED Control Register */
#define MIIM_88E1111_PHY_LED_CONTROL	24
#define MIIM_88E1111_PHY_LED_DIRECT	0x4100
#define MIIM_88E1111_PHY_LED_COMBINE	0x411C

/* 88E1111 Extended PHY Specific Control Register */
#define MIIM_88E1111_PHY_EXT_CR		0x14
#define MIIM_88E1111_RX_DELAY		0x80
#define MIIM_88E1111_TX_DELAY		0x2

/* 88E1111 Extended PHY Specific Status Register */
#define MIIM_88E1111_PHY_EXT_SR		0x1b
#define MIIM_88E1111_HWCFG_MODE_MASK		0xf
#define MIIM_88E1111_HWCFG_MODE_COPPER_RGMII	0xb
#define MIIM_88E1111_HWCFG_MODE_FIBER_RGMII	0x3
#define MIIM_88E1111_HWCFG_MODE_SGMII_NO_CLK	0x4
#define MIIM_88E1111_HWCFG_MODE_COPPER_RTBI	0x9
#define MIIM_88E1111_HWCFG_FIBER_COPPER_AUTO	0x8000
#define MIIM_88E1111_HWCFG_FIBER_COPPER_RES	0x2000

#define MIIM_88E1111_COPPER		0
#define MIIM_88E1111_FIBER		1

/* 88E1118 PHY defines */
#define MIIM_88E1118_PHY_PAGE		22
#define MIIM_88E1118_PHY_LED_PAGE	3

/* 88E1121 PHY LED Control Register */
#define MIIM_88E1121_PHY_LED_CTRL	16
#define MIIM_88E1121_PHY_LED_PAGE	3
#define MIIM_88E1121_PHY_LED_DEF	0x0030

/* 88E1121 PHY IRQ Enable/Status Register */
#define MIIM_88E1121_PHY_IRQ_EN		18
#define MIIM_88E1121_PHY_IRQ_STATUS	19

#define MIIM_88E1121_PHY_PAGE		22

/* 88E1145 Extended PHY Specific Control Register */
#define MIIM_88E1145_PHY_EXT_CR 20
#define MIIM_M88E1145_RGMII_RX_DELAY	0x0080
#define MIIM_M88E1145_RGMII_TX_DELAY	0x0002

#define MIIM_88E1145_PHY_LED_CONTROL	24
#define MIIM_88E1145_PHY_LED_DIRECT	0x4100

#define MIIM_88E1145_PHY_PAGE	29
#define MIIM_88E1145_PHY_CAL_OV 30

#define MIIM_88E1149_PHY_PAGE	29

/* 88E1310 PHY defines */
#define MIIM_88E1310_PHY_LED_CTRL	16
#define MIIM_88E1310_PHY_IRQ_EN		18
#define MIIM_88E1310_PHY_RGMII_CTRL	21
#define MIIM_88E1310_PHY_PAGE		22

/* 88E151x PHY defines */
/* Page 2 registers */
#define MIIM_88E151x_PHY_MSCR		21
#define MIIM_88E151x_RGMII_RX_DELAY	BIT(5)
#define MIIM_88E151x_RGMII_TX_DELAY	BIT(4)
#define MIIM_88E151x_RGMII_RXTX_DELAY	(BIT(5) | BIT(4))
/* Page 3 registers */
#define MIIM_88E151x_LED_FUNC_CTRL	16
#define MIIM_88E151x_LED_FLD_SZ		4
#define MIIM_88E151x_LED0_OFFS		(0 * MIIM_88E151x_LED_FLD_SZ)
#define MIIM_88E151x_LED1_OFFS		(1 * MIIM_88E151x_LED_FLD_SZ)
#define MIIM_88E151x_LED0_ACT		3
#define MIIM_88E151x_LED1_100_1000_LINK	6
#define MIIM_88E151x_LED_TIMER_CTRL	18
#define MIIM_88E151x_INT_EN_OFFS	7
/* Page 18 registers */
#define MIIM_88E151x_GENERAL_CTRL	20
#define MIIM_88E151x_MODE_SGMII		1
#define MIIM_88E151x_RESET_OFFS		15

/* Ethernet driver configuration */
#define CONFIG_PHY_RESET_DELAY			10000		/* in usec */

#define AUTONEG_DISABLE		0x00
#define AUTONEG_ENABLE		0x01

#define PHY_ID 0x1410dd0
#define BIT(nr)			(1UL << (nr))



struct phy_device g_phydev={0};

extern void udelay(unsigned long usec);

extern void mdelay(unsigned long msec);



int phy_read(int regnum)
{
	struct phy_device *phydev = &g_phydev;
	
	return eqos_mdio_read(phydev->addr, regnum);
}
int phy_write(int regnum, u16 val)
{
	struct phy_device *phydev = &g_phydev;

	return eqos_mdio_write(phydev->addr, regnum, val);
}

int ScanPhyAddr(void)
{
	int i;
	u16 val;
	struct phy_device *phydev = &g_phydev;
	
	for(i=0; i<31; i++)
	{	
		val = eqos_mdio_read(i, 2);
		if(0x0141 == val)
		{
			phydev->addr = i;
			return i;
		}
	}
	return -1;
}
int phy_reset()
{
	int reg;



	phy_write(MII_BMCR, BMCR_RESET);

	udelay(CONFIG_PHY_RESET_DELAY);	/* Intel LXT971A needs this */
	/*
	 * Poll the control register for the reset bit to go to 0 (it is
	 * auto-clearing).  This should happen within 0.5 seconds per the
	 * IEEE spec.
	 */
	reg = phy_read(MII_BMCR);
	while (reg & BMCR_RESET) {
		reg = phy_read(MII_BMCR);
		udelay(1000);
	}

	if (reg & BMCR_RESET) {
		return -1;
	}

	return 0;
}


int genphy_update_link()
{
	unsigned int mii_reg;
	struct phy_device *phydev = &g_phydev;
	/*
	 * Wait if the link is up, and autonegotiation is in progress
	 * (ie - we're capable and it's not done)
	 */
	mii_reg = phy_read(MII_BMSR);

	/*
	 * If we already saw the link up, and it hasn't gone down, then
	 * we don't need to wait for autoneg again
	 */
	if (phydev->link && mii_reg & BMSR_LSTATUS)
		return 0;

	if ((phydev->autoneg == AUTONEG_ENABLE) &&
	    !(mii_reg & BMSR_ANEGCOMPLETE)) {
		int i = 0;


		while (!(mii_reg & BMSR_ANEGCOMPLETE)) {
			/*
			 * Timeout reached ?
			 */
			if (i > PHY_ANEG_TIMEOUT) {
				phydev->link = 0;
				return -ETIMEDOUT;
			}



			if ((i++ % 500) == 0)

			udelay(1000);	/* 1 ms */
			mii_reg = phy_read(MII_BMSR);
		}
		phydev->link = 1;
	} else {
		/* Read the link a second time to clear the latched state */
		mii_reg = phy_read(MII_BMSR);

		if (mii_reg & BMSR_LSTATUS)
			phydev->link = 1;
		else
			phydev->link = 0;
	}

	return 0;
}
static int genphy_setup_forced(void)
{

	int err;
	int ctl = BMCR_ANRESTART;
	struct phy_device *phydev = &g_phydev;
	
	phydev->pause = 0;
	phydev->asym_pause = 0;

	

	if (phydev->speed == SPEED_1000)
		ctl |= BMCR_SPEED1000;
	else if (phydev->speed == SPEED_100)
		ctl |= BMCR_SPEED100;


	if (phydev->duplex == DUPLEX_FULL)
		ctl |= BMCR_FULLDPLX;

	err = phy_write(MII_BMCR, ctl);

	return err;

}

int genphy_config_advert(void)
{
	int oldadv, adv, bmsr;
	int err, changed = 0;

	/* Only allow advertising what this PHY supports */


	/* Setup standard advertisement */
	adv = phy_read(MII_ADVERTISE);
	oldadv = adv;

	if (adv < 0)
		return adv;

	adv &= ~(ADVERTISE_ALL | ADVERTISE_100BASE4 | ADVERTISE_PAUSE_CAP |
		 ADVERTISE_PAUSE_ASYM);

	adv |= ADVERTISE_100FULL;
	adv |= ADVERTISE_1000XFULL;

	if (adv != oldadv) {
		err = phy_write(MII_ADVERTISE, adv);

		if (err < 0)
			return err;
		changed = 1;
	}

	bmsr = phy_read(MII_BMSR);
	if (bmsr < 0)
		return bmsr;

	/* Per 802.3-2008, Section 22.2.4.2.16 Extended status all
	 * 1000Mbits/sec capable PHYs shall have the BMSR_ESTATEN bit set to a
	 * logical 1.
	 */
	if (!(bmsr & BMSR_ESTATEN))
		return changed;

	/* Configure gigabit if it's supported */
	adv = phy_read(MII_CTRL1000);
	oldadv = adv;

	if (adv < 0)
		return adv;

	adv &= ~(ADVERTISE_1000FULL | ADVERTISE_1000HALF);

	adv |= ADVERTISE_1000HALF;
	adv |= ADVERTISE_1000FULL;

	if (adv != oldadv)
		changed = 1;

	err = phy_write(MII_CTRL1000, adv);
	if (err < 0)
		return err;

	return changed;
}
int genphy_restart_aneg(void)
{
	int ctl;

	ctl = phy_read(MII_BMCR);

	if (ctl < 0)
		return ctl;

	ctl |= (BMCR_ANENABLE | BMCR_ANRESTART);

	/* Don't isolate the PHY if we're negotiating */
	ctl &= ~(BMCR_ISOLATE);

	ctl = phy_write(MII_BMCR, ctl);

	return ctl;
}


int genphy_config_aneg(void)
{
	int result;
	/*前期调试，强制设置，取消自动协商功能*/
	return genphy_setup_forced();
	result = genphy_config_advert();

	if (result < 0) /* error */
		return result;

	if (result == 0) {
		/*
		 * Advertisment hasn't changed, but maybe aneg was never on to
		 * begin with?  Or maybe phy was isolated?
		 */
		int ctl = phy_read(MII_BMCR);

		if (ctl < 0)
			return ctl;

		if (!(ctl & BMCR_ANENABLE) || (ctl & BMCR_ISOLATE))
			result = 1; /* do restart aneg */
	}

	/*
	 * Only restart aneg if we are advertising something different
	 * than we were before.
	 */
	if (result > 0)
		result = genphy_restart_aneg();

	return result;
}



/* Parse the 88E1011's status register for speed and duplex
 * information
 */
int m88e1xxx_parse_status(void)
{
	unsigned int speed;
	unsigned int mii_reg;
	struct phy_device *phydev = &g_phydev;

	mii_reg = phy_read(MIIM_88E1xxx_PHY_STATUS);

	if ((mii_reg & MIIM_88E1xxx_PHYSTAT_LINK) &&
	    !(mii_reg & MIIM_88E1xxx_PHYSTAT_SPDDONE)) {
		int i = 0;


		while (!(mii_reg & MIIM_88E1xxx_PHYSTAT_SPDDONE)) {
			/* Timeout reached ? */
			if (i > PHY_AUTONEGOTIATE_TIMEOUT) {

				phydev->link = 0;
				return -ETIMEDOUT;
			}


			udelay(1000);
			mii_reg = phy_read(MIIM_88E1xxx_PHY_STATUS);
		}

		mdelay(50);	/* another 500 ms (results in faster booting) 2.5M ~50*/
	} else {
		if (mii_reg & MIIM_88E1xxx_PHYSTAT_LINK)
			phydev->link = 1;
		else
			phydev->link = 0;
	}

	if (mii_reg & MIIM_88E1xxx_PHYSTAT_DUPLEX)
		phydev->duplex = DUPLEX_FULL;
	else
		phydev->duplex = DUPLEX_HALF;

	speed = mii_reg & MIIM_88E1xxx_PHYSTAT_SPEED;

	switch (speed) {
	case MIIM_88E1xxx_PHYSTAT_GBIT:
		phydev->speed = SPEED_1000;
		break;
	case MIIM_88E1xxx_PHYSTAT_100:
		phydev->speed = SPEED_100;
		break;
	default:
		phydev->speed = SPEED_10;
		break;
	}

	return 0;
}

int m88e1011s_startup(void)
{
	int ret;

	ret = genphy_update_link();
	if (ret)
		return ret;

	return m88e1xxx_parse_status();
}
int my_phy_init(void)
{
	struct phy_device *phydev = &g_phydev;
	phydev->speed = SPEED_100;
	phydev->duplex = DUPLEX_FULL;
	
}
int m88e1518_config(void)
{
	u16 reg;

	my_phy_init();
	/*
	 * As per Marvell Release Notes - Alaska 88E1510/88E1518/88E1512
	 * /88E1514 Rev A0, Errata Section 3.1
	 */

	/* EEE initialization */
	phy_write(MIIM_88E1118_PHY_PAGE, 0x00ff);
	phy_write( 17, 0x214B);
	phy_write(16, 0x2144);
	phy_write(17, 0x0C28);
	phy_write(16, 0x2146);
	phy_write(17, 0xB233);
	phy_write(16, 0x214D);
	phy_write(17, 0xCC0C);
	phy_write(16, 0x2159);
	phy_write(MIIM_88E1118_PHY_PAGE, 0x0000);

	/* led initialization */
//	phy_write(MIIM_88E1118_PHY_LED_PAGE, 0x00ff);
//	phy_write( 16, 0x0);
//	phy_write(MIIM_88E1118_PHY_LED_PAGE, 0x0000);


	/* rgmii init */
	phy_write(MII_MARVELL_PHY_PAGE, 2);

	reg = phy_read(MIIM_88E151x_PHY_MSCR);
	reg &= ~MIIM_88E151x_RGMII_RXTX_DELAY;

	reg |= MIIM_88E151x_RGMII_RXTX_DELAY;

	phy_write(MIIM_88E151x_PHY_MSCR, reg);

	phy_write(MII_MARVELL_PHY_PAGE, 0);


	/* soft reset */
	phy_reset();

	genphy_config_aneg();
//	genphy_restart_aneg();/* it will make phy-mode 10M  to 100M */

	return 0;
}

u32 get_phy_id(void)
{
	u16 reg= 0;
	u32 id = 0;
	struct phy_device *phydev = &g_phydev;

	
	reg = phy_read(MII_PHYSID1);
	id = reg;
	reg = phy_read(MII_PHYSID2);
	id = id<<16;
	id |= reg;
	phydev->phy_id = id;

	return id;
}


