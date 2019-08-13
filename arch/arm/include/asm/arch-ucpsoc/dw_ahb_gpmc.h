//******************** (C) COPYRIGHT 2019 SmartLogic*******************************
// FileName           : dw_ahb_gpmc.h
// Author             : lijian, jian.li@smartlogictech.com
// Date First Issued  : 2019-03-29 02:58:59 PM
// Last Modified      : 2019-04-26 04:56:23 PM
// Description        :
// ------------------------------------------------------------
// Modification History:
// Version    Date       Author    Modification Description
//
//**********************************************************************************


#ifndef __GPMC_H__
#define __GPMC_H__


#define ahb_gpmc_DW_MEMCTL_BASE           0x02090000

#define MEMCTRL_SCONR             (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x00)))
#define MEMCTRL_STMG0R            (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x04)))
#define MEMCTRL_STMG1R            (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x08)))
#define MEMCTRL_SCTLR             (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x0c)))
#define MEMCTRL_SREFR             (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x10)))
#define MEMCTRL_SCSLR0_LOW        (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x14)))
#define MEMCTRL_SCSLR1_LOW        (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x18)))
#define MEMCTRL_SCSLR2_LOW        (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x1c)))
#define MEMCTRL_SCSLR3_LOW        (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x20)))
#define MEMCTRL_SCSLR4_LOW        (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x24)))
#define MEMCTRL_SCSLR5_LOW        (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x28)))
#define MEMCTRL_SCSLR6_LOW        (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x2c)))
#define MEMCTRL_SCSLR7_LOW        (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x30)))
#define MEMCTRL_SMSKR0            (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x54)))
#define MEMCTRL_SMSKR1            (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x58)))
#define MEMCTRL_SMSKR2            (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x5c)))
#define MEMCTRL_SMSKR3            (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x60)))
#define MEMCTRL_SMSKR4            (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x64)))
#define MEMCTRL_SMSKR5            (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x68)))
#define MEMCTRL_SMSKR6            (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x6c)))
#define MEMCTRL_SMSKR7            (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x70)))
#define MEMCTRL_CSALIAS0_LOW      (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x74)))
#define MEMCTRL_CSALIAS1_LOW      (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x78)))
#define MEMCTRL_CSREMAP0_LOW      (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x84)))
#define MEMCTRL_CSREMAP1_LOW      (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x88)))
#define MEMCTRL_SMTMGR_SET0       (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x94)))
#define MEMCTRL_SMTMGR_SET1       (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x98)))
#define MEMCTRL_SMTMGR_SET2       (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0x9c)))
#define MEMCTRL_FLASH_TRPDR       (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0xa0)))
#define MEMCTRL_SMCTLR            (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0xa4)))
#define MEMCTRL_EXN_MODE_REG      (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0xac)))
#define MEMCTRL_COMP_TYPE         (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0xfc)))
#define MEMCTRL_COMP_VERSION      (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0xf8)))
#define MEMCTRL_COMP_PARAMS_1     (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0xf4)))
#define MEMCTRL_COMP_PARAMS_2     (*((volatile UINT32 *)(ahb_gpmc_DW_MEMCTL_BASE + 0xf0)))

#define MEMCTLahb_gpmc_MEMCTL_PING_1BIT_WR  (ahb_gpmc_MEMCTL_SCONR)

