//******************** (C) COPYRIGHT 2019 SmartLogic*******************************
// FileName           : dw_apb_spi.h
// Author             : lijian, jian.li@smartlogictech.com
// Date First Issued  : 2019-03-29 04:00:13 PM
// Last Modified      : 2019-03-29 04:08:17 PM
// Description        :
// ------------------------------------------------------------
// Modification History:
// Version    Date       Author    Modification Description
//
//**********************************************************************************
#ifndef __SPI_H__
#define __SPI_H__

#define SPI0_DW_APB_SSI_BASE 0x020f8000
#define SPI1_DW_APB_SSI_BASE 0x02100000
#define SPI2_DW_APB_SSI_BASE 0x04a00000
#define SPI3_DW_APB_SSI_BASE 0x04a10000

#define SPI0_SSI_Ctrlr0_Offset      0x00
#define SPI0_SSI_Ctrlr1_Offset      0x04
#define SPI0_SSI_SSIenr_Offset      0x08
#define SPI0_SSI_Mwcr_Offset        0x0C
#define SPI0_SSI_Ser_Offset         0x10
#define SPI0_SSI_Baudr_Offset       0x14
#define SPI0_SSI_Txftlr_Offset      0x18
#define SPI0_SSI_Rxftlr_Offset      0x1C
#define SPI0_SSI_Txflr_Offset       0x20
#define SPI0_SSI_Rxflr_Offset       0x24
#define SPI0_SSI_Sr_Offset          0x28
#define SPI0_SSI_Imr_Offset         0x2C
#define SPI0_SSI_Isr_Offset         0x30
#define SPI0_SSI_Risr_Offset        0x34
#define SPI0_SSI_Txoicr_Offset      0x38
#define SPI0_SSI_Rxoicr_Offset      0x3C
#define SPI0_SSI_Rxuicr_Offset      0x40
#define SPI0_SSI_Msticr_Offset      0x44
#define SPI0_SSI_Icr_Offset         0x48
#define SPI0_SSI_Dmacr_Offset       0x4C
#define SPI0_SSI_Dmatdlr_Offset     0x50
#define SPI0_SSI_Dmardlr_Offset     0x54
#define SPI0_SSI_Idr_Offset         0x58
#define SPI0_SSI_Version_Id_Offset  0x5C
#define SPI0_SSI_Dr_Low_Offset      0x60
#define SPI0_SSI_Dr_High_Offset     0x9C
#define SPI0_EXT_REG_ADDR_Offset    0xfc
#define SPI0_SSI_Ctrlr0            (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Ctrlr0_Offset    )))
#define SPI0_SSI_Ctrlr1            (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Ctrlr1_Offset    )))
#define SPI0_SSI_SSIenr            (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_SSIenr_Offset    )))
#define SPI0_SSI_Mwcr              (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Mwcr_Offset      )))
#define SPI0_SSI_Ser               (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Ser_Offset       )))
#define SPI0_SSI_Baudr             (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Baudr_Offset     )))
#define SPI0_SSI_Txftlr            (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Txftlr_Offset    )))
#define SPI0_SSI_Rxftlr            (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Rxftlr_Offset    )))
#define SPI0_SSI_Txflr             (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Txflr_Offset     )))
#define SPI0_SSI_Rxflr             (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Rxflr_Offset     )))
#define SPI0_SSI_Sr                (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Sr_Offset        )))
#define SPI0_SSI_Imr               (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Imr_Offset       )))
#define SPI0_SSI_Isr               (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Isr_Offset       )))
#define SPI0_SSI_Risr              (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Risr_Offset      )))
#define SPI0_SSI_Txoicr            (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Txoicr_Offset    )))
#define SPI0_SSI_Rxoicr            (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Rxoicr_Offset    )))
#define SPI0_SSI_Rxuicr            (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Rxuicr_Offset    )))
#define SPI0_SSI_Msticr            (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Msticr_Offset    )))
#define SPI0_SSI_Icr               (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Icr_Offset       )))
#define SPI0_SSI_Dmacr             (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Dmacr_Offset     )))
#define SPI0_SSI_Dmatdlr           (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Dmatdlr_Offset   )))
#define SPI0_SSI_Dmardlr           (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Dmardlr_Offset   )))
#define SPI0_SSI_Idr               (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Idr_Offset       )))
#define SPI0_SSI_Version_Id        (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Version_Id_Offset)))
#define SPI0_SSI_Dr_Low            (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Dr_Low_Offset    )))
#define SPI0_SSI_Dr_High           (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_SSI_Dr_High_Offset   )))
#define SPI0_EXT_REG               (*((volatile UINT32 *)(SPI0_DW_APB_SSI_BASE + SPI0_EXT_REG_ADDR_Offset  )))

