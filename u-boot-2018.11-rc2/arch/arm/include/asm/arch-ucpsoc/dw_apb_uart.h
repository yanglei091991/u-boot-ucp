//******************** (C) COPYRIGHT 2019 SmartLogic*******************************
// FileName           : dw_apb_UART.h
// Author             : lijian, jian.li@smartlogictech.com
// Date First Issued  : 2019-03-29 03:53:32 PM
// Last Modified      : 2019-03-29 03:59:12 PM
// Description        :
// ------------------------------------------------------------
// Modification History:
// Version    Date       Author    Modification Description
//
//**********************************************************************************
#ifndef __UART_H__
#define __UART_H__

#define UART0_DW_APB_UART_BASE 0x02108000
#define UART1_DW_APB_UART_BASE 0x02110000
#define UART2_DW_APB_UART_BASE 0x049e0000
#define UART3_DW_APB_UART_BASE 0x049f0000

#define UART0_UARTReceiveBufferReg_Offset               0x00
#define UART0_UARTTransmitHoldingReg_Offset             0x00
#define UART0_UARTDivisorLatchLow_Offset                0x00
#define UART0_UARTInterruptEnableReg_Offset             0x04
#define UART0_UARTDivisorLatchHigh_Offset               0x04
#define UART0_UARTInterruptIdentificationReg_Offset     0x08
#define UART0_UARTFIFOControlReg_Offset                 0x08
#define UART0_UARTLineControlReg_Offset                 0x0C
#define UART0_UARTModemControlReg_Offset                0x10
#define UART0_UARTLineStatusReg_Offset                  0x14
#define UART0_UARTModemStatusReg_Offset                 0x18
#define UART0_UARTScratchpadReg_Offset                  0x1C
#define UART0_UARTLowPowerDivisorLatchLow_Offset        0x20
#define UART0_UARTLowPowerDivisorLatchHigh_Offset       0x24
#define UART0_UARTShadowReceiveBufferRegLow_Offset      0x30
#define UART0_UARTShadowReceiveBufferRegHigh_Offset     0x6C
#define UART0_UARTShadowTransmitHoldingRegLow_Offset    0x30
#define UART0_UARTShadowTransmitHoldingRegHigh_Offset   0x6C
#define UART0_UARTFIFOAccessReg_Offset                  0x70
#define UART0_UARTTransmitFIFOReadReg_Offset            0x74
#define UART0_UARTReceiveFIFOWriteReg_Offset            0x78
#define UART0_UARTUARTStatusReg_Offset                  0x7C
#define UART0_UARTTransmitFIFOLevelReg_Offset           0x80
#define UART0_UARTReceiveFIFOLevelReg_Offset            0x84
#define UART0_UARTSoftwareResetReg_Offset               0x88
#define UART0_UARTShadowRequestToSendReg_Offset         0x8C
#define UART0_UARTShadowBreakControlReg_Offset          0x90
#define UART0_UARTShadowDMAModeReg_Offset               0x94
#define UART0_UARTShadowFIFOEnableReg_Offset            0x98
#define UART0_UARTShadowRCVRTriggerReg_Offset           0x9C
#define UART0_UARTShadowTXEmptyTriggerReg_Offset        0xA0
#define UART0_UARTHaltTXReg_Offset                      0xA4
#define UART0_UARTDMASAReg_Offset                       0xA8
#define UART0_UARTCIDReg_Offset                         0xF4
#define UART0_UARTCVReg_Offset                          0xF8
#define UART0_UARTPIDReg_Offset                         0xFC

