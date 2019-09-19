#ifndef _TYPES_H_
#define _TYPES_H_

typedef signed char s8;
typedef unsigned char u8;
typedef unsigned char uchar;
typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;
typedef unsigned int uint;

typedef signed long long s64;
typedef unsigned long long u64;
#define BIT(nr)			(1UL << (nr))
typedef unsigned long   ulong;

struct phy_device {
	/* forced speed & duplex (no autoneg)
	 * partner speed & duplex & pause (autoneg)
	 */
	int speed;
	int duplex;

	/* The most recently read link state */
	int link;
	int port;

	u32 mmds;

	int autoneg;
	int addr;
	int pause;
	int asym_pause;
	u32 phy_id;
	u32 flags;
};


extern void udelay(unsigned long usec);
void mdelay(unsigned long msec);
int phy_reset(void);
int m88e1518_config(void);
int m88e1011s_startup(void);
int eqos_mdio_read(int mdio_addr, int mdio_reg);
int eqos_mdio_write(int mdio_addr,int mdio_reg, u16 mdio_val);


#endif
