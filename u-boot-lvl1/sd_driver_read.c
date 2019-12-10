#include <stdio.h>
#include <string.h>
#include "drv_common.h"
#include "sd_common.h"
#include "mmc.h"
#include "dwmmc.h"


//#define  UCP_SDIO_BASE       0x02050000
#define  SDIO_BUS_WIDTH      4

//#define	 DWMMC_MAX_FREQ			5000000   /* 5M */
#define	 DWMMC_MAX_FREQ			10000000   /* 10M */
#define	 DWMMC_MIN_FREQ			  400000   /* 400k */
#define	 DWMMC_CLOCK			SYS_CLK   /* 50M */

struct mmc ucp_mmc;
struct dwmci_host ucp_host;

#define SYSTIMER_RELOAD 0xFFFFFFFF
static struct dw_timer *systimer_base = (struct dw_timer *)0x031d0000;
static struct dw_timer *systimer1_base = (struct dw_timer *)0x031d0014;

#define TIMER_CLK   SYS_CLK            /* 50M */
#define BASE_US    (TIMER_CLK/1000000)  /* BASE_US=1us */

#define BASE_10US   25     /* timer clk=2.5M, base=10us */

int mmc_init(struct mmc *mmc);
u32 mmc_bread(u32 start, u32 blkcnt,void *dst);
int add_dwmci(struct dwmci_host *host, u32 max_clk, u32 min_clk);

int mmc_set_blocklen(struct mmc *mmc, int len);
int mmc_read_blocks(struct mmc *mmc, void *dst, unsigned int start,unsigned int blkcnt);
const char *mmc_mode_name(enum bus_mode mode);
struct mmc *mmc_create(const struct mmc_config *cfg, void *priv)
//struct mmc *mmc_create(const struct mmc_config *cfg)
{
	struct mmc *mmc = &ucp_mmc;

	mmc->cfg = cfg;
	mmc->priv = priv;

	return mmc;
}

/* blocksize=512byte, 
   start: start block
*/
//ulong mmc_bread(struct blk_desc *block_dev, u32 start, u32 blkcnt,void *dst)
u32 mmc_bread(u32 start, u32 blkcnt,void *dst)
{	
	int err;
	u32 cur, blocks_todo = blkcnt;
    struct mmc *mmc = &ucp_mmc;
    
	if (blkcnt == 0)
		return 0;
		
	if (mmc_set_blocklen(mmc, mmc->read_bl_len)) 
	{
		//pr_debug("%s: Failed to set blocklen\n", __func__);
		debug("%s: Failed to set blocklen\n\r", __func__);
		return 0;
	}

    /* 
      mmc->cfg->b_max ??
    */
	do {
		cur = (blocks_todo > mmc->cfg->b_max) ?
			mmc->cfg->b_max : blocks_todo;
		if (mmc_read_blocks(mmc, dst, start, cur) != cur) 
		{
			//pr_debug("%s: Failed to read blocks\n", __func__);
			debug("%s: Failed to read blocks\n\r", __func__);
			return 0;
		}
		blocks_todo -= cur;
		start += cur;
		dst += cur * mmc->read_bl_len;
	} while (blocks_todo > 0);

	return blkcnt;
}

/* delay = usec us, usec < 85000000(85s)
*/
void us_delay(unsigned int usec)
{
    unsigned int value,status;

    writel(0, &systimer1_base->timer0control);
    value = usec*BASE_US;
    writel(value, &systimer1_base->timer0load);
	writel(3, &systimer1_base->timer0control);

    do{    
       status = readl(&systimer1_base->timer0IntStatus);
    }while(!status);	
	writel(0, &systimer1_base->timer0control);	
}

/* before pll locked, clock is 2.5MHz  
  delay unit: 10us */
void tus_delay(unsigned int tusec)
{
    unsigned int value,status;

    writel(0, &systimer1_base->timer0control);
    value = tusec*BASE_10US;
    writel(value, &systimer1_base->timer0load);
	writel(3, &systimer1_base->timer0control);

    do{    
       status = readl(&systimer1_base->timer0IntStatus);
    }while(!status);	
	writel(0, &systimer1_base->timer0control);	
}



/* 返回值单位us  */
ulong get_timer(ulong usec)
{
    ulong  now,base;
	uint   value;

#if 0    
    if(!usec)
      return (readl(&systimer_base->timer0value)/BASE_US);
#else
    if(!usec)
    {
       value = readl(&systimer_base->timer0value);
       return (value/BASE_US);
    }
#endif
      
    base = (usec*BASE_US);
    now = readl(&systimer_base->timer0value);
    if(base > now)
       return ((base-now)/BASE_US);
	else
	{
       base = 0xFFFFFFFF-now+base;
       return (base/BASE_US);
	}
}

 void timer_init(void)
{
	/*
	 * Set Timer0 to be:
	 *   Enabled, free running, no interrupt, user-mode, Timer down counter
	 */
	writel(SYSTIMER_RELOAD, &systimer_base->timer0load);
	writel(5, &systimer_base->timer0control);
}


int sd_init(void)
{
    struct dwmci_host *host = &ucp_host;
    int err=0;
    
	memset(host,0,sizeof(struct dwmci_host));
	memset(&ucp_mmc,0,sizeof(struct mmc));
	
	host->ioaddr = (void *)UCP_SDIO_BASE;
	host->buswidth = 4;
	host->name = "UCP DWMMC";
    host->bus_hz = DWMMC_CLOCK;
	host->dev_index = 0;
#if 0
    host->fifo_mode = 1;
    host->fifoth_val = MSIZE(0x2) | RX_WMARK(0x100 / 2 - 1) | TX_WMARK(0x100 / 2);
#endif
    
	/* Add the mmc channel to be registered with mmc core */
	if (add_dwmci(host, DWMMC_MAX_FREQ, DWMMC_MIN_FREQ)) 
	{
		debug("DWMMC registration failed\n\r");
		return -1;
	}    
    ucp_mmc.dsr_imp		= 0;
    ucp_mmc.dsr			= 0xffffffff;
    err = mmc_init(&ucp_mmc);	
	if(err)
    {
	  debug("%s: Failed in mmc_init(). \n\r", __func__);
      return -1;
    }
    return 0;
}

int  sd_fs_read(void) // sd driver file system read
{
   timer_init();
   if(sd_init() != 0) return false;

   int loadfile(void *addr);
   if(loadfile((void*)0x04e60000) == false) return false;

   return true;
}