#define UART0_UARTReceiveBufferReg             (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTReceiveBufferReg_Offset            )))
#define UART0_UARTTransmitHoldingReg           (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTTransmitHoldingReg_Offset          )))
#define UART0_UARTDivisorLatchLow              (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTDivisorLatchLow_Offset             )))
#define UART0_UARTInterruptEnableReg           (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTInterruptEnableReg_Offset          )))
#define UART0_UARTDivisorLatchHigh             (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTDivisorLatchHigh_Offset            )))
#define UART0_UARTInterruptIdentificationReg   (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTInterruptIdentificationReg_Offset  )))
#define UART0_UARTFIFOControlReg               (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTFIFOControlReg_Offset              )))
#define UART0_UARTLineControlReg               (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTLineControlReg_Offset              )))
#define UART0_UARTModemControlReg              (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTModemControlReg_Offset             )))
#define UART0_UARTLineStatusReg                (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTLineStatusReg_Offset               )))
#define UART0_UARTModemStatusReg               (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTModemStatusReg_Offset              )))
#define UART0_UARTScratchpadReg                (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTScratchpadReg_Offset               )))
#define UART0_UARTLowPowerDivisorLatchLowReg   (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTLowPowerDivisorLatchLow_Offset     )))
#define UART0_UARTLowPowerDivisorLatchHighReg  (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTLowPowerDivisorLatchHigh_Offset    )))
#define UART0_UARTShadowReceiveBufferRegLow    (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTShadowReceiveBufferRegLow_Offset   )))
#define UART0_UARTShadowReceiveBufferRegHigh   (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTShadowReceiveBufferRegHigh_Offset  )))
#define UART0_UARTShadowTransmitHoldingRegLow  (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTShadowTransmitHoldingRegLow_Offset )))
#define UART0_UARTShadowTransmitHoldingRegHigh (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTShadowTransmitHoldingRegHigh_Offset)))
#define UART0_UARTFIFOAccessReg                (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTFIFOAccessReg_Offset               )))
#define UART0_UARTTransmitFIFOReadReg          (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTTransmitFIFOReadReg_Offset         )))
#define UART0_UARTReceiveFIFOWriteReg          (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTReceiveFIFOWriteReg_Offset         )))
#define UART0_UARTUARTStatusReg                (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTUARTStatusReg_Offset               )))
#define UART0_UARTTransmitFIFOLevelReg         (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTTransmitFIFOLevelReg_Offset        )))
#define UART0_UARTReceiveFIFOLevelReg          (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTReceiveFIFOLevelReg_Offset         )))
#define UART0_UARTSoftwareResetReg             (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTSoftwareResetReg_Offset            )))
#define UART0_UARTShadowRequestToSendReg       (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTShadowRequestToSendReg_Offset      )))
#define UART0_UARTShadowBreakControlReg        (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTShadowBreakControlReg_Offset       )))
#define UART0_UARTShadowDMAModeReg             (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTShadowDMAModeReg_Offset            )))
#define UART0_UARTShadowFIFOEnableReg          (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTShadowFIFOEnableReg_Offset         )))
#define UART0_UARTShadowRCVRTriggerReg         (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTShadowRCVRTriggerReg_Offset        )))
#define UART0_UARTShadowTXEmptyTriggerReg      (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTShadowTXEmptyTriggerReg_Offset     )))
#define UART0_UARTHaltTXReg                    (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTHaltTXReg_Offset                   )))
#define UART0_UARTDMASAReg                     (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTDMASAReg_Offset                    )))
#define UART0_UARTCIDReg                       (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTCIDReg_Offset                      )))
#define UART0_UARTCVReg                        (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTCVReg_Offset                       )))
#define UART0_UARTPIDReg                       (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTPIDReg_Offset                      )))
#define UART0_UART_RBR             	           (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTReceiveBufferReg_Offset            )))
#define UART0_UART_THR             	           (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTTransmitHoldingReg_Offset          )))
#define UART0_UART_DLL             	           (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTDivisorLatchLow_Offset             )))
#define UART0_UART_IER             	           (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTInterruptEnableReg_Offset          )))
#define UART0_UART_DLH             	           (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTDivisorLatchHigh_Offset            )))
#define UART0_UART_IIR             	           (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTInterruptIdentificationReg_Offset  )))
#define UART0_UART_FCR             	           (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTFIFOControlReg_Offset              )))
#define UART0_UART_LCR             	           (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTLineControlReg_Offset              )))
#define UART0_UART_MCR             	           (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTModemControlReg_Offset             )))
#define UART0_UART_LSR             	           (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTLineStatusReg_Offset               )))
#define UART0_UART_MSR             	           (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTModemStatusReg_Offset              )))
#define UART0_UART_SCR             	           (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTScratchpadReg_Offset               )))
#define UART0_UART_LPDLL           	           (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTLowPowerDivisorLatchLow_Offset     )))
#define UART0_UART_LPDLH           	           (*((volatile UINT32 *)(UART0_DW_APB_UART_BASE + UART0_UARTLowPowerDivisorLatchHigh_Offset    )))
#define UARTUART0_PING_1BIT_WR (UART0_UART_LCR)
#define UART0_CC_UART_APB_DATA_WIDTH        32
#define UART0_CC_UART_MAX_APB_DATA_WIDTH    32
#define UART0_CC_UART_FIFO_MODE             16
#define UART0_CC_UART_MEM_SELECT            1
#define UART0_CC_UART_MEM_MODE              0
#define UART0_CC_UART_CLOCK_MODE            2
#define UART0_CC_UART_AFCE_MODE             0x1
#define UART0_CC_UART_THRE_MODE             0x1
#define UART0_CC_UART_SIR_MODE              0x0
#define UART0_CC_UART_CLK_GATE_EN           0
#define UART0_CC_UART_FIFO_ACCESS           0x1
#define UART0_CC_UART_DMA_EXTRA             0x1
#define UART0_CC_UART_DMA_POL               0
#define UART0_CC_UART_SIR_LP_MODE           0x0
#define UART0_CC_UART_DEBUG                 0
#define UART0_CC_UART_BAUD_CLK              1
#define UART0_CC_UART_ADDITIONAL_FEATURES   0x0
#define UART0_CC_UART_FIFO_STAT             0x0
#define UART0_CC_UART_SHADOW                0x0
#define UART0_CC_UART_ADD_ENCODED_PARAMS    0x0
#define UART0_CC_UART_LATCH_MODE            0
#define UART0_CC_UART_ADDR_SLICE_LHS        8
#define UART0_CC_UART_COMP_VERSION          0x3331342a