#define SPI1_SSI_Ctrlr0_Offset      0x00
#define SPI1_SSI_Ctrlr1_Offset      0x04
#define SPI1_SSI_SSIenr_Offset      0x08
#define SPI1_SSI_Mwcr_Offset        0x0C
#define SPI1_SSI_Ser_Offset         0x10
#define SPI1_SSI_Baudr_Offset       0x14
#define SPI1_SSI_Txftlr_Offset      0x18
#define SPI1_SSI_Rxftlr_Offset      0x1C
#define SPI1_SSI_Txflr_Offset       0x20
#define SPI1_SSI_Rxflr_Offset       0x24
#define SPI1_SSI_Sr_Offset          0x28
#define SPI1_SSI_Imr_Offset         0x2C
#define SPI1_SSI_Isr_Offset         0x30
#define SPI1_SSI_Risr_Offset        0x34
#define SPI1_SSI_Txoicr_Offset      0x38
#define SPI1_SSI_Rxoicr_Offset      0x3C
#define SPI1_SSI_Rxuicr_Offset      0x40
#define SPI1_SSI_Msticr_Offset      0x44
#define SPI1_SSI_Icr_Offset         0x48
#define SPI1_SSI_Dmacr_Offset       0x4C
#define SPI1_SSI_Dmatdlr_Offset     0x50
#define SPI1_SSI_Dmardlr_Offset     0x54
#define SPI1_SSI_Idr_Offset         0x58
#define SPI1_SSI_Version_Id_Offset  0x5C
#define SPI1_SSI_Dr_Low_Offset      0x60
#define SPI1_SSI_Dr_High_Offset     0x9C
#define SPI1_EXT_REG_ADDR_Offset    0xfc
#define SPI1_SSI_Ctrlr0            (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Ctrlr0_Offset    )))
#define SPI1_SSI_Ctrlr1            (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Ctrlr1_Offset    )))
#define SPI1_SSI_SSIenr            (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_SSIenr_Offset    )))
#define SPI1_SSI_Mwcr              (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Mwcr_Offset      )))
#define SPI1_SSI_Ser               (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Ser_Offset       )))
#define SPI1_SSI_Baudr             (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Baudr_Offset     )))
#define SPI1_SSI_Txftlr            (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Txftlr_Offset    )))
#define SPI1_SSI_Rxftlr            (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Rxftlr_Offset    )))
#define SPI1_SSI_Txflr             (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Txflr_Offset     )))
#define SPI1_SSI_Rxflr             (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Rxflr_Offset     )))
#define SPI1_SSI_Sr                (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Sr_Offset        )))
#define SPI1_SSI_Imr               (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Imr_Offset       )))
#define SPI1_SSI_Isr               (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Isr_Offset       )))
#define SPI1_SSI_Risr              (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Risr_Offset      )))
#define SPI1_SSI_Txoicr            (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Txoicr_Offset    )))
#define SPI1_SSI_Rxoicr            (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Rxoicr_Offset    )))
#define SPI1_SSI_Rxuicr            (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Rxuicr_Offset    )))
#define SPI1_SSI_Msticr            (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Msticr_Offset    )))
#define SPI1_SSI_Icr               (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Icr_Offset       )))
#define SPI1_SSI_Dmacr             (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Dmacr_Offset     )))
#define SPI1_SSI_Dmatdlr           (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Dmatdlr_Offset   )))
#define SPI1_SSI_Dmardlr           (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Dmardlr_Offset   )))
#define SPI1_SSI_Idr               (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Idr_Offset       )))
#define SPI1_SSI_Version_Id        (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Version_Id_Offset)))
#define SPI1_SSI_Dr_Low            (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Dr_Low_Offset    )))
#define SPI1_SSI_Dr_High           (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_SSI_Dr_High_Offset   )))
#define SPI1_EXT_REG               (*((volatile UINT32 *)(SPI1_DW_APB_SSI_BASE + SPI1_EXT_REG_ADDR_Offset  )))

