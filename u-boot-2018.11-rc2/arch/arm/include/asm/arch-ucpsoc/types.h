#ifndef _TYPES_H_
#define _TYPES_H_

//#define ARCH_DMA_MINALIGN 64 

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

void udelay(unsigned long usec);
void mdelay(unsigned long msec);
int ucp_phy_reset(void);
u32 ucp_get_phy_id(void);  
int m88e1518_config(void);
int m88e1011s_startup(void);
extern struct phy_device g_phydev;

int eqos_mdio_read(struct mii_dev *bus, int mdio_addr, int mdio_devad, int mdio_reg);
int eqos_mdio_write(struct mii_dev *bus, int mdio_addr, int mdio_devad,  int mdio_reg, u16 mdio_val);

#endif