#define UART1_UARTReceiveBufferReg_Offset               0x00
#define UART1_UARTTransmitHoldingReg_Offset             0x00
#define UART1_UARTDivisorLatchLow_Offset                0x00
#define UART1_UARTInterruptEnableReg_Offset             0x04
#define UART1_UARTDivisorLatchHigh_Offset               0x04
#define UART1_UARTInterruptIdentificationReg_Offset     0x08
#define UART1_UARTFIFOControlReg_Offset                 0x08
#define UART1_UARTLineControlReg_Offset                 0x0C
#define UART1_UARTModemControlReg_Offset                0x10
#define UART1_UARTLineStatusReg_Offset                  0x14
#define UART1_UARTModemStatusReg_Offset                 0x18
#define UART1_UARTScratchpadReg_Offset                  0x1C
#define UART1_UARTLowPowerDivisorLatchLow_Offset        0x20
#define UART1_UARTLowPowerDivisorLatchHigh_Offset       0x24
#define UART1_UARTShadowReceiveBufferRegLow_Offset      0x30
#define UART1_UARTShadowReceiveBufferRegHigh_Offset     0x6C
#define UART1_UARTShadowTransmitHoldingRegLow_Offset    0x30
#define UART1_UARTShadowTransmitHoldingRegHigh_Offset   0x6C
#define UART1_UARTFIFOAccessReg_Offset                  0x70
#define UART1_UARTTransmitFIFOReadReg_Offset            0x74
#define UART1_UARTReceiveFIFOWriteReg_Offset            0x78
#define UART1_UARTUARTStatusReg_Offset                  0x7C
#define UART1_UARTTransmitFIFOLevelReg_Offset           0x80
#define UART1_UARTReceiveFIFOLevelReg_Offset            0x84
#define UART1_UARTSoftwareResetReg_Offset               0x88
#define UART1_UARTShadowRequestToSendReg_Offset         0x8C
#define UART1_UARTShadowBreakControlReg_Offset          0x90
#define UART1_UARTShadowDMAModeReg_Offset               0x94
#define UART1_UARTShadowFIFOEnableReg_Offset            0x98
#define UART1_UARTShadowRCVRTriggerReg_Offset           0x9C
#define UART1_UARTShadowTXEmptyTriggerReg_Offset        0xA0
#define UART1_UARTHaltTXReg_Offset                      0xA4
#define UART1_UARTDMASAReg_Offset                       0xA8
#define UART1_UARTCIDReg_Offset                         0xF4
#define UART1_UARTCVReg_Offset                          0xF8
#define UART1_UARTPIDReg_Offset                         0xFC

