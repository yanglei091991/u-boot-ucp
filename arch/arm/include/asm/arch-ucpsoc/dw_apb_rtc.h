//******************** (C) COPYRIGHT 2019 SmartLogic*******************************
// FileName           : dw_apb_rtc.h
// Author             : lijian, jian.li@smartlogictech.com
// Date First Issued  : 2019-03-29 02:43:13 PM
// Last Modified      : 2019-03-29 03:40:24 PM
// Description        :
// ------------------------------------------------------------
// Modification History:
// Version    Date       Author    Modification Description
//
//**********************************************************************************
#ifndef __RTC_H__
#define __RTC_H__

#define DW_APB_RTC_BASE            0x031c8000

#define RTCCounterDataReg_Offset   0x00
#define RTCMatchReg_Offset         0x04
#define RTCCounterLoadReg_Offset   0x08
#define RTCControlReg_Offset       0x0C
#define RTCStatReg_Offset          0x10
#define RTCRawStatReg_Offset       0x14
#define RTCEOIReg_Offset           0x18
#define RTCVIDReg_Offset           0x1C

#define RTCCounterDataReg   (*((volatile UINT32 *)(DW_APB_RTC_BASE + RTCCounterDataReg_Offset  )))
#define RTCMatchReg         (*((volatile UINT32 *)(DW_APB_RTC_BASE + RTCMatchReg_Offset        )))
#define RTCCounterLoadReg   (*((volatile UINT32 *)(DW_APB_RTC_BASE + RTCCounterLoadReg_Offset  )))
#define RTCControlReg       (*((volatile UINT32 *)(DW_APB_RTC_BASE + RTCControlReg_Offset      )))
#define RTCStatReg          (*((volatile UINT32 *)(DW_APB_RTC_BASE + RTCStatReg_Offset         )))
#define RTCRawStatReg       (*((volatile UINT32 *)(DW_APB_RTC_BASE + RTCRawStatReg_Offset      )))
#define RTCEOIReg           (*((volatile UINT32 *)(DW_APB_RTC_BASE + RTCEOIReg_Offset          )))
#define RTCVIDReg           (*((volatile UINT32 *)(DW_APB_RTC_BASE + RTCVIDReg_Offset          )))

#define RTCPING_1BIT_WR        (RTCMatchReg                                                )


#endif
