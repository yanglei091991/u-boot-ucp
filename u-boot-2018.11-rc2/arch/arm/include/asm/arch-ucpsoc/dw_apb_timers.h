//******************** (C) COPYRIGHT 2019 SmartLogic*******************************
// FileName           : dw_apb_timers.h
// Author             : lijian, jian.li@smartlogictech.com
// Date First Issued  : 2019-03-29 02:23:07 PM
// Last Modified      : 2019-04-10 10:32:18 AM
// Description        :
// ------------------------------------------------------------
// Modification History:
// Version    Date       Author    Modification Description
//
//**********************************************************************************
#ifndef __TIMER_H__
#define __TIMER_H__

#define DW_APB_TIMERS0_BASE          0x031d0000
#define DW_APB_TIMERS1_BASE          0x04a20000
#define DW_APB_TIMERS2_BASE          0x04a30000
#define TIMERLOADCOUNTOFF            0x00
#define TIMERCURRENTVALOFF           0x04
#define TIMERCONTROLREGOFF           0x08
#define TIMEREOIOFF                  0x0c
#define TIMERINTSTATOFF              0x10
#define TIMERSINTSTATOFF             0xa0
#define TIMERSEOIOFF                 0xa4
#define TIMERSRAWINTSTATOFF          0xa8
#define TIMERVERSIONIDOFF            0xac

#define TIMER0_TIMER1BASE            (DW_APB_TIMERS0_BASE + TIMERLOADCOUNTOFF)
#define TIMER0_TIMER2BASE            (DW_APB_TIMERS0_BASE + 0x14)
#define TIMER0_TIMER3BASE            (DW_APB_TIMERS0_BASE + 0x28)
#define TIMER0_TIMER4BASE            (DW_APB_TIMERS0_BASE + 0x3c)
#define TIMER0_TIMER5BASE            (DW_APB_TIMERS0_BASE + 0x50)
#define TIMER0_TIMER6BASE            (DW_APB_TIMERS0_BASE + 0x64)
#define TIMER0_TIMER7BASE            (DW_APB_TIMERS0_BASE + 0x78)
#define TIMER0_TIMER8BASE            (DW_APB_TIMERS0_BASE + 0x8c)
#define TIMER1_TIMER1BASE            (DW_APB_TIMERS1_BASE + TIMERLOADCOUNTOFF)
#define TIMER1_TIMER2BASE            (DW_APB_TIMERS1_BASE + 0x14)
#define TIMER1_TIMER3BASE            (DW_APB_TIMERS1_BASE + 0x28)
#define TIMER1_TIMER4BASE            (DW_APB_TIMERS1_BASE + 0x3c)
#define TIMER1_TIMER5BASE            (DW_APB_TIMERS1_BASE + 0x50)
#define TIMER1_TIMER6BASE            (DW_APB_TIMERS1_BASE + 0x64)
#define TIMER1_TIMER7BASE            (DW_APB_TIMERS1_BASE + 0x78)
#define TIMER1_TIMER8BASE            (DW_APB_TIMERS1_BASE + 0x8c)
#define TIMER2_TIMER1BASE            (DW_APB_TIMERS2_BASE + TIMERLOADCOUNTOFF)
#define TIMER2_TIMER2BASE            (DW_APB_TIMERS2_BASE + 0x14)
#define TIMER2_TIMER3BASE            (DW_APB_TIMERS2_BASE + 0x28)
#define TIMER2_TIMER4BASE            (DW_APB_TIMERS2_BASE + 0x3c)
#define TIMER2_TIMER5BASE            (DW_APB_TIMERS2_BASE + 0x50)
#define TIMER2_TIMER6BASE            (DW_APB_TIMERS2_BASE + 0x64)
#define TIMER2_TIMER7BASE            (DW_APB_TIMERS2_BASE + 0x78)
#define TIMER2_TIMER8BASE            (DW_APB_TIMERS2_BASE + 0x8c)