#define UART1_UARTReceiveBufferReg             (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTReceiveBufferReg_Offset            )))
#define UART1_UARTTransmitHoldingReg           (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTTransmitHoldingReg_Offset          )))
#define UART1_UARTDivisorLatchLow              (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTDivisorLatchLow_Offset             )))
#define UART1_UARTInterruptEnableReg           (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTInterruptEnableReg_Offset          )))
#define UART1_UARTDivisorLatchHigh             (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTDivisorLatchHigh_Offset            )))
#define UART1_UARTInterruptIdentificationReg   (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTInterruptIdentificationReg_Offset  )))
#define UART1_UARTFIFOControlReg               (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTFIFOControlReg_Offset              )))
#define UART1_UARTLineControlReg               (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTLineControlReg_Offset              )))
#define UART1_UARTModemControlReg              (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTModemControlReg_Offset             )))
#define UART1_UARTLineStatusReg                (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTLineStatusReg_Offset               )))
#define UART1_UARTModemStatusReg               (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTModemStatusReg_Offset              )))
#define UART1_UARTScratchpadReg                (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTScratchpadReg_Offset               )))
#define UART1_UARTLowPowerDivisorLatchLowReg   (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTLowPowerDivisorLatchLow_Offset     )))
#define UART1_UARTLowPowerDivisorLatchHighReg  (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTLowPowerDivisorLatchHigh_Offset    )))
#define UART1_UARTShadowReceiveBufferRegLow    (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTShadowReceiveBufferRegLow_Offset   )))
#define UART1_UARTShadowReceiveBufferRegHigh   (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTShadowReceiveBufferRegHigh_Offset  )))
#define UART1_UARTShadowTransmitHoldingRegLow  (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTShadowTransmitHoldingRegLow_Offset )))
#define UART1_UARTShadowTransmitHoldingRegHigh (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTShadowTransmitHoldingRegHigh_Offset)))
#define UART1_UARTFIFOAccessReg                (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTFIFOAccessReg_Offset               )))
#define UART1_UARTTransmitFIFOReadReg          (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTTransmitFIFOReadReg_Offset         )))
#define UART1_UARTReceiveFIFOWriteReg          (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTReceiveFIFOWriteReg_Offset         )))
#define UART1_UARTUARTStatusReg                (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTUARTStatusReg_Offset               )))
#define UART1_UARTTransmitFIFOLevelReg         (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTTransmitFIFOLevelReg_Offset        )))
#define UART1_UARTReceiveFIFOLevelReg          (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTReceiveFIFOLevelReg_Offset         )))
#define UART1_UARTSoftwareResetReg             (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTSoftwareResetReg_Offset            )))
#define UART1_UARTShadowRequestToSendReg       (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTShadowRequestToSendReg_Offset      )))
#define UART1_UARTShadowBreakControlReg        (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTShadowBreakControlReg_Offset       )))
#define UART1_UARTShadowDMAModeReg             (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTShadowDMAModeReg_Offset            )))
#define UART1_UARTShadowFIFOEnableReg          (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTShadowFIFOEnableReg_Offset         )))
#define UART1_UARTShadowRCVRTriggerReg         (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTShadowRCVRTriggerReg_Offset        )))
#define UART1_UARTShadowTXEmptyTriggerReg      (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTShadowTXEmptyTriggerReg_Offset     )))
#define UART1_UARTHaltTXReg                    (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTHaltTXReg_Offset                   )))
#define UART1_UARTDMASAReg                     (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTDMASAReg_Offset                    )))
#define UART1_UARTCIDReg                       (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTCIDReg_Offset                      )))
#define UART1_UARTCVReg                        (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTCVReg_Offset                       )))
#define UART1_UARTPIDReg                       (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTPIDReg_Offset                      )))
#define UART1_UART_RBR             	           (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTReceiveBufferReg_Offset            )))
#define UART1_UART_THR             	           (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTTransmitHoldingReg_Offset          )))
#define UART1_UART_DLL             	           (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTDivisorLatchLow_Offset             )))
#define UART1_UART_IER             	           (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTInterruptEnableReg_Offset          )))
#define UART1_UART_DLH             	           (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTDivisorLatchHigh_Offset            )))
#define UART1_UART_IIR             	           (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTInterruptIdentificationReg_Offset  )))
#define UART1_UART_FCR             	           (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTFIFOControlReg_Offset              )))
#define UART1_UART_LCR             	           (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTLineControlReg_Offset              )))
#define UART1_UART_MCR             	           (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTModemControlReg_Offset             )))
#define UART1_UART_LSR             	           (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTLineStatusReg_Offset               )))
#define UART1_UART_MSR             	           (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTModemStatusReg_Offset              )))
#define UART1_UART_SCR             	           (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTScratchpadReg_Offset               )))
#define UART1_UART_LPDLL           	           (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTLowPowerDivisorLatchLow_Offset     )))
#define UART1_UART_LPDLH           	           (*((volatile UINT32 *)(UART1_DW_APB_UART_BASE + UART1_UARTLowPowerDivisorLatchHigh_Offset    )))
#define UARTUART1_PING_1BIT_WR (UART1_UART_LCR)
#define UART1_CC_UART_APB_DATA_WIDTH        32
#define UART1_CC_UART_MAX_APB_DATA_WIDTH    32
#define UART1_CC_UART_FIFO_MODE             16
#define UART1_CC_UART_MEM_SELECT            1
#define UART1_CC_UART_MEM_MODE              0
#define UART1_CC_UART_CLOCK_MODE            2
#define UART1_CC_UART_AFCE_MODE             0x1
#define UART1_CC_UART_THRE_MODE             0x1
#define UART1_CC_UART_SIR_MODE              0x1
#define UART1_CC_UART_CLK_GATE_EN           0
#define UART1_CC_UART_FIFO_ACCESS           0x1
#define UART1_CC_UART_DMA_EXTRA             0x1
#define UART1_CC_UART_DMA_POL               0
#define UART1_CC_UART_SIR_LP_MODE           0x0
#define UART1_CC_UART_DEBUG                 0
#define UART1_CC_UART_BAUD_CLK              1
#define UART1_CC_UART_ADDITIONAL_FEATURES   0x0
#define UART1_CC_UART_FIFO_STAT             0x0
#define UART1_CC_UART_SHADOW                0x0
#define UART1_CC_UART_ADD_ENCODED_PARAMS    0x0
#define UART1_CC_UART_LATCH_MODE            0
#define UART1_CC_UART_ADDR_SLICE_LHS        8
#define UART1_CC_UART_COMP_VERSION          0x3331342a

