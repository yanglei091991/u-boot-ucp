//******************** (C) COPYRIGHT 2019 SmartLogic*******************************
// FileName           : func_lib.h
// Author             : lijian, jian.li@smartlogictech.com
// Date First Issued  : 2019-04-03 08:31:24 AM
// Last Modified      : 2019-05-17 10:16:39 AM
// Description        :
// ------------------------------------------------------------
// Modification History:
// Version    Date       Author    Modification Description
//
//**********************************************************************************

#ifndef __FUNC_LIB_H__
#define __FUNC_LIB_H__

//void print(char * pstr);
void    ucp_ddr_init(void);
void    ERR(void);
void    FINISH(void);
void    SET_CLK_CFG(void);
void    EN_CACHE(void);
void    SET_FLAG (unsigned int a);
void    dwc_ddrc_apb_wr(unsigned int addr , unsigned int data);
void    dwc_ddrphy_apb_wr(unsigned int addr , unsigned int data);
unsigned int  dwc_ddrphy_apb_rd(unsigned int addr);
unsigned int  dwc_ddrc_apb_rd(unsigned int addr);

#endif