#define TIMER0_TIMER1LOADCOUNT       (*((volatile UINT32 *)(TIMER0_TIMER1BASE + TIMERLOADCOUNTOFF)))
#define TIMER0_TIMER1CURRENTVAL      (*((volatile UINT32 *)(TIMER0_TIMER1BASE + TIMERCURRENTVALOFF)))
#define TIMER0_TIMER1CONTROLREG      (*((volatile UINT32 *)(TIMER0_TIMER1BASE + TIMERCONTROLREGOFF)))
#define TIMER0_TIMER1EOI             (*((volatile UINT32 *)(TIMER0_TIMER1BASE + TIMEREOIOFF)))
#define TIMER0_TIMER1INTSTAT         (*((volatile UINT32 *)(TIMER0_TIMER1BASE + TIMERINTSTATOFF)))
#define TIMER0_TIMER2LOADCOUNT       (*((volatile UINT32 *)(TIMER0_TIMER2BASE + TIMERLOADCOUNTOFF)))
#define TIMER0_TIMER2CURRENTVAL      (*((volatile UINT32 *)(TIMER0_TIMER2BASE + TIMERCURRENTVALOFF)))
#define TIMER0_TIMER2CONTROLREG      (*((volatile UINT32 *)(TIMER0_TIMER2BASE + TIMERCONTROLREGOFF)))
#define TIMER0_TIMER2EOI             (*((volatile UINT32 *)(TIMER0_TIMER2BASE + TIMEREOIOFF)))
#define TIMER0_TIMER2INTSTAT         (*((volatile UINT32 *)(TIMER0_TIMER2BASE + TIMERINTSTATOFF)))
#define TIMER0_TIMER3LOADCOUNT       (*((volatile UINT32 *)(TIMER0_TIMER3BASE + TIMERLOADCOUNTOFF)))
#define TIMER0_TIMER3CURRENTVAL      (*((volatile UINT32 *)(TIMER0_TIMER3BASE + TIMERCURRENTVALOFF)))
#define TIMER0_TIMER3CONTROLREG      (*((volatile UINT32 *)(TIMER0_TIMER3BASE + TIMERCONTROLREGOFF)))
#define TIMER0_TIMER3EOI             (*((volatile UINT32 *)(TIMER0_TIMER3BASE + TIMEREOIOFF)))
#define TIMER0_TIMER3INTSTAT         (*((volatile UINT32 *)(TIMER0_TIMER3BASE + TIMERINTSTATOFF)))
#define TIMER0_TIMER4LOADCOUNT       (*((volatile UINT32 *)(TIMER0_TIMER4BASE + TIMERLOADCOUNTOFF)))
#define TIMER0_TIMER4CURRENTVAL      (*((volatile UINT32 *)(TIMER0_TIMER4BASE + TIMERCURRENTVALOFF)))
#define TIMER0_TIMER4CONTROLREG      (*((volatile UINT32 *)(TIMER0_TIMER4BASE + TIMERCONTROLREGOFF)))
#define TIMER0_TIMER4EOI             (*((volatile UINT32 *)(TIMER0_TIMER4BASE + TIMEREOIOFF)))
#define TIMER0_TIMER4INTSTAT         (*((volatile UINT32 *)(TIMER0_TIMER4BASE + TIMERINTSTATOFF)))
#define TIMER0_TIMER5LOADCOUNT       (*((volatile UINT32 *)(TIMER0_TIMER5BASE + TIMERLOADCOUNTOFF)))
#define TIMER0_TIMER5CURRENTVAL      (*((volatile UINT32 *)(TIMER0_TIMER5BASE + TIMERCURRENTVALOFF)))
#define TIMER0_TIMER5CONTROLREG      (*((volatile UINT32 *)(TIMER0_TIMER5BASE + TIMERCONTROLREGOFF)))
#define TIMER0_TIMER5EOI             (*((volatile UINT32 *)(TIMER0_TIMER5BASE + TIMEREOIOFF)))
#define TIMER0_TIMER5INTSTAT         (*((volatile UINT32 *)(TIMER0_TIMER5BASE + TIMERINTSTATOFF)))
#define TIMER0_TIMER6LOADCOUNT       (*((volatile UINT32 *)(TIMER0_TIMER6BASE + TIMERLOADCOUNTOFF)))
#define TIMER0_TIMER6CURRENTVAL      (*((volatile UINT32 *)(TIMER0_TIMER6BASE + TIMERCURRENTVALOFF)))
#define TIMER0_TIMER6CONTROLREG      (*((volatile UINT32 *)(TIMER0_TIMER6BASE + TIMERCONTROLREGOFF)))
#define TIMER0_TIMER6EOI             (*((volatile UINT32 *)(TIMER0_TIMER6BASE + TIMEREOIOFF)))
#define TIMER0_TIMER6INTSTAT         (*((volatile UINT32 *)(TIMER0_TIMER6BASE + TIMERINTSTATOFF)))
#define TIMER0_TIMER7LOADCOUNT       (*((volatile UINT32 *)(TIMER0_TIMER7BASE + TIMERLOADCOUNTOFF)))
#define TIMER0_TIMER7CURRENTVAL      (*((volatile UINT32 *)(TIMER0_TIMER7BASE + TIMERCURRENTVALOFF)))
#define TIMER0_TIMER7CONTROLREG      (*((volatile UINT32 *)(TIMER0_TIMER7BASE + TIMERCONTROLREGOFF)))
#define TIMER0_TIMER7EOI             (*((volatile UINT32 *)(TIMER0_TIMER7BASE + TIMEREOIOFF)))
#define TIMER0_TIMER7INTSTAT         (*((volatile UINT32 *)(TIMER0_TIMER7BASE + TIMERINTSTATOFF)))
#define TIMER0_TIMER8LOADCOUNT       (*((volatile UINT32 *)(TIMER0_TIMER8BASE + TIMERLOADCOUNTOFF)))
#define TIMER0_TIMER8CURRENTVAL      (*((volatile UINT32 *)(TIMER0_TIMER8BASE + TIMERCURRENTVALOFF)))
#define TIMER0_TIMER8CONTROLREG      (*((volatile UINT32 *)(TIMER0_TIMER8BASE + TIMERCONTROLREGOFF)))
#define TIMER0_TIMER8EOI             (*((volatile UINT32 *)(TIMER0_TIMER8BASE + TIMEREOIOFF)))
#define TIMER0_TIMER8INTSTAT         (*((volatile UINT32 *)(TIMER0_TIMER8BASE + TIMERINTSTATOFF)))
#define TIMER0_TIMERSEOI             (*((volatile UINT32 *)(DW_APB_TIMERS0_BASE + TIMERSEOIOFF)))
#define TIMER0_TIMERSINTSTAT         (*((volatile UINT32 *)(DW_APB_TIMERS0_BASE + TIMERSINTSTATOFF)))
#define TIMER0_TIMERSRAWINTSTAT      (*((volatile UINT32 *)(DW_APB_TIMERS0_BASE + TIMERSRAWINTSTATOFF)))
#define TIMER0_TIMERPING_1BIT_WR     (TIMER0_TIMER1LOADCOUNT)