#define UART2_UARTReceiveBufferReg_Offset               0x00
#define UART2_UARTTransmitHoldingReg_Offset             0x00
#define UART2_UARTDivisorLatchLow_Offset                0x00
#define UART2_UARTInterruptEnableReg_Offset             0x04
#define UART2_UARTDivisorLatchHigh_Offset               0x04
#define UART2_UARTInterruptIdentificationReg_Offset     0x08
#define UART2_UARTFIFOControlReg_Offset                 0x08
#define UART2_UARTLineControlReg_Offset                 0x0C
#define UART2_UARTModemControlReg_Offset                0x10
#define UART2_UARTLineStatusReg_Offset                  0x14
#define UART2_UARTModemStatusReg_Offset                 0x18
#define UART2_UARTScratchpadReg_Offset                  0x1C
#define UART2_UARTLowPowerDivisorLatchLow_Offset        0x20
#define UART2_UARTLowPowerDivisorLatchHigh_Offset       0x24
#define UART2_UARTShadowReceiveBufferRegLow_Offset      0x30
#define UART2_UARTShadowReceiveBufferRegHigh_Offset     0x6C
#define UART2_UARTShadowTransmitHoldingRegLow_Offset    0x30
#define UART2_UARTShadowTransmitHoldingRegHigh_Offset   0x6C
#define UART2_UARTFIFOAccessReg_Offset                  0x70
#define UART2_UARTTransmitFIFOReadReg_Offset            0x74
#define UART2_UARTReceiveFIFOWriteReg_Offset            0x78
#define UART2_UARTUARTStatusReg_Offset                  0x7C
#define UART2_UARTTransmitFIFOLevelReg_Offset           0x80
#define UART2_UARTReceiveFIFOLevelReg_Offset            0x84
#define UART2_UARTSoftwareResetReg_Offset               0x88
#define UART2_UARTShadowRequestToSendReg_Offset         0x8C
#define UART2_UARTShadowBreakControlReg_Offset          0x90
#define UART2_UARTShadowDMAModeReg_Offset               0x94
#define UART2_UARTShadowFIFOEnableReg_Offset            0x98
#define UART2_UARTShadowRCVRTriggerReg_Offset           0x9C
#define UART2_UARTShadowTXEmptyTriggerReg_Offset        0xA0
#define UART2_UARTHaltTXReg_Offset                      0xA4
#define UART2_UARTDMASAReg_Offset                       0xA8
#define UART2_UARTCIDReg_Offset                         0xF4
#define UART2_UARTCVReg_Offset                          0xF8
#define UART2_UARTPIDReg_Offset                         0xFC