#define ahb_gpmc_CC_MEMCTL_VER_1_2A_COMPATIABLE_MODE        0
#define ahb_gpmc_CC_MEMCTL_H_DATA_WIDTH                     32
#define ahb_gpmc_CC_MEMCTL_H_ADDR_WIDTH                     32
#define ahb_gpmc_CC_MEMCTL_PIPE_ADDRESS_DECODER             0
#define ahb_gpmc_CC_MEMCTL_ADDR_FIFO_DEPTH                  4
#define ahb_gpmc_CC_MEMCTL_WRITE_FIFO_DEPTH                 8
#define ahb_gpmc_CC_MEMCTL_EBI_INTERFACE                    0
#define ahb_gpmc_CC_MEMCTL_DYNAMIC_RAM_TYPE                 6
#define ahb_gpmc_CC_MEMCTL_ENABLE_STATIC                    1
#define ahb_gpmc_CC_MEMCTL_N_CS                             2
#define ahb_gpmc_CC_MEMCTL_ENABLE_DATABUS_SHARING           0
#define ahb_gpmc_CC_MEMCTL_ENABLE_ADDRBUS_SHARING           0
#define ahb_gpmc_CC_MEMCTL_HARD_WIRE_SDRAM_PARAMETERS       0
#define ahb_gpmc_CC_MEMCTL_HARD_WIRE_SYNCFLASH_PARAMETERS   0
#define ahb_gpmc_CC_MEMCTL_HARD_WIRE_STATIC_PARAMETERS      0
#define ahb_gpmc_CC_MEMCTL_HARD_WIRE_CHIPSELECT_PARAMETERS  0
#define ahb_gpmc_CC_MEMCTL_WRITE_PIPE                       0
#define ahb_gpmc_CC_MEMCTL_READ_PIPE                        2
#define ahb_gpmc_CC_MEMCTL_T_REF                            1040
#define ahb_gpmc_CC_MEMCTL_T_INIT                           8
#define ahb_gpmc_CC_MEMCTL_MAX_S_DATA_WIDTH                 32
#define ahb_gpmc_CC_MEMCTL_S_DATA_WIDTH                     32
#define ahb_gpmc_CC_MEMCTL_MAX_S_ADDR_WIDTH                 16
#define ahb_gpmc_CC_MEMCTL_MAX_S_BANK_ADDR_WIDTH            2
#define ahb_gpmc_CC_MEMCTL_HIGHER_ADDR_FOR_BANKS            0
#define ahb_gpmc_CC_MEMCTL_HIGHER_ADDR_FOR_SF_BANKS         0
#define ahb_gpmc_CC_MEMCTL_NUM_DQS                          4
#define ahb_gpmc_CC_MEMCTL_EXTENDED_MODE_REG                0x0
#define ahb_gpmc_CC_MEMCTL_SM_WRITE_PIPE                    0
#define ahb_gpmc_CC_MEMCTL_MAX_SM_DATA_WIDTH                32
#define ahb_gpmc_CC_MEMCTL_MAX_SM_ADDR_WIDTH                29
#define ahb_gpmc_CC_MEMCTL_T_RPD                            200
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT0_MEM                 2
#define ahb_gpmc_CC_MEMCTL_REG_SELECT0                      0
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT0_BASE_ADDRESS        0x20000000
#define ahb_gpmc_CC_MEMCTL_BLOCK_SIZE0                      14
#define ahb_gpmc_CC_MEMCTL_CHIP_SEL0_REMAP_ENABLE           1
#define ahb_gpmc_CC_MEMCTL_CHIP_SEL0_ALIAS_ENABLE           0
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT0_ALIAS_ADDRESS       0x80000000
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT0_REMAP_ADDRESS       0x0
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT1_MEM                 1
#define ahb_gpmc_CC_MEMCTL_REG_SELECT1                      1
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT1_BASE_ADDRESS        0x0
#define ahb_gpmc_CC_MEMCTL_BLOCK_SIZE1                      14
#define ahb_gpmc_CC_MEMCTL_CHIP_SEL1_REMAP_ENABLE           1
#define ahb_gpmc_CC_MEMCTL_CHIP_SEL1_ALIAS_ENABLE           0
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT1_ALIAS_ADDRESS       0x18000000
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT1_REMAP_ADDRESS       0x20000000
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT2_MEM                 1
#define ahb_gpmc_CC_MEMCTL_REG_SELECT2                      0
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT2_BASE_ADDRESS        0x20000000
#define ahb_gpmc_CC_MEMCTL_BLOCK_SIZE2                      1
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT3_MEM                 2
#define ahb_gpmc_CC_MEMCTL_REG_SELECT3                      1
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT3_BASE_ADDRESS        0x30000000
#define ahb_gpmc_CC_MEMCTL_BLOCK_SIZE3                      1
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT4_MEM                 3
#define ahb_gpmc_CC_MEMCTL_REG_SELECT4                      2
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT4_BASE_ADDRESS        0x40000000
#define ahb_gpmc_CC_MEMCTL_BLOCK_SIZE4                      1
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT5_MEM                 0
#define ahb_gpmc_CC_MEMCTL_REG_SELECT5                      1
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT5_BASE_ADDRESS        0x50000000
#define ahb_gpmc_CC_MEMCTL_BLOCK_SIZE5                      1
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT6_MEM                 0
#define ahb_gpmc_CC_MEMCTL_REG_SELECT6                      1
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT6_BASE_ADDRESS        0x60000000
#define ahb_gpmc_CC_MEMCTL_BLOCK_SIZE6                      1
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT7_MEM                 0
#define ahb_gpmc_CC_MEMCTL_REG_SELECT7                      1
#define ahb_gpmc_CC_MEMCTL_CHIP_SELECT7_BASE_ADDRESS        0x70000000
#define ahb_gpmc_CC_MEMCTL_BLOCK_SIZE7                      1
#define ahb_gpmc_CC_MEMCTL_S_ROW_ADDR_WIDTH                 12
#define ahb_gpmc_CC_MEMCTL_S_COL_ADDR_WIDTH                 9
#define ahb_gpmc_CC_MEMCTL_S_BANK_ADDR_WIDTH                2
#define ahb_gpmc_CC_MEMCTL_A8_FOR_PRECHARGE                 0
#define ahb_gpmc_CC_MEMCTL_OPEN_BANKS                       4
#define ahb_gpmc_CC_MEMCTL_CAS_LATENCY                      3
#define ahb_gpmc_CC_MEMCTL_T_RAS_MIN                        6
#define ahb_gpmc_CC_MEMCTL_T_RCD                            3
#define ahb_gpmc_CC_MEMCTL_T_RP                             3
#define ahb_gpmc_CC_MEMCTL_T_WR                             3
#define ahb_gpmc_CC_MEMCTL_T_RCAR                           10
#define ahb_gpmc_CC_MEMCTL_T_XSR                            250
#define ahb_gpmc_CC_MEMCTL_T_RC                             10
#define ahb_gpmc_CC_MEMCTL_NUM_INIT_REF                     8
#define ahb_gpmc_CC_MEMCTL_T_WTR                            1
#define ahb_gpmc_CC_MEMCTL_S_READY_VALID                    0
#define ahb_gpmc_CC_MEMCTL_SF_ROW_ADDR_WIDTH                12
#define ahb_gpmc_CC_MEMCTL_SF_COL_ADDR_WIDTH                9
#define ahb_gpmc_CC_MEMCTL_SF_BANK_ADDR_WIDTH               2
#define ahb_gpmc_CC_MEMCTL_SF_CAS_LATENCY                   3
#define ahb_gpmc_CC_MEMCTL_SF_T_RCD                         3
#define ahb_gpmc_CC_MEMCTL_SF_T_RC                          10
#define ahb_gpmc_CC_MEMCTL_T_RC_SET0                        14
#define ahb_gpmc_CC_MEMCTL_T_AS_SET0                        3
#define ahb_gpmc_CC_MEMCTL_T_WR_SET0                        3
#define ahb_gpmc_CC_MEMCTL_T_WP_SET0                        11
#define ahb_gpmc_CC_MEMCTL_T_BTA_SET0                       7
#define ahb_gpmc_CC_MEMCTL_T_PRC_SET0                       5
#define ahb_gpmc_CC_MEMCTL_PAGE_MODE_SET0                   1
#define ahb_gpmc_CC_MEMCTL_PAGE_SIZE_SET0                   2
#define ahb_gpmc_CC_MEMCTL_READY_MODE_SET0                  0
#define ahb_gpmc_CC_MEMCTL_LOW_FREQ_DEV_SET0                0
#define ahb_gpmc_CC_MEMCTL_SM_READ_PIPE_SET0                0
#define ahb_gpmc_CC_MEMCTL_SM_DATA_WIDTH_SET0               32
#define ahb_gpmc_CC_MEMCTL_T_RC_SET1                        1
#define ahb_gpmc_CC_MEMCTL_T_AS_SET1                        1
#define ahb_gpmc_CC_MEMCTL_T_WR_SET1                        1
#define ahb_gpmc_CC_MEMCTL_T_WP_SET1                        1
#define ahb_gpmc_CC_MEMCTL_T_BTA_SET1                       1
#define ahb_gpmc_CC_MEMCTL_T_PRC_SET1                       1
#define ahb_gpmc_CC_MEMCTL_PAGE_MODE_SET1                   0
#define ahb_gpmc_CC_MEMCTL_PAGE_SIZE_SET1                   0
#define ahb_gpmc_CC_MEMCTL_READY_MODE_SET1                  0
#define ahb_gpmc_CC_MEMCTL_LOW_FREQ_DEV_SET1                0
#define ahb_gpmc_CC_MEMCTL_SM_READ_PIPE_SET1                0
#define ahb_gpmc_CC_MEMCTL_SM_DATA_WIDTH_SET1               32
#define ahb_gpmc_CC_MEMCTL_T_RC_SET2                        1
#define ahb_gpmc_CC_MEMCTL_T_AS_SET2                        1
#define ahb_gpmc_CC_MEMCTL_T_WR_SET2                        1
#define ahb_gpmc_CC_MEMCTL_T_WP_SET2                        1
#define ahb_gpmc_CC_MEMCTL_T_BTA_SET2                       1
#define ahb_gpmc_CC_MEMCTL_T_PRC_SET2                       1
#define ahb_gpmc_CC_MEMCTL_PAGE_MODE_SET2                   0
#define ahb_gpmc_CC_MEMCTL_PAGE_SIZE_SET2                   0
#define ahb_gpmc_CC_MEMCTL_READY_MODE_SET2                  1
#define ahb_gpmc_CC_MEMCTL_LOW_FREQ_DEV_SET2                0
#define ahb_gpmc_CC_MEMCTL_SM_READ_PIPE_SET2                1
#define ahb_gpmc_CC_MEMCTL_SM_DATA_WIDTH_SET2               32
#define ahb_gpmc_CC_MEMCTL_USE_MOBILE_DDR                   0
#define ahb_gpmc_CC_MEMCTL_COMP_VERSION                     0x3237392a
#define ahb_gpmc_CC_MEMCTL_COMP_TYPE                        0x44572110

#endif