#define TIMER1_TIMER1LOADCOUNT       (*((volatile UINT32 *)(TIMER1_TIMER1BASE + TIMERLOADCOUNTOFF)))
#define TIMER1_TIMER1CURRENTVAL      (*((volatile UINT32 *)(TIMER1_TIMER1BASE + TIMERCURRENTVALOFF)))
#define TIMER1_TIMER1CONTROLREG      (*((volatile UINT32 *)(TIMER1_TIMER1BASE + TIMERCONTROLREGOFF)))
#define TIMER1_TIMER1EOI             (*((volatile UINT32 *)(TIMER1_TIMER1BASE + TIMEREOIOFF)))
#define TIMER1_TIMER1INTSTAT         (*((volatile UINT32 *)(TIMER1_TIMER1BASE + TIMERINTSTATOFF)))
#define TIMER1_TIMER2LOADCOUNT       (*((volatile UINT32 *)(TIMER1_TIMER2BASE + TIMERLOADCOUNTOFF)))
#define TIMER1_TIMER2CURRENTVAL      (*((volatile UINT32 *)(TIMER1_TIMER2BASE + TIMERCURRENTVALOFF)))
#define TIMER1_TIMER2CONTROLREG      (*((volatile UINT32 *)(TIMER1_TIMER2BASE + TIMERCONTROLREGOFF)))
#define TIMER1_TIMER2EOI             (*((volatile UINT32 *)(TIMER1_TIMER2BASE + TIMEREOIOFF)))
#define TIMER1_TIMER2INTSTAT         (*((volatile UINT32 *)(TIMER1_TIMER2BASE + TIMERINTSTATOFF)))
#define TIMER1_TIMER3LOADCOUNT       (*((volatile UINT32 *)(TIMER1_TIMER3BASE + TIMERLOADCOUNTOFF)))
#define TIMER1_TIMER3CURRENTVAL      (*((volatile UINT32 *)(TIMER1_TIMER3BASE + TIMERCURRENTVALOFF)))
#define TIMER1_TIMER3CONTROLREG      (*((volatile UINT32 *)(TIMER1_TIMER3BASE + TIMERCONTROLREGOFF)))
#define TIMER1_TIMER3EOI             (*((volatile UINT32 *)(TIMER1_TIMER3BASE + TIMEREOIOFF)))
#define TIMER1_TIMER3INTSTAT         (*((volatile UINT32 *)(TIMER1_TIMER3BASE + TIMERINTSTATOFF)))
#define TIMER1_TIMER4LOADCOUNT       (*((volatile UINT32 *)(TIMER1_TIMER4BASE + TIMERLOADCOUNTOFF)))
#define TIMER1_TIMER4CURRENTVAL      (*((volatile UINT32 *)(TIMER1_TIMER4BASE + TIMERCURRENTVALOFF)))
#define TIMER1_TIMER4CONTROLREG      (*((volatile UINT32 *)(TIMER1_TIMER4BASE + TIMERCONTROLREGOFF)))
#define TIMER1_TIMER4EOI             (*((volatile UINT32 *)(TIMER1_TIMER4BASE + TIMEREOIOFF)))
#define TIMER1_TIMER4INTSTAT         (*((volatile UINT32 *)(TIMER1_TIMER4BASE + TIMERINTSTATOFF)))
#define TIMER1_TIMER5LOADCOUNT       (*((volatile UINT32 *)(TIMER1_TIMER5BASE + TIMERLOADCOUNTOFF)))
#define TIMER1_TIMER5CURRENTVAL      (*((volatile UINT32 *)(TIMER1_TIMER5BASE + TIMERCURRENTVALOFF)))
#define TIMER1_TIMER5CONTROLREG      (*((volatile UINT32 *)(TIMER1_TIMER5BASE + TIMERCONTROLREGOFF)))
#define TIMER1_TIMER5EOI             (*((volatile UINT32 *)(TIMER1_TIMER5BASE + TIMEREOIOFF)))
#define TIMER1_TIMER5INTSTAT         (*((volatile UINT32 *)(TIMER1_TIMER5BASE + TIMERINTSTATOFF)))
#define TIMER1_TIMER6LOADCOUNT       (*((volatile UINT32 *)(TIMER1_TIMER6BASE + TIMERLOADCOUNTOFF)))
#define TIMER1_TIMER6CURRENTVAL      (*((volatile UINT32 *)(TIMER1_TIMER6BASE + TIMERCURRENTVALOFF)))
#define TIMER1_TIMER6CONTROLREG      (*((volatile UINT32 *)(TIMER1_TIMER6BASE + TIMERCONTROLREGOFF)))
#define TIMER1_TIMER6EOI             (*((volatile UINT32 *)(TIMER1_TIMER6BASE + TIMEREOIOFF)))
#define TIMER1_TIMER6INTSTAT         (*((volatile UINT32 *)(TIMER1_TIMER6BASE + TIMERINTSTATOFF)))
#define TIMER1_TIMER7LOADCOUNT       (*((volatile UINT32 *)(TIMER1_TIMER7BASE + TIMERLOADCOUNTOFF)))
#define TIMER1_TIMER7CURRENTVAL      (*((volatile UINT32 *)(TIMER1_TIMER7BASE + TIMERCURRENTVALOFF)))
#define TIMER1_TIMER7CONTROLREG      (*((volatile UINT32 *)(TIMER1_TIMER7BASE + TIMERCONTROLREGOFF)))
#define TIMER1_TIMER7EOI             (*((volatile UINT32 *)(TIMER1_TIMER7BASE + TIMEREOIOFF)))
#define TIMER1_TIMER7INTSTAT         (*((volatile UINT32 *)(TIMER1_TIMER7BASE + TIMERINTSTATOFF)))
#define TIMER1_TIMER8LOADCOUNT       (*((volatile UINT32 *)(TIMER1_TIMER8BASE + TIMERLOADCOUNTOFF)))
#define TIMER1_TIMER8CURRENTVAL      (*((volatile UINT32 *)(TIMER1_TIMER8BASE + TIMERCURRENTVALOFF)))
#define TIMER1_TIMER8CONTROLREG      (*((volatile UINT32 *)(TIMER1_TIMER8BASE + TIMERCONTROLREGOFF)))
#define TIMER1_TIMER8EOI             (*((volatile UINT32 *)(TIMER1_TIMER8BASE + TIMEREOIOFF)))
#define TIMER1_TIMER8INTSTAT         (*((volatile UINT32 *)(TIMER1_TIMER8BASE + TIMERINTSTATOFF)))
#define TIMER1_TIMERSEOI             (*((volatile UINT32 *)(DW_APB_TIMERS1_BASE + TIMERSEOIOFF)))
#define TIMER1_TIMERSINTSTAT         (*((volatile UINT32 *)(DW_APB_TIMERS1_BASE + TIMERSINTSTATOFF)))
#define TIMER1_TIMERSRAWINTSTAT      (*((volatile UINT32 *)(DW_APB_TIMERS1_BASE + TIMERSRAWINTSTATOFF)))
#define TIMER1_TIMERPING_1BIT_WR     (TIMER1_TIMER1LOADCOUNT)