#define UART2_UARTReceiveBufferReg             (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTReceiveBufferReg_Offset            )))
#define UART2_UARTTransmitHoldingReg           (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTTransmitHoldingReg_Offset          )))
#define UART2_UARTDivisorLatchLow              (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTDivisorLatchLow_Offset             )))
#define UART2_UARTInterruptEnableReg           (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTInterruptEnableReg_Offset          )))
#define UART2_UARTDivisorLatchHigh             (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTDivisorLatchHigh_Offset            )))
#define UART2_UARTInterruptIdentificationReg   (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTInterruptIdentificationReg_Offset  )))
#define UART2_UARTFIFOControlReg               (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTFIFOControlReg_Offset              )))
#define UART2_UARTLineControlReg               (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTLineControlReg_Offset              )))
#define UART2_UARTModemControlReg              (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTModemControlReg_Offset             )))
#define UART2_UARTLineStatusReg                (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTLineStatusReg_Offset               )))
#define UART2_UARTModemStatusReg               (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTModemStatusReg_Offset              )))
#define UART2_UARTScratchpadReg                (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTScratchpadReg_Offset               )))
#define UART2_UARTLowPowerDivisorLatchLowReg   (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTLowPowerDivisorLatchLow_Offset     )))
#define UART2_UARTLowPowerDivisorLatchHighReg  (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTLowPowerDivisorLatchHigh_Offset    )))
#define UART2_UARTShadowReceiveBufferRegLow    (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTShadowReceiveBufferRegLow_Offset   )))
#define UART2_UARTShadowReceiveBufferRegHigh   (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTShadowReceiveBufferRegHigh_Offset  )))
#define UART2_UARTShadowTransmitHoldingRegLow  (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTShadowTransmitHoldingRegLow_Offset )))
#define UART2_UARTShadowTransmitHoldingRegHigh (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTShadowTransmitHoldingRegHigh_Offset)))
#define UART2_UARTFIFOAccessReg                (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTFIFOAccessReg_Offset               )))
#define UART2_UARTTransmitFIFOReadReg          (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTTransmitFIFOReadReg_Offset         )))
#define UART2_UARTReceiveFIFOWriteReg          (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTReceiveFIFOWriteReg_Offset         )))
#define UART2_UARTUARTStatusReg                (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTUARTStatusReg_Offset               )))
#define UART2_UARTTransmitFIFOLevelReg         (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTTransmitFIFOLevelReg_Offset        )))
#define UART2_UARTReceiveFIFOLevelReg          (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTReceiveFIFOLevelReg_Offset         )))
#define UART2_UARTSoftwareResetReg             (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTSoftwareResetReg_Offset            )))
#define UART2_UARTShadowRequestToSendReg       (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTShadowRequestToSendReg_Offset      )))
#define UART2_UARTShadowBreakControlReg        (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTShadowBreakControlReg_Offset       )))
#define UART2_UARTShadowDMAModeReg             (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTShadowDMAModeReg_Offset            )))
#define UART2_UARTShadowFIFOEnableReg          (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTShadowFIFOEnableReg_Offset         )))
#define UART2_UARTShadowRCVRTriggerReg         (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTShadowRCVRTriggerReg_Offset        )))
#define UART2_UARTShadowTXEmptyTriggerReg      (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTShadowTXEmptyTriggerReg_Offset     )))
#define UART2_UARTHaltTXReg                    (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTHaltTXReg_Offset                   )))
#define UART2_UARTDMASAReg                     (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTDMASAReg_Offset                    )))
#define UART2_UARTCIDReg                       (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTCIDReg_Offset                      )))
#define UART2_UARTCVReg                        (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTCVReg_Offset                       )))
#define UART2_UARTPIDReg                       (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTPIDReg_Offset                      )))
#define UART2_UART_RBR             	           (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTReceiveBufferReg_Offset            )))
#define UART2_UART_THR             	           (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTTransmitHoldingReg_Offset          )))
#define UART2_UART_DLL             	           (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTDivisorLatchLow_Offset             )))
#define UART2_UART_IER             	           (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTInterruptEnableReg_Offset          )))
#define UART2_UART_DLH             	           (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTDivisorLatchHigh_Offset            )))
#define UART2_UART_IIR             	           (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTInterruptIdentificationReg_Offset  )))
#define UART2_UART_FCR             	           (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTFIFOControlReg_Offset              )))
#define UART2_UART_LCR             	           (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTLineControlReg_Offset              )))
#define UART2_UART_MCR             	           (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTModemControlReg_Offset             )))
#define UART2_UART_LSR             	           (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTLineStatusReg_Offset               )))
#define UART2_UART_MSR             	           (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTModemStatusReg_Offset              )))
#define UART2_UART_SCR             	           (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTScratchpadReg_Offset               )))
#define UART2_UART_LPDLL           	           (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTLowPowerDivisorLatchLow_Offset     )))
#define UART2_UART_LPDLH           	           (*((volatile UINT32 *)(UART2_DW_APB_UART_BASE + UART2_UARTLowPowerDivisorLatchHigh_Offset    )))
#define UARTUART2_PING_1BIT_WR (UART2_UART_LCR)
#define UART2_CC_UART_APB_DATA_WIDTH        32
#define UART2_CC_UART_MAX_APB_DATA_WIDTH    32
#define UART2_CC_UART_FIFO_MODE             16
#define UART2_CC_UART_MEM_SELECT            1
#define UART2_CC_UART_MEM_MODE              0
#define UART2_CC_UART_CLOCK_MODE            2
#define UART2_CC_UART_AFCE_MODE             0x1
#define UART2_CC_UART_THRE_MODE             0x1
#define UART2_CC_UART_SIR_MODE              0x0
#define UART2_CC_UART_CLK_GATE_EN           0
#define UART2_CC_UART_FIFO_ACCESS           0x1
#define UART2_CC_UART_DMA_EXTRA             0x1
#define UART2_CC_UART_DMA_POL               0
#define UART2_CC_UART_SIR_LP_MODE           0x0
#define UART2_CC_UART_DEBUG                 0
#define UART2_CC_UART_BAUD_CLK              1
#define UART2_CC_UART_ADDITIONAL_FEATURES   0x0
#define UART2_CC_UART_FIFO_STAT             0x0
#define UART2_CC_UART_SHADOW                0x0
#define UART2_CC_UART_ADD_ENCODED_PARAMS    0x0
#define UART2_CC_UART_LATCH_MODE            0
#define UART2_CC_UART_ADDR_SLICE_LHS        8
#define UART2_CC_UART_COMP_VERSION          0x3331342a

