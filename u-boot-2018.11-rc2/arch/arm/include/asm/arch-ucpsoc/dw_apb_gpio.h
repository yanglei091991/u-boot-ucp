//******************** (C) COPYRIGHT 2019 SmartLogic*******************************
// FileName           : dw_apb_gpio.h
// Author             : lijian, jian.li@smartlogictech.com
// Date First Issued  : 2019-03-29 03:39:50 PM
// Last Modified      : 2019-03-29 03:43:29 PM
// Description        :
// ------------------------------------------------------------
// Modification History:
// Version    Date       Author    Modification Description
//
//**********************************************************************************
#ifndef __GPIO_H__
#define __GPIO_H__


#define DW_APB_GPIO0_BASE 0x02118000
#define DW_APB_GPIO1_BASE 0x04a40000
#define GPIO_SWPORTA_DR_OFFSET    0x00
#define GPIO_SWPORTA_DDR_OFFSET   0x04
#define GPIO_SWPORTA_CTL_OFFSET   0x08
#define GPIO_SWPORTB_DR_OFFSET    0x0C
#define GPIO_SWPORTB_DDR_OFFSET   0x10
#define GPIO_SWPORTB_CTL_OFFSET   0x14
#define GPIO_SWPORTC_DR_OFFSET    0x18
#define GPIO_SWPORTC_DDR_OFFSET   0x1C
#define GPIO_SWPORTC_CTL_OFFSET   0x20
#define GPIO_SWPORTD_DR_OFFSET    0x24
#define GPIO_SWPORTD_DDR_OFFSET   0x28
#define GPIO_SWPORTD_CTL_OFFSET   0x2C
#define GPIO_INTEN_OFFSET         0x30
#define GPIO_INTMASK_OFFSET       0x34
#define GPIO_INTTYPE_LEVEL_OFFSET 0x38
#define GPIO_INT_POLARITY_OFFSET  0x3C
#define GPIO_INTSTATUS_OFFSET     0x40
#define GPIO_RAW_INTSTATUS_OFFSET 0x44
#define GPIO_DEBOUNCE_OFFSET      0x48
#define GPIO_PORTA_EOI_OFFSET     0x4C
#define GPIO_EXT_PORTA_OFFSET     0x50
#define GPIO_EXT_PORTB_OFFSET     0x54
#define GPIO_EXT_PORTC_OFFSET     0x58
#define GPIO_EXT_PORTD_OFFSET     0x5C
#define GPIO_LS_SYNC_OFFSET       0x60
#define GPIO_ID_CODE_OFFSET       0x64
#define GPIO_VER_ID_CODE_OFFSET   0x6C
#define GPIO_CONFIGID_REG2_OFFSET 0x70
#define GPIO_CONFIGID_REG1_OFFSET 0x74

