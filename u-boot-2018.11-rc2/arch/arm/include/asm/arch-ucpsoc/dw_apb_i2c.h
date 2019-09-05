//******************** (C) COPYRIGHT 2019 SmartLogic*******************************
// FileName           : dw_apb_I2C.h
// Author             : lijian, jian.li@smartlogictech.com
// Date First Issued  : 2019-03-29 03:44:23 PM
// Last Modified      : 2019-03-29 03:49:17 PM
// Description        :
// ------------------------------------------------------------
// Modification History:
// Version    Date       Author    Modification Description
//
//**********************************************************************************
#ifndef __I2C_H__
#define __I2C_H__
#define I2C0_DW_APB_I2C_BASE 0x020e8000
#define I2C1_DW_APB_I2C_BASE 0x020f0000


#define I2C0_IC_CON_OFFSET            0x00
#define I2C0_IC_TAR_OFFSET            0x04
#define I2C0_IC_SAR_OFFSET            0x08
#define I2C0_IC_HS_MADDR_OFFSET       0x0c
#define I2C0_IC_DATA_CMD_OFFSET       0x10
#define I2C0_IC_SS_HCNT_OFFSET        0x14
#define I2C0_IC_SS_LCNT_OFFSET        0x18
#define I2C0_IC_FS_HCNT_OFFSET        0x1c
#define I2C0_IC_FS_LCNT_OFFSET        0x20
#define I2C0_IC_HS_HCNT_OFFSET        0x24
#define I2C0_IC_HS_LCNT_OFFSET        0x28
#define I2C0_IC_INTR_STAT_OFFSET      0x2c
#define I2C0_IC_INTR_MASK_OFFSET      0x30
#define I2C0_IC_RAW_INTR_STAT_OFFSET  0x34
#define I2C0_IC_RX_TL_OFFSET          0x38
#define I2C0_IC_TX_TL_OFFSET          0x3c
#define I2C0_IC_CLR_INTR_OFFSET       0x40
#define I2C0_IC_CLR_RX_UNDER_OFFSET   0x44
#define I2C0_IC_CLR_RX_OVER_OFFSET    0x48
#define I2C0_IC_CLR_TX_OVER_OFFSET    0x4c
#define I2C0_IC_CLR_RD_REQ_OFFSET     0x50
#define I2C0_IC_CLR_TX_ABRT_OFFSET    0x54
#define I2C0_IC_CLR_RX_DONE_OFFSET    0x58
#define I2C0_IC_CLR_ACTIVITY_OFFSET   0x5c
#define I2C0_IC_CLR_STOP_DET_OFFSET   0x60
#define I2C0_IC_CLR_START_DET_OFFSET  0x64
#define I2C0_IC_CLR_GEN_CALL_OFFSET   0x68
#define I2C0_IC_ENABLE_OFFSET         0x6c
#define I2C0_IC_STATUS_OFFSET         0x70
#define I2C0_IC_TXFLR_OFFSET          0x74
#define I2C0_IC_RXFLR_OFFSET          0x78
#define I2C0_IC_SRESET_OFFSET         0x7c
#define I2C0_IC_TX_ABRT_SOURCE_OFFSET 0x80
#define I2C0_IC_VERSION_ID_OFFSET     0xf8
#define I2C0_IC_DMA_CR_OFFSET         0x88
#define I2C0_IC_DMA_TDLR_OFFSET       0x8c
#define I2C0_IC_DMA_RDLR_OFFSET       0x90
#define I2C0_IC_PARAM_1_OFFSET        0xf4
#define I2C0_IC_COMP_VERSION_OFFSET   0xf8
#define I2C0_IC_COMP_TYPE_OFFSET      0xfc
#define I2C0_IC_CON                   (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_CON_OFFSET)))
#define I2C0_IC_TAR                   (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_TAR_OFFSET)))
#define I2C0_IC_SAR                   (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_SAR_OFFSET)))
#define I2C0_IC_HS_MADDR              (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_HS_MADDR_OFFSET)))
#define I2C0_IC_DATA_CMD              (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_DATA_CMD_OFFSET)))
#define I2C0_IC_SS_HCNT               (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_SS_HCNT_OFFSET)))
#define I2C0_IC_SS_LCNT               (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_SS_LCNT_OFFSET)))
#define I2C0_IC_FS_HCNT               (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_FS_HCNT_OFFSET)))
#define I2C0_IC_FS_LCNT               (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_FS_LCNT_OFFSET)))
#define I2C0_IC_HS_HCNT               (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_HS_HCNT_OFFSET)))
#define I2C0_IC_HS_LCNT               (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_HS_LCNT_OFFSET)))
#define I2C0_IC_INTR_STAT             (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_INTR_STAT_OFFSET)))
#define I2C0_IC_INTR_MASK             (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_INTR_MASK_OFFSET)))
#define I2C0_IC_RAW_INTR_STAT         (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_RAW_INTR_STAT_OFFSET)))
#define I2C0_IC_RX_TL                 (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_RX_TL_OFFSET)))
#define I2C0_IC_TX_TL                 (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_TX_TL_OFFSET)))
#define I2C0_IC_CLR_INTR              (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_CLR_INTR_OFFSET)))
#define I2C0_IC_CLR_RX_UNDER          (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_CLR_RX_UNDER_OFFSET)))
#define I2C0_IC_CLR_RX_OVER           (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_CLR_RX_OVER_OFFSET)))
#define I2C0_IC_CLR_TX_OVER           (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_CLR_TX_OVER_OFFSET)))
#define I2C0_IC_CLR_RD_REQ            (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_CLR_RD_REQ_OFFSET)))
#define I2C0_IC_CLR_TX_ABRT           (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_CLR_TX_ABRT_OFFSET)))
#define I2C0_IC_CLR_RX_DONE           (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_CLR_RX_DONE_OFFSET)))
#define I2C0_IC_CLR_ACTIVITY          (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_CLR_ACTIVITY_OFFSET)))
#define I2C0_IC_CLR_STOP_DET          (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_CLR_STOP_DET_OFFSET)))
#define I2C0_IC_CLR_START_DET         (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_CLR_START_DET_OFFSET)))
#define I2C0_IC_CLR_GEN_CALL          (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_CLR_GEN_CALL_OFFSET)))
#define I2C0_IC_ENABLE                (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_ENABLE_OFFSET)))
#define I2C0_IC_STATUS                (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_STATUS_OFFSET)))
#define I2C0_IC_TXFLR                 (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_TXFLR_OFFSET)))
#define I2C0_IC_RXFLR                 (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_RXFLR_OFFSET)))
#define I2C0_IC_SRESET                (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_SRESET_OFFSET)))
#define I2C0_IC_TX_ABRT_SOURCE        (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_TX_ABRT_SOURCE_OFFSET)))
#define I2C0_IC_VERSION_ID            (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_VERSION_ID_OFFSET)))
#define I2C0_IC_DMA_CR                (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_DMA_CR_OFFSET)))
#define I2C0_IC_DMA_TDLR              (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_DMA_TDLR_OFFSET)))
#define I2C0_IC_DMA_RDLR              (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_DMA_RDLR_OFFSET)))
#define I2C0_IC_COMP_PARAM_1          (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_COMP_PARAM_1_OFFSET)))
#define I2C0_IC_COMP_VERSION          (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_COMP_VERSION_OFFSET)))
#define I2C0_IC_COMP_TYPE             (*((volatile UINT32 *)(I2C0_DW_APB_I2C_BASE + I2C0_IC_COMP_TYPE_OFFSET)))
#define I2CI2C0_PING_1BIT_WR          (I2C0_IC_TAR)