#define UART3_UARTReceiveBufferReg_Offset               0x00
#define UART3_UARTTransmitHoldingReg_Offset             0x00
#define UART3_UARTDivisorLatchLow_Offset                0x00
#define UART3_UARTInterruptEnableReg_Offset             0x04
#define UART3_UARTDivisorLatchHigh_Offset               0x04
#define UART3_UARTInterruptIdentificationReg_Offset     0x08
#define UART3_UARTFIFOControlReg_Offset                 0x08
#define UART3_UARTLineControlReg_Offset                 0x0C
#define UART3_UARTModemControlReg_Offset                0x10
#define UART3_UARTLineStatusReg_Offset                  0x14
#define UART3_UARTModemStatusReg_Offset                 0x18
#define UART3_UARTScratchpadReg_Offset                  0x1C
#define UART3_UARTLowPowerDivisorLatchLow_Offset        0x20
#define UART3_UARTLowPowerDivisorLatchHigh_Offset       0x24
#define UART3_UARTShadowReceiveBufferRegLow_Offset      0x30
#define UART3_UARTShadowReceiveBufferRegHigh_Offset     0x6C
#define UART3_UARTShadowTransmitHoldingRegLow_Offset    0x30
#define UART3_UARTShadowTransmitHoldingRegHigh_Offset   0x6C
#define UART3_UARTFIFOAccessReg_Offset                  0x70
#define UART3_UARTTransmitFIFOReadReg_Offset            0x74
#define UART3_UARTReceiveFIFOWriteReg_Offset            0x78
#define UART3_UARTUARTStatusReg_Offset                  0x7C
#define UART3_UARTTransmitFIFOLevelReg_Offset           0x80
#define UART3_UARTReceiveFIFOLevelReg_Offset            0x84
#define UART3_UARTSoftwareResetReg_Offset               0x88
#define UART3_UARTShadowRequestToSendReg_Offset         0x8C
#define UART3_UARTShadowBreakControlReg_Offset          0x90
#define UART3_UARTShadowDMAModeReg_Offset               0x94
#define UART3_UARTShadowFIFOEnableReg_Offset            0x98
#define UART3_UARTShadowRCVRTriggerReg_Offset           0x9C
#define UART3_UARTShadowTXEmptyTriggerReg_Offset        0xA0
#define UART3_UARTHaltTXReg_Offset                      0xA4
#define UART3_UARTDMASAReg_Offset                       0xA8
#define UART3_UARTCIDReg_Offset                         0xF4
#define UART3_UARTCVReg_Offset                          0xF8
#define UART3_UARTPIDReg_Offset                         0xFC