#define TIMER2_TIMER1LOADCOUNT       (*((volatile UINT32 *)(TIMER2_TIMER1BASE + TIMERLOADCOUNTOFF)))
#define TIMER2_TIMER1CURRENTVAL      (*((volatile UINT32 *)(TIMER2_TIMER1BASE + TIMERCURRENTVALOFF)))
#define TIMER2_TIMER1CONTROLREG      (*((volatile UINT32 *)(TIMER2_TIMER1BASE + TIMERCONTROLREGOFF)))
#define TIMER2_TIMER1EOI             (*((volatile UINT32 *)(TIMER2_TIMER1BASE + TIMEREOIOFF)))
#define TIMER2_TIMER1INTSTAT         (*((volatile UINT32 *)(TIMER2_TIMER1BASE + TIMERINTSTATOFF)))
#define TIMER2_TIMER2LOADCOUNT       (*((volatile UINT32 *)(TIMER2_TIMER2BASE + TIMERLOADCOUNTOFF)))
#define TIMER2_TIMER2CURRENTVAL      (*((volatile UINT32 *)(TIMER2_TIMER2BASE + TIMERCURRENTVALOFF)))
#define TIMER2_TIMER2CONTROLREG      (*((volatile UINT32 *)(TIMER2_TIMER2BASE + TIMERCONTROLREGOFF)))
#define TIMER2_TIMER2EOI             (*((volatile UINT32 *)(TIMER2_TIMER2BASE + TIMEREOIOFF)))
#define TIMER2_TIMER2INTSTAT         (*((volatile UINT32 *)(TIMER2_TIMER2BASE + TIMERINTSTATOFF)))
#define TIMER2_TIMER3LOADCOUNT       (*((volatile UINT32 *)(TIMER2_TIMER3BASE + TIMERLOADCOUNTOFF)))
#define TIMER2_TIMER3CURRENTVAL      (*((volatile UINT32 *)(TIMER2_TIMER3BASE + TIMERCURRENTVALOFF)))
#define TIMER2_TIMER3CONTROLREG      (*((volatile UINT32 *)(TIMER2_TIMER3BASE + TIMERCONTROLREGOFF)))
#define TIMER2_TIMER3EOI             (*((volatile UINT32 *)(TIMER2_TIMER3BASE + TIMEREOIOFF)))
#define TIMER2_TIMER3INTSTAT         (*((volatile UINT32 *)(TIMER2_TIMER3BASE + TIMERINTSTATOFF)))
#define TIMER2_TIMER4LOADCOUNT       (*((volatile UINT32 *)(TIMER2_TIMER4BASE + TIMERLOADCOUNTOFF)))
#define TIMER2_TIMER4CURRENTVAL      (*((volatile UINT32 *)(TIMER2_TIMER4BASE + TIMERCURRENTVALOFF)))
#define TIMER2_TIMER4CONTROLREG      (*((volatile UINT32 *)(TIMER2_TIMER4BASE + TIMERCONTROLREGOFF)))
#define TIMER2_TIMER4EOI             (*((volatile UINT32 *)(TIMER2_TIMER4BASE + TIMEREOIOFF)))
#define TIMER2_TIMER4INTSTAT         (*((volatile UINT32 *)(TIMER2_TIMER4BASE + TIMERINTSTATOFF)))
#define TIMER2_TIMER5LOADCOUNT       (*((volatile UINT32 *)(TIMER2_TIMER5BASE + TIMERLOADCOUNTOFF)))
#define TIMER2_TIMER5CURRENTVAL      (*((volatile UINT32 *)(TIMER2_TIMER5BASE + TIMERCURRENTVALOFF)))
#define TIMER2_TIMER5CONTROLREG      (*((volatile UINT32 *)(TIMER2_TIMER5BASE + TIMERCONTROLREGOFF)))
#define TIMER2_TIMER5EOI             (*((volatile UINT32 *)(TIMER2_TIMER5BASE + TIMEREOIOFF)))
#define TIMER2_TIMER5INTSTAT         (*((volatile UINT32 *)(TIMER2_TIMER5BASE + TIMERINTSTATOFF)))
#define TIMER2_TIMER6LOADCOUNT       (*((volatile UINT32 *)(TIMER2_TIMER6BASE + TIMERLOADCOUNTOFF)))
#define TIMER2_TIMER6CURRENTVAL      (*((volatile UINT32 *)(TIMER2_TIMER6BASE + TIMERCURRENTVALOFF)))
#define TIMER2_TIMER6CONTROLREG      (*((volatile UINT32 *)(TIMER2_TIMER6BASE + TIMERCONTROLREGOFF)))
#define TIMER2_TIMER6EOI             (*((volatile UINT32 *)(TIMER2_TIMER6BASE + TIMEREOIOFF)))
#define TIMER2_TIMER6INTSTAT         (*((volatile UINT32 *)(TIMER2_TIMER6BASE + TIMERINTSTATOFF)))
#define TIMER2_TIMER7LOADCOUNT       (*((volatile UINT32 *)(TIMER2_TIMER7BASE + TIMERLOADCOUNTOFF)))
#define TIMER2_TIMER7CURRENTVAL      (*((volatile UINT32 *)(TIMER2_TIMER7BASE + TIMERCURRENTVALOFF)))
#define TIMER2_TIMER7CONTROLREG      (*((volatile UINT32 *)(TIMER2_TIMER7BASE + TIMERCONTROLREGOFF)))
#define TIMER2_TIMER7EOI             (*((volatile UINT32 *)(TIMER2_TIMER7BASE + TIMEREOIOFF)))
#define TIMER2_TIMER7INTSTAT         (*((volatile UINT32 *)(TIMER2_TIMER7BASE + TIMERINTSTATOFF)))
#define TIMER2_TIMER8LOADCOUNT       (*((volatile UINT32 *)(TIMER2_TIMER8BASE + TIMERLOADCOUNTOFF)))
#define TIMER2_TIMER8CURRENTVAL      (*((volatile UINT32 *)(TIMER2_TIMER8BASE + TIMERCURRENTVALOFF)))
#define TIMER2_TIMER8CONTROLREG      (*((volatile UINT32 *)(TIMER2_TIMER8BASE + TIMERCONTROLREGOFF)))
#define TIMER2_TIMER8EOI             (*((volatile UINT32 *)(TIMER2_TIMER8BASE + TIMEREOIOFF)))
#define TIMER2_TIMER8INTSTAT         (*((volatile UINT32 *)(TIMER2_TIMER8BASE + TIMERINTSTATOFF)))
#define TIMER2_TIMERSEOI             (*((volatile UINT32 *)(DW_APB_TIMERS2_BASE + TIMERSEOIOFF)))
#define TIMER2_TIMERSINTSTAT         (*((volatile UINT32 *)(DW_APB_TIMERS2_BASE + TIMERSINTSTATOFF)))
#define TIMER2_TIMERSRAWINTSTAT      (*((volatile UINT32 *)(DW_APB_TIMERS2_BASE + TIMERSRAWINTSTATOFF)))
#define TIMER2_TIMERPING_1BIT_WR     (TIMER2_TIMER1LOADCOUNT)

#endif