//******************** (C) COPYRIGHT 2019 SmartLogic*******************************
// FileName           : dw_apb_wdt.h
// Author             : lijian, jian.li@smartlogictech.com
// Date First Issued  : 2019-03-29 02:39:38 PM
// Last Modified      : 2019-03-29 02:42:38 PM
// Description        :
// ------------------------------------------------------------
// Modification History:
// Version    Date       Author    Modification Description
//
//**********************************************************************************
#ifndef __WDT_H__
#define __WDT_H__

#define DW_APB_WDT_BASE                    0x031c0000
#define WDTControlReg_Offset               0x00
#define WDTTimeoutRangeReg_Offset          0x04
#define WDTCurrentCounterValueReg_Offset   0x08
#define WDTCounterResetReg_Offset          0x0C
#define WDTStatReg_Offset                  0x10
#define WDTEOIReg_Offset                   0x14
#define WDTVIDReg_Offset                   0x18

#define WDTCOMP_PARAMS_5_Offset            0xe4
#define WDTCOMP_PARAMS_4_Offset            0xe8
#define WDTCOMP_PARAMS_3_Offset            0xec
#define WDTCOMP_PARAMS_2_Offset            0xf0
#define WDTCOMP_PARAMS_1_Offset            0xf4
#define WDTCOMP_VERSION_Offset             0xf8
#define WDTCOMP_TYPE_Offset                0xfc

#define WDT_CR                    (*((volatile UINT32 *)(DW_APB_WDT_BASE + WDTControlReg_Offset            )))
#define WDT_TORR                  (*((volatile UINT32 *)(DW_APB_WDT_BASE + WDTTimeoutRangeReg_Offset       )))
#define WDT_CCVR                  (*((volatile UINT32 *)(DW_APB_WDT_BASE + WDTCurrentCounterValueReg_Offset)))
#define WDT_CRR                   (*((volatile UINT32 *)(DW_APB_WDT_BASE + WDTCounterResetReg_Offset       )))
#define WDT_STAT                  (*((volatile UINT32 *)(DW_APB_WDT_BASE + WDTStatReg_Offset               )))
#define WDT_EOI                   (*((volatile UINT32 *)(DW_APB_WDT_BASE + WDTEOIReg_Offset                )))
#define WDT_VID                   (*((volatile UINT32 *)(DW_APB_WDT_BASE + WDTVIDReg_Offset                )))
#define WDT_COMP_PARAMS_5         (*((volatile UINT32 *)(DW_APB_WDT_BASE + WDTCOMP_PARAMS_5_Offset         )))
#define WDT_COMP_PARAMS_4         (*((volatile UINT32 *)(DW_APB_WDT_BASE + WDTCOMP_PARAMS_4_Offset         )))
#define WDT_COMP_PARAMS_3         (*((volatile UINT32 *)(DW_APB_WDT_BASE + WDTCOMP_PARAMS_3_Offset         )))
#define WDT_COMP_PARAMS_2         (*((volatile UINT32 *)(DW_APB_WDT_BASE + WDTCOMP_PARAMS_2_Offset         )))
#define WDT_COMP_PARAMS_1         (*((volatile UINT32 *)(DW_APB_WDT_BASE + WDTCOMP_PARAMS_1_Offset         )))
#define WDT_COMP_VERSION          (*((volatile UINT32 *)(DW_APB_WDT_BASE + WDTCOMP_VERSION_Offset          )))
#define WDT_COMP_TYPE             (*((volatile UINT32 *)(DW_APB_WDT_BASE + WDTCOMP_TYPE_Offset             )))
#define WDTPING_1BIT_WR           (WDT_CR

#endif
