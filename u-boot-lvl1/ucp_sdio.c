#include <stdio.h>
#include <string.h>
#include "ucp_common.h"
#include "mmc.h"
#include "dwmmc.h"

#define  UCP_SDIO_BASE       0x02050000
#define  SDIO_BUS_WIDTH      4

//#define	 DWMMC_MAX_FREQ			5000000   /* 5M */
#define	 DWMMC_MAX_FREQ			10000000   /* 10M */
#define	 DWMMC_MIN_FREQ			  400000   /* 400k */
#define	 DWMMC_CLOCK			50000000   /* 50M */

struct mmc ucp_mmc;
struct dwmci_host ucp_host;

#define SYSTIMER_RELOAD 0xFFFFFFFF
static struct dw_timer *systimer_base = (struct dw_timer *)0x031d0000;

#define TIMER_CLK   50000000            /* 50M */
#define BASE_US    (TIMER_CLK/1000000)  /* BASE_US=1us */

int mmc_init(struct mmc *mmc);
u32 mmc_bread(u32 start, u32 blkcnt,void *dst);
int add_dwmci(struct dwmci_host *host, u32 max_clk, u32 min_clk);

int mmc_set_blocklen(struct mmc *mmc, int len);
int mmc_read_blocks(struct mmc *mmc, void *dst, unsigned int start,unsigned int blkcnt);

struct mmc *mmc_create(const struct mmc_config *cfg, void *priv)
//struct mmc *mmc_create(const struct mmc_config *cfg)
{
	struct mmc *mmc = &ucp_mmc;

	mmc->cfg = cfg;
	mmc->priv = priv;

	return mmc;
}


//ulong mmc_bread(struct blk_desc *block_dev, u32 start, u32 blkcnt,void *dst)
u32 mmc_bread(u32 start, u32 blkcnt,void *dst)
{
#ifndef  SELF_TEST
	int dev_num = block_dev->devnum;
#endif	
	int err;
	u32 cur, blocks_todo = blkcnt;
    struct mmc *mmc = &ucp_mmc;
    
	if (blkcnt == 0)
		return 0;
		
#ifndef  SELF_TEST
	struct mmc *mmc = find_mmc_device(dev_num);
	if (!mmc)
		return 0;

	if (CONFIG_IS_ENABLED(MMC_TINY))
		err = mmc_switch_part(mmc, block_dev->hwpart);
	else
		err = blk_dselect_hwpart(block_dev, block_dev->hwpart);

	if (err < 0)
		return 0;

	if ((start + blkcnt) > block_dev->lba) 
	{
#if !defined(CONFIG_SPL_BUILD) || defined(CONFIG_SPL_LIBCOMMON_SUPPORT)
		pr_err("MMC: block number 0x" LBAF " exceeds max(0x" LBAF ")\n",
		       start + blkcnt, block_dev->lba);
#endif
		return 0;
	}
#endif

	if (mmc_set_blocklen(mmc, mmc->read_bl_len)) 
	{
		//pr_debug("%s: Failed to set blocklen\n", __func__);
		debug("%s: Failed to set blocklen\n", __func__);
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
			debug("%s: Failed to read blocks\n", __func__);
			return 0;
		}
		blocks_todo -= cur;
		start += cur;
		dst += cur * mmc->read_bl_len;
	} while (blocks_todo > 0);

	return blkcnt;
}

/* 返回值单位us  */
ulong get_timer(ulong usec)
{
    ulong  now,base;
    
    if(!usec)
      return (readl(&systimer_base->timer0value)/BASE_US);
      
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

 void ucp_timer_init(void)
{
	/*
	 * Set Timer0 to be:
	 *   Enabled, free running, no interrupt, user-mode
	 */
	writel(SYSTIMER_RELOAD, &systimer_base->timer0load);
	writel(5, &systimer_base->timer0control);
}


int ucp_sdio_init(void)
{
    struct dwmci_host *host = &ucp_host;

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
		debug("DWMMC registration failed\n");
		return -1;
	}

    ucp_mmc.dsr_imp		= 0;
    ucp_mmc.dsr			= 0xffffffff;
    mmc_init(&ucp_mmc);	
}

void  ucp_sdio_main(void)
{
   //memset(&ucp_mmc,0,sizeof(struct mmc));
   
   //ucp_mmc.dsr_imp		= 0;
   //ucp_mmc.dsr			= 0xffffffff;
   //ucp_mmc.cfg->host_caps =0;

   ucp_timer_init();

   //mmc_init(&ucp_mmc);
   ucp_sdio_init();
//   mmc_bread(0, 1,(void *)0x40000000);

//   mmc_bread(0, 3,(void *)0x41000000);

//   mmc_bread(1, 3,(void *)0x42000000);

   void loadfile(void *addr);
   loadfile((void*)0x04e60000);
}