#define SPI2_SSI_Ctrlr0_Offset      0x00
#define SPI2_SSI_Ctrlr1_Offset      0x04
#define SPI2_SSI_SSIenr_Offset      0x08
#define SPI2_SSI_Mwcr_Offset        0x0C
#define SPI2_SSI_Ser_Offset         0x10
#define SPI2_SSI_Baudr_Offset       0x14
#define SPI2_SSI_Txftlr_Offset      0x18
#define SPI2_SSI_Rxftlr_Offset      0x1C
#define SPI2_SSI_Txflr_Offset       0x20
#define SPI2_SSI_Rxflr_Offset       0x24
#define SPI2_SSI_Sr_Offset          0x28
#define SPI2_SSI_Imr_Offset         0x2C
#define SPI2_SSI_Isr_Offset         0x30
#define SPI2_SSI_Risr_Offset        0x34
#define SPI2_SSI_Txoicr_Offset      0x38
#define SPI2_SSI_Rxoicr_Offset      0x3C
#define SPI2_SSI_Rxuicr_Offset      0x40
#define SPI2_SSI_Msticr_Offset      0x44
#define SPI2_SSI_Icr_Offset         0x48
#define SPI2_SSI_Dmacr_Offset       0x4C
#define SPI2_SSI_Dmatdlr_Offset     0x50
#define SPI2_SSI_Dmardlr_Offset     0x54
#define SPI2_SSI_Idr_Offset         0x58
#define SPI2_SSI_Version_Id_Offset  0x5C
#define SPI2_SSI_Dr_Low_Offset      0x60
#define SPI2_SSI_Dr_High_Offset     0x9C
#define SPI2_EXT_REG_ADDR_Offset    0xfc
#define SPI2_SSI_Ctrlr0            (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Ctrlr0_Offset    )))
#define SPI2_SSI_Ctrlr1            (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Ctrlr1_Offset    )))
#define SPI2_SSI_SSIenr            (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_SSIenr_Offset    )))
#define SPI2_SSI_Mwcr              (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Mwcr_Offset      )))
#define SPI2_SSI_Ser               (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Ser_Offset       )))
#define SPI2_SSI_Baudr             (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Baudr_Offset     )))
#define SPI2_SSI_Txftlr            (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Txftlr_Offset    )))
#define SPI2_SSI_Rxftlr            (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Rxftlr_Offset    )))
#define SPI2_SSI_Txflr             (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Txflr_Offset     )))
#define SPI2_SSI_Rxflr             (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Rxflr_Offset     )))
#define SPI2_SSI_Sr                (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Sr_Offset        )))
#define SPI2_SSI_Imr               (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Imr_Offset       )))
#define SPI2_SSI_Isr               (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Isr_Offset       )))
#define SPI2_SSI_Risr              (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Risr_Offset      )))
#define SPI2_SSI_Txoicr            (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Txoicr_Offset    )))
#define SPI2_SSI_Rxoicr            (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Rxoicr_Offset    )))
#define SPI2_SSI_Rxuicr            (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Rxuicr_Offset    )))
#define SPI2_SSI_Msticr            (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Msticr_Offset    )))
#define SPI2_SSI_Icr               (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Icr_Offset       )))
#define SPI2_SSI_Dmacr             (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Dmacr_Offset     )))
#define SPI2_SSI_Dmatdlr           (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Dmatdlr_Offset   )))
#define SPI2_SSI_Dmardlr           (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Dmardlr_Offset   )))
#define SPI2_SSI_Idr               (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Idr_Offset       )))
#define SPI2_SSI_Version_Id        (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Version_Id_Offset)))
#define SPI2_SSI_Dr_Low            (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Dr_Low_Offset    )))
#define SPI2_SSI_Dr_High           (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_SSI_Dr_High_Offset   )))
#define SPI2_EXT_REG               (*((volatile UINT32 *)(SPI2_DW_APB_SSI_BASE + SPI2_EXT_REG_ADDR_Offset  )))