#define UART3_UARTReceiveBufferReg             (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTReceiveBufferReg_Offset            )))
#define UART3_UARTTransmitHoldingReg           (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTTransmitHoldingReg_Offset          )))
#define UART3_UARTDivisorLatchLow              (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTDivisorLatchLow_Offset             )))
#define UART3_UARTInterruptEnableReg           (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTInterruptEnableReg_Offset          )))
#define UART3_UARTDivisorLatchHigh             (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTDivisorLatchHigh_Offset            )))
#define UART3_UARTInterruptIdentificationReg   (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTInterruptIdentificationReg_Offset  )))
#define UART3_UARTFIFOControlReg               (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTFIFOControlReg_Offset              )))
#define UART3_UARTLineControlReg               (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTLineControlReg_Offset              )))
#define UART3_UARTModemControlReg              (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTModemControlReg_Offset             )))
#define UART3_UARTLineStatusReg                (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTLineStatusReg_Offset               )))
#define UART3_UARTModemStatusReg               (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTModemStatusReg_Offset              )))
#define UART3_UARTScratchpadReg                (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTScratchpadReg_Offset               )))
#define UART3_UARTLowPowerDivisorLatchLowReg   (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTLowPowerDivisorLatchLow_Offset     )))
#define UART3_UARTLowPowerDivisorLatchHighReg  (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTLowPowerDivisorLatchHigh_Offset    )))
#define UART3_UARTShadowReceiveBufferRegLow    (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTShadowReceiveBufferRegLow_Offset   )))
#define UART3_UARTShadowReceiveBufferRegHigh   (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTShadowReceiveBufferRegHigh_Offset  )))
#define UART3_UARTShadowTransmitHoldingRegLow  (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTShadowTransmitHoldingRegLow_Offset )))
#define UART3_UARTShadowTransmitHoldingRegHigh (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTShadowTransmitHoldingRegHigh_Offset)))
#define UART3_UARTFIFOAccessReg                (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTFIFOAccessReg_Offset               )))
#define UART3_UARTTransmitFIFOReadReg          (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTTransmitFIFOReadReg_Offset         )))
#define UART3_UARTReceiveFIFOWriteReg          (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTReceiveFIFOWriteReg_Offset         )))
#define UART3_UARTUARTStatusReg                (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTUARTStatusReg_Offset               )))
#define UART3_UARTTransmitFIFOLevelReg         (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTTransmitFIFOLevelReg_Offset        )))
#define UART3_UARTReceiveFIFOLevelReg          (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTReceiveFIFOLevelReg_Offset         )))
#define UART3_UARTSoftwareResetReg             (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTSoftwareResetReg_Offset            )))
#define UART3_UARTShadowRequestToSendReg       (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTShadowRequestToSendReg_Offset      )))
#define UART3_UARTShadowBreakControlReg        (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTShadowBreakControlReg_Offset       )))
#define UART3_UARTShadowDMAModeReg             (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTShadowDMAModeReg_Offset            )))
#define UART3_UARTShadowFIFOEnableReg          (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTShadowFIFOEnableReg_Offset         )))
#define UART3_UARTShadowRCVRTriggerReg         (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTShadowRCVRTriggerReg_Offset        )))
#define UART3_UARTShadowTXEmptyTriggerReg      (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTShadowTXEmptyTriggerReg_Offset     )))
#define UART3_UARTHaltTXReg                    (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTHaltTXReg_Offset                   )))
#define UART3_UARTDMASAReg                     (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTDMASAReg_Offset                    )))
#define UART3_UARTCIDReg                       (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTCIDReg_Offset                      )))
#define UART3_UARTCVReg                        (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTCVReg_Offset                       )))
#define UART3_UARTPIDReg                       (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTPIDReg_Offset                      )))
#define UART3_UART_RBR             	           (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTReceiveBufferReg_Offset            )))
#define UART3_UART_THR             	           (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTTransmitHoldingReg_Offset          )))
#define UART3_UART_DLL             	           (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTDivisorLatchLow_Offset             )))
#define UART3_UART_IER             	           (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTInterruptEnableReg_Offset          )))
#define UART3_UART_DLH             	           (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTDivisorLatchHigh_Offset            )))
#define UART3_UART_IIR             	           (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTInterruptIdentificationReg_Offset  )))
#define UART3_UART_FCR             	           (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTFIFOControlReg_Offset              )))
#define UART3_UART_LCR             	           (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTLineControlReg_Offset              )))
#define UART3_UART_MCR             	           (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTModemControlReg_Offset             )))
#define UART3_UART_LSR             	           (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTLineStatusReg_Offset               )))
#define UART3_UART_MSR             	           (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTModemStatusReg_Offset              )))
#define UART3_UART_SCR             	           (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTScratchpadReg_Offset               )))
#define UART3_UART_LPDLL           	           (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTLowPowerDivisorLatchLow_Offset     )))
#define UART3_UART_LPDLH           	           (*((volatile UINT32 *)(UART3_DW_APB_UART_BASE + UART3_UARTLowPowerDivisorLatchHigh_Offset    )))
#define UARTUART3_PING_1BIT_WR (UART3_UART_LCR)
#define UART3_CC_UART_APB_DATA_WIDTH        32
#define UART3_CC_UART_MAX_APB_DATA_WIDTH    32
#define UART3_CC_UART_FIFO_MODE             16
#define UART3_CC_UART_MEM_SELECT            1
#define UART3_CC_UART_MEM_MODE              0
#define UART3_CC_UART_CLOCK_MODE            2
#define UART3_CC_UART_AFCE_MODE             0x1
#define UART3_CC_UART_THRE_MODE             0x1
#define UART3_CC_UART_SIR_MODE              0x1
#define UART3_CC_UART_CLK_GATE_EN           0
#define UART3_CC_UART_FIFO_ACCESS           0x1
#define UART3_CC_UART_DMA_EXTRA             0x1
#define UART3_CC_UART_DMA_POL               0
#define UART3_CC_UART_SIR_LP_MODE           0x0
#define UART3_CC_UART_DEBUG                 0
#define UART3_CC_UART_BAUD_CLK              1
#define UART3_CC_UART_ADDITIONAL_FEATURES   0x0
#define UART3_CC_UART_FIFO_STAT             0x0
#define UART3_CC_UART_SHADOW                0x0
#define UART3_CC_UART_ADD_ENCODED_PARAMS    0x0
#define UART3_CC_UART_LATCH_MODE            0
#define UART3_CC_UART_ADDR_SLICE_LHS        8
#define UART3_CC_UART_COMP_VERSION          0x3331342a

#endif