#define I2C1_IC_CON_OFFSET            0x00
#define I2C1_IC_TAR_OFFSET            0x04
#define I2C1_IC_SAR_OFFSET            0x08
#define I2C1_IC_HS_MADDR_OFFSET       0x0c
#define I2C1_IC_DATA_CMD_OFFSET       0x10
#define I2C1_IC_SS_HCNT_OFFSET        0x14
#define I2C1_IC_SS_LCNT_OFFSET        0x18
#define I2C1_IC_FS_HCNT_OFFSET        0x1c
#define I2C1_IC_FS_LCNT_OFFSET        0x20
#define I2C1_IC_HS_HCNT_OFFSET        0x24
#define I2C1_IC_HS_LCNT_OFFSET        0x28
#define I2C1_IC_INTR_STAT_OFFSET      0x2c
#define I2C1_IC_INTR_MASK_OFFSET      0x30
#define I2C1_IC_RAW_INTR_STAT_OFFSET  0x34
#define I2C1_IC_RX_TL_OFFSET          0x38
#define I2C1_IC_TX_TL_OFFSET          0x3c
#define I2C1_IC_CLR_INTR_OFFSET       0x40
#define I2C1_IC_CLR_RX_UNDER_OFFSET   0x44
#define I2C1_IC_CLR_RX_OVER_OFFSET    0x48
#define I2C1_IC_CLR_TX_OVER_OFFSET    0x4c
#define I2C1_IC_CLR_RD_REQ_OFFSET     0x50
#define I2C1_IC_CLR_TX_ABRT_OFFSET    0x54
#define I2C1_IC_CLR_RX_DONE_OFFSET    0x58
#define I2C1_IC_CLR_ACTIVITY_OFFSET   0x5c
#define I2C1_IC_CLR_STOP_DET_OFFSET   0x60
#define I2C1_IC_CLR_START_DET_OFFSET  0x64
#define I2C1_IC_CLR_GEN_CALL_OFFSET   0x68
#define I2C1_IC_ENABLE_OFFSET         0x6c
#define I2C1_IC_STATUS_OFFSET         0x70
#define I2C1_IC_TXFLR_OFFSET          0x74
#define I2C1_IC_RXFLR_OFFSET          0x78
#define I2C1_IC_SRESET_OFFSET         0x7c
#define I2C1_IC_TX_ABRT_SOURCE_OFFSET 0x80
#define I2C1_IC_VERSION_ID_OFFSET     0xf8
#define I2C1_IC_DMA_CR_OFFSET         0x88
#define I2C1_IC_DMA_TDLR_OFFSET       0x8c
#define I2C1_IC_DMA_RDLR_OFFSET       0x90
#define I2C1_IC_PARAM_1_OFFSET        0xf4
#define I2C1_IC_COMP_VERSION_OFFSET   0xf8
#define I2C1_IC_COMP_TYPE_OFFSET      0xfc
#define I2C1_IC_CON                   (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_CON_OFFSET)))
#define I2C1_IC_TAR                   (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_TAR_OFFSET)))
#define I2C1_IC_SAR                   (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_SAR_OFFSET)))
#define I2C1_IC_HS_MADDR              (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_HS_MADDR_OFFSET)))
#define I2C1_IC_DATA_CMD              (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_DATA_CMD_OFFSET)))
#define I2C1_IC_SS_HCNT               (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_SS_HCNT_OFFSET)))
#define I2C1_IC_SS_LCNT               (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_SS_LCNT_OFFSET)))
#define I2C1_IC_FS_HCNT               (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_FS_HCNT_OFFSET)))
#define I2C1_IC_FS_LCNT               (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_FS_LCNT_OFFSET)))
#define I2C1_IC_HS_HCNT               (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_HS_HCNT_OFFSET)))
#define I2C1_IC_HS_LCNT               (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_HS_LCNT_OFFSET)))
#define I2C1_IC_INTR_STAT             (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_INTR_STAT_OFFSET)))
#define I2C1_IC_INTR_MASK             (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_INTR_MASK_OFFSET)))
#define I2C1_IC_RAW_INTR_STAT         (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_RAW_INTR_STAT_OFFSET)))
#define I2C1_IC_RX_TL                 (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_RX_TL_OFFSET)))
#define I2C1_IC_TX_TL                 (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_TX_TL_OFFSET)))
#define I2C1_IC_CLR_INTR              (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_CLR_INTR_OFFSET)))
#define I2C1_IC_CLR_RX_UNDER          (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_CLR_RX_UNDER_OFFSET)))
#define I2C1_IC_CLR_RX_OVER           (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_CLR_RX_OVER_OFFSET)))
#define I2C1_IC_CLR_TX_OVER           (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_CLR_TX_OVER_OFFSET)))
#define I2C1_IC_CLR_RD_REQ            (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_CLR_RD_REQ_OFFSET)))
#define I2C1_IC_CLR_TX_ABRT           (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_CLR_TX_ABRT_OFFSET)))
#define I2C1_IC_CLR_RX_DONE           (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_CLR_RX_DONE_OFFSET)))
#define I2C1_IC_CLR_ACTIVITY          (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_CLR_ACTIVITY_OFFSET)))
#define I2C1_IC_CLR_STOP_DET          (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_CLR_STOP_DET_OFFSET)))
#define I2C1_IC_CLR_START_DET         (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_CLR_START_DET_OFFSET)))
#define I2C1_IC_CLR_GEN_CALL          (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_CLR_GEN_CALL_OFFSET)))
#define I2C1_IC_ENABLE                (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_ENABLE_OFFSET)))
#define I2C1_IC_STATUS                (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_STATUS_OFFSET)))
#define I2C1_IC_TXFLR                 (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_TXFLR_OFFSET)))
#define I2C1_IC_RXFLR                 (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_RXFLR_OFFSET)))
#define I2C1_IC_SRESET                (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_SRESET_OFFSET)))
#define I2C1_IC_TX_ABRT_SOURCE        (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_TX_ABRT_SOURCE_OFFSET)))
#define I2C1_IC_VERSION_ID            (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_VERSION_ID_OFFSET)))
#define I2C1_IC_DMA_CR                (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_DMA_CR_OFFSET)))
#define I2C1_IC_DMA_TDLR              (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_DMA_TDLR_OFFSET)))
#define I2C1_IC_DMA_RDLR              (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_DMA_RDLR_OFFSET)))
#define I2C1_IC_COMP_PARAM_1          (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_COMP_PARAM_1_OFFSET)))
#define I2C1_IC_COMP_VERSION          (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_COMP_VERSION_OFFSET)))
#define I2C1_IC_COMP_TYPE             (*((volatile UINT32 *)(I2C1_DW_APB_I2C_BASE + I2C1_IC_COMP_TYPE_OFFSET)))
#define I2CI2C1_PING_1BIT_WR          (I2C1_IC_TAR)

#endif