#define SPI3_SSI_Ctrlr0_Offset      0x00
#define SPI3_SSI_Ctrlr1_Offset      0x04
#define SPI3_SSI_SSIenr_Offset      0x08
#define SPI3_SSI_Mwcr_Offset        0x0C
#define SPI3_SSI_Ser_Offset         0x10
#define SPI3_SSI_Baudr_Offset       0x14
#define SPI3_SSI_Txftlr_Offset      0x18
#define SPI3_SSI_Rxftlr_Offset      0x1C
#define SPI3_SSI_Txflr_Offset       0x20
#define SPI3_SSI_Rxflr_Offset       0x24
#define SPI3_SSI_Sr_Offset          0x28
#define SPI3_SSI_Imr_Offset         0x2C
#define SPI3_SSI_Isr_Offset         0x30
#define SPI3_SSI_Risr_Offset        0x34
#define SPI3_SSI_Txoicr_Offset      0x38
#define SPI3_SSI_Rxoicr_Offset      0x3C
#define SPI3_SSI_Rxuicr_Offset      0x40
#define SPI3_SSI_Msticr_Offset      0x44
#define SPI3_SSI_Icr_Offset         0x48
#define SPI3_SSI_Dmacr_Offset       0x4C
#define SPI3_SSI_Dmatdlr_Offset     0x50
#define SPI3_SSI_Dmardlr_Offset     0x54
#define SPI3_SSI_Idr_Offset         0x58
#define SPI3_SSI_Version_Id_Offset  0x5C
#define SPI3_SSI_Dr_Low_Offset      0x60
#define SPI3_SSI_Dr_High_Offset     0x9C
#define SPI3_EXT_REG_ADDR_Offset    0xfc
#define SPI3_SSI_Ctrlr0            (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Ctrlr0_Offset    )))
#define SPI3_SSI_Ctrlr1            (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Ctrlr1_Offset    )))
#define SPI3_SSI_SSIenr            (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_SSIenr_Offset    )))
#define SPI3_SSI_Mwcr              (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Mwcr_Offset      )))
#define SPI3_SSI_Ser               (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Ser_Offset       )))
#define SPI3_SSI_Baudr             (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Baudr_Offset     )))
#define SPI3_SSI_Txftlr            (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Txftlr_Offset    )))
#define SPI3_SSI_Rxftlr            (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Rxftlr_Offset    )))
#define SPI3_SSI_Txflr             (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Txflr_Offset     )))
#define SPI3_SSI_Rxflr             (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Rxflr_Offset     )))
#define SPI3_SSI_Sr                (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Sr_Offset        )))
#define SPI3_SSI_Imr               (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Imr_Offset       )))
#define SPI3_SSI_Isr               (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Isr_Offset       )))
#define SPI3_SSI_Risr              (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Risr_Offset      )))
#define SPI3_SSI_Txoicr            (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Txoicr_Offset    )))
#define SPI3_SSI_Rxoicr            (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Rxoicr_Offset    )))
#define SPI3_SSI_Rxuicr            (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Rxuicr_Offset    )))
#define SPI3_SSI_Msticr            (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Msticr_Offset    )))
#define SPI3_SSI_Icr               (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Icr_Offset       )))
#define SPI3_SSI_Dmacr             (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Dmacr_Offset     )))
#define SPI3_SSI_Dmatdlr           (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Dmatdlr_Offset   )))
#define SPI3_SSI_Dmardlr           (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Dmardlr_Offset   )))
#define SPI3_SSI_Idr               (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Idr_Offset       )))
#define SPI3_SSI_Version_Id        (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Version_Id_Offset)))
#define SPI3_SSI_Dr_Low            (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Dr_Low_Offset    )))
#define SPI3_SSI_Dr_High           (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_SSI_Dr_High_Offset   )))
#define SPI3_EXT_REG               (*((volatile UINT32 *)(SPI3_DW_APB_SSI_BASE + SPI3_EXT_REG_ADDR_Offset  )))





#endif
