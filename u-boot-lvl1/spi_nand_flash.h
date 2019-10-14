


#ifndef __NAND_FLASH_H__
#define __NAND_FLASH_H__


/* C版本GD5F1GQ4UC  */
#define GD5F1GQ4U 	0XC8B148
#define GD5F2GQ4U 	0XC8B248
#define GD5F1GQ4R 	0XC8A148
#define GD5F2GQ4R 	0XC8A248
            

/* B 版本 */
#define GD5F1GQ4RB 	0XC8C1     /* 1Gbit,  B version, 1.8v */
#define GD5F2GQ4RB 	0XC8C2     /* 2Gbit,  B version, 1.8v */

#define   DELAY_CYCLE     1000*55  
#define   CPU_FREQ           50               /* 50MHz */
#define   CPU_NS               (DELAY_CYCLE/CPU_FREQ)     /* ns */


#define NAND_SPI_ER_STATUS_P_FAIL       (1 << 3)		//写入失败标记
#define NAND_SPI_ER_STATUS_E_FAIL       (1 << 2)		//擦除失败标记
#define NAND_SPI_ER_STATUS_WEL          (1 << 1)		//允许写入标记
#define NAND_SPI_ER_STATUS_OIP          (1 << 0)		//设备忙碌标记


/* SPI NAND Flash Command */
#define SPI_NAND_WRITE_ENABLE_CMD           0x06
#define SPI_NAND_WRITE_DISABLE_CMD          0x04
#define SPI_NAND_GET_FEATURE_CMD            0x0f
#define SPI_NAND_SET_FEATURE_CMD            0x1f
#define SPI_NAND_READ_TO_CACHE_CMD          0x13
#define SPI_NAND_READ_FROM_CACHE1_CMD       0x03
#define SPI_NAND_READ_FROM_CACHE2_CMD       0x0b
#define SPI_NAND_READ_ID_CMD                0x9f
#define SPI_NAND_PROGRAM_LOAD_CMD           0x02
#define SPI_NAND_PROGRAM_EXEC_CMD           0x10
#define SPI_NAND_PROGRAM_LOAD_RANDOM_CMD    0x84
#define SPI_NAND_ERASE_BLOCK_CMD            0xd8
#define SPI_NAND_RESET_CMD                  0xff


#define NAND_ID_GD5F1G                      0x00C8


/* nandflash confg */
#define PAGES_PER_BLOCK         64
#define PAGE_DATA_SIZE          2048
#define PAGE_OOB_SIZE           64
#define NAND_MARK_SPARE_OFFSET  4

#define   FLASH_512M_BIT     1
#define   FLASH_1G_BIT          2
#define   FLASH_2G_BIT          3

#define m_max(a,b) ( ((a)>(b)) ? (a):(b) )
#define m_min(a,b) ( ((a)>(b)) ? (b):(a) )


#define BL_ALL_LOCKED           0x38 
#define BLOCK_0_LOCKED        0x32
#define BLOCK_0_LOCKED2      0x36
#define BL_ALL_UNLOCKED      0

#define BL_1_2_LOCKED      0x30
#define BL_1_4_LOCKED      0x28
#define BL_1_8_LOCKED      0x20
#define BL_1_16_LOCKED     0x18
#define BL_1_32_LOCKED     0x10
#define BL_1_64_LOCKED     0x08

/* Feature register */
#define   STAT_PROTECT      0xA0
#define   STAT_FEATURE1    0xB0
#define   STAT_STATUS        0xC0
#define   STAT_FEATURE2    0xD0
#define   STAT_STATUS2      0xF0

#define  SET_BRWD          0x80
#define  SET_ECC_EN        0x10
#define  STATUS_WEL       0x02

#define  CHECK_NUM        500

#define  ECC_ERROR_4     4
#define  ECC_ERROR_5     5
#define  ECC_ERROR_6     6
#define  ECC_ERROR_7     7

#define    ECC_OK                      0x0
#define    ECC_FAILED               0x1
#define    ECC_CORRECT            0x2 

/* block0 空间分配   */
#define    BLOCK0           0x0       /* block0 page n   */
/* block0 page0-1 预留 */
#define    CC_BK_PAGE       0x2        /* 出厂坏块标记的存储页--block0 page x */
#define    USE_BK_PAGE      0x3        /* 使用坏块标记的存储页--block0 page y  */

#define    UBOOT_PAGE       0x4
#define    DDR_PAGE         0x5       /* DDR参数 */
#define    LINUX_PAGE       0x6
#define    LINUX_FS_PAGE    0x7
#define    LINUX_FS_DTB     0x8
#define    END_PAGE         (LINUX_FS_DTB+1)


/*  */
#define    FILE_NUM_ALL      0x5  
#define    FILE_UBOOT        0x0
#define    FILE_DDR          0x1
#define    FILE_LINUX        0x2
#define    FILE_LINUX_FS     0x3
#define    FILE_LINUX_DTB    0x4


#define    BK_LEN                 64         /*  坏块表长度 */
#define    PAGE_LEN             2048     /*  页长度 */
#define    END_FLG               0x5A6B7C8D   
#define    HEAD_LEN             16

#define    DRV_OK              0x0
#define    WAIT_TIMEOUT        0x1
#define    ECC_ERROR           0x2
#define    PARA_ERROR          0x3
#define    ERASE_ERROR         0x4
#define    PROM_ERROR          0x5



typedef struct
{
    unsigned char   file_typ;       /* uboot,linux,ddr data */
    unsigned char   rev2[3];
    unsigned int     file_len;       /* 文件长度,单位字节 */
    unsigned int     crc;              /*  CRC校验值 */   
    unsigned int     f_end;        /*  结束标记 */   
  
}file_head;

int spi_nand_flash_init(void);

unsigned char nandflash_read(unsigned int         src_row_addr,
                                                      unsigned int         src_col_addr,
                                                      unsigned char     *dst_addr,
                                                      unsigned int         data_len);


unsigned char nandflash_readid(unsigned char *rxiD);		//读取NANDFLASH的ID号

unsigned char nandflash_readpage(unsigned int                 page,//页地址			读取一个页面的数据
                                   unsigned char                *data,//保存读取数据的缓存
                                   unsigned int                data_addr,//要读取页内的首地址
                                   unsigned int                data_len);//要读取页的字节数

#endif /* __NAND_FLASH_H__ */