#define GPIO0_SWPORTA_DR       (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_SWPORTA_DR_OFFSET)))
#define GPIO0_SWPORTA_DDR      (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_SWPORTA_DDR_OFFSET)))
#define GPIO0_SWPORTA_CTL      (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_SWPORTA_CTL_OFFSET)))
#define GPIO0_SWPORTB_DR       (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_SWPORTB_DR_OFFSET)))
#define GPIO0_SWPORTB_DDR      (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_SWPORTB_DDR_OFFSET)))
#define GPIO0_SWPORTB_CTL      (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_SWPORTB_CTL_OFFSET)))
#define GPIO0_SWPORTC_DR       (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_SWPORTC_DR_OFFSET)))
#define GPIO0_SWPORTC_DDR      (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_SWPORTC_DDR_OFFSET)))
#define GPIO0_SWPORTC_CTL      (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_SWPORTC_CTL_OFFSET)))
#define GPIO0_SWPORTD_DR       (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_SWPORTD_DR_OFFSET)))
#define GPIO0_SWPORTD_DDR      (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_SWPORTD_DDR_OFFSET)))
#define GPIO0_SWPORTD_CTL      (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_SWPORTD_CTL_OFFSET)))
#define GPIO0_INTEN            (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_INTEN_OFFSET)))
#define GPIO0_INTMASK          (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_INTMASK_OFFSET)))
#define GPIO0_INTTYPE_LEVEL    (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_INTTYPE_LEVEL_OFFSET)))
#define GPIO0_INT_POLARITY     (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_INT_POLARITY_OFFSET)))
#define GPIO0_INTSTATUS        (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_INTSTATUS_OFFSET)))
#define GPIO0_RAW_INTSTATUS    (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_RAW_INTSTATUS_OFFSET)))
#define GPIO0_DEBOUNCE         (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_DEBOUNCE_OFFSET)))
#define GPIO0_PORTA_EOI        (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_PORTA_EOI_OFFSET)))
#define GPIO0_EXT_PORTA        (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_EXT_PORTA_OFFSET)))
#define GPIO0_EXT_PORTB        (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_EXT_PORTB_OFFSET)))
#define GPIO0_EXT_PORTC        (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_EXT_PORTC_OFFSET)))
#define GPIO0_EXT_PORTD        (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_EXT_PORTD_OFFSET)))
#define GPIO0_LS_SYNC          (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_LS_SYNC_OFFSET)))
#define GPIO0_ID_CODE          (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_ID_CODE_OFFSET)))
#define GPIO0_VER_ID_CODE      (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_VER_ID_CODE_OFFSET)))
#define GPIO0_CONFIGID_REG2    (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_CONFIGID_REG2_OFFSET)))
#define GPIO0_CONFIGID_REG1    (*((volatile UINT32 *)(DW_APB_GPIO0_BASE  + GPIO_CONFIGID_REG1_OFFSET)))
#define GPIO0PING_1BIT_WR      (GPIO0_SWPORTA_DR)
#define GPIO1_SWPORTA_DR       (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_SWPORTA_DR_OFFSET)))
#define GPIO1_SWPORTA_DDR      (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_SWPORTA_DDR_OFFSET)))
#define GPIO1_SWPORTA_CTL      (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_SWPORTA_CTL_OFFSET)))
#define GPIO1_SWPORTB_DR       (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_SWPORTB_DR_OFFSET)))
#define GPIO1_SWPORTB_DDR      (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_SWPORTB_DDR_OFFSET)))
#define GPIO1_SWPORTB_CTL      (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_SWPORTB_CTL_OFFSET)))
#define GPIO1_SWPORTC_DR       (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_SWPORTC_DR_OFFSET)))
#define GPIO1_SWPORTC_DDR      (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_SWPORTC_DDR_OFFSET)))
#define GPIO1_SWPORTC_CTL      (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_SWPORTC_CTL_OFFSET)))
#define GPIO1_SWPORTD_DR       (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_SWPORTD_DR_OFFSET)))
#define GPIO1_SWPORTD_DDR      (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_SWPORTD_DDR_OFFSET)))
#define GPIO1_SWPORTD_CTL      (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_SWPORTD_CTL_OFFSET)))
#define GPIO1_INTEN            (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_INTEN_OFFSET)))
#define GPIO1_INTMASK          (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_INTMASK_OFFSET)))
#define GPIO1_INTTYPE_LEVEL    (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_INTTYPE_LEVEL_OFFSET)))
#define GPIO1_INT_POLARITY     (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_INT_POLARITY_OFFSET)))
#define GPIO1_INTSTATUS        (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_INTSTATUS_OFFSET)))
#define GPIO1_RAW_INTSTATUS    (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_RAW_INTSTATUS_OFFSET)))
#define GPIO1_DEBOUNCE         (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_DEBOUNCE_OFFSET)))
#define GPIO1_PORTA_EOI        (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_PORTA_EOI_OFFSET)))
#define GPIO1_EXT_PORTA        (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_EXT_PORTA_OFFSET)))
#define GPIO1_EXT_PORTB        (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_EXT_PORTB_OFFSET)))
#define GPIO1_EXT_PORTC        (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_EXT_PORTC_OFFSET)))
#define GPIO1_EXT_PORTD        (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_EXT_PORTD_OFFSET)))
#define GPIO1_LS_SYNC          (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_LS_SYNC_OFFSET)))
#define GPIO1_ID_CODE          (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_ID_CODE_OFFSET)))
#define GPIO1_VER_ID_CODE      (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_VER_ID_CODE_OFFSET)))
#define GPIO1_CONFIGID_REG2    (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_CONFIGID_REG2_OFFSET)))
#define GPIO1_CONFIGID_REG1    (*((volatile UINT32 *)(DW_APB_GPIO1_BASE  + GPIO_CONFIGID_REG1_OFFSET)))
#define GPIO1PING_1BIT_WR      (GPIO1_SWPORTA_DR)


#define CC_GPIO_ADD_ENCODED_PARAM            0x1
#define CC_GPIO_APB_DATA_WIDTH               32
#define CC_GPIO_NUM_PORTS                    4
#define CC_GPIO_ID                           0
#define CC_GPIO_DEBOUNCE                     0
#define CC_GPIO_ID_WIDTH                     32
#define CC_GPIO_ID_NUM                       0x0
#define CC_GPIO_REV_ID                       0
#define CC_GPIO_REV_ID_WIDTH                 32
#define CC_GPIO_REV_ID_NUM                   0x0
#define CC_GPIO_PWIDTH_A                     8
#define CC_GPIO_PORTA_SINGLE_CTL             1
#define CC_GPIO_SWPORTA_RESET                0x0
#define CC_GPIO_HW_PORTA                     1
#define CC_GPIO_DFLT_DIR_A                   0
#define CC_GPIO_DFLT_SRC_A                   0
#define CC_GPIO_PORTA_INTR                   1
#define CC_GPIO_INT_POL                      0
#define CC_GPIO_INTR_IO                      0
#define CC_GPIO_PA_SYNC_EXT_DATA             1
#define CC_GPIO_PA_SYNC_INTERRUPTS           1
#define CC_GPIO_PWIDTH_B                     32
#define CC_GPIO_PORTB_SINGLE_CTL             1
#define CC_GPIO_SWPORTB_RESET                0x0
#define CC_GPIO_HW_PORTB                     0
#define CC_GPIO_DFLT_DIR_B                   0
#define CC_GPIO_DFLT_SRC_B                   0
#define CC_GPIO_PB_SYNC_EXT_DATA             1
#define CC_GPIO_PWIDTH_C                     32
#define CC_GPIO_PORTC_SINGLE_CTL             1
#define CC_GPIO_SWPORTC_RESET                0x0
#define CC_GPIO_HW_PORTC                     0
#define CC_GPIO_DFLT_DIR_C                   1
#define CC_GPIO_DFLT_SRC_C                   0
#define CC_GPIO_PC_SYNC_EXT_DATA             0
#define CC_GPIO_PWIDTH_D                     8
#define CC_GPIO_PORTD_SINGLE_CTL             1
#define CC_GPIO_SWPORTD_RESET                0x0
#define CC_GPIO_HW_PORTD                     1
#define CC_GPIO_DFLT_DIR_D                   1
#define CC_GPIO_DFLT_SRC_D                   1
#define CC_GPIO_PD_SYNC_EXT_DATA             1


#endif
