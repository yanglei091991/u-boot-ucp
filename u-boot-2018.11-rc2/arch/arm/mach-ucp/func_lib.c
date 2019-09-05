//******************** (C) COPYRIGHT 2019 SmartLogic*******************************
// FileName           : func_lib.c
// Author             : lijian, jian.li@smartlogictech.com
// Date First Issued  : 2019-03-29 08:48:11 AM
// Last Modified      : 2019-05-16 06:21:34 PM
// Description        :
// ------------------------------------------------------------
// Modification History:
// Version    Date       Author    Modification Description
//
//**********************************************************************************
#include <asm/arch/ucp_sfr_c.h>
#include <asm/arch/func_lib.h>
#define __weak __attribute__((weak))
/*void output_char(char c);*/

void ERR (void) {
    SIMULATION_END = 0x1234567F;
    while(1);
}

void FINISH (void) {
    SIMULATION_END = 0x1234567C;
    while(1);
}

void SET_FLAG (unsigned int a ) {
    C2UVM_FLAG = a;
}
void print(char * pstr){
    int i;
    for(i=0;pstr[i]!='\0';i++){
        /*output_char(pstr[i]);*/
    }
    /*output_char('\n');*/

}
void SET_CLK_CFG (void) {
    //pll_postdiv2[15:14];
    //pll_postdiv1[13:12];
    //pll_fbdiv[11:0];
   // PLL0_CONFIG0 = 25 + (0x3<<12) + (0x2<<14);//100MHZ
   // PLL1_CONFIG0 = 25 + (0x3<<12) + (0x2<<14);//100MHZ
   // PLL2_CONFIG0 = 25 + (0x3<<12) + (0x2<<14);//100MHZ
   // PLL3_CONFIG0 = 25 + (0x3<<12) + (0x2<<14);//100MHZ
}
void dwc_ddrc_apb_wr(unsigned int addr , unsigned int data){
  (*((volatile unsigned int *)(0x031e8000 + addr))) = data;


}
unsigned int  dwc_ddrc_apb_rd(unsigned int addr){
    unsigned int temp;
    temp = (*((volatile unsigned int *)(0x031e8000 + addr)));
    return temp;
}
void dwc_ddrphy_apb_wr(unsigned int addr , unsigned int data){
  (*((volatile unsigned int *)(0x031f0000 + addr*4))) = data;


}
unsigned int  dwc_ddrphy_apb_rd(unsigned int addr){
    unsigned int temp;
    temp = (*((volatile unsigned int *)(0x031f0000 + addr*4)));
    return temp;
}
/*
void EN_CACHE(void){
    asm(
                "push    {r0,r1}\n"
                "ldr     r1, =ttb0_base\n"
                "mcr     p15, 0, r1, c2, c0, 0\n"   // TTBR0
                // Set all domains as client"
                "ldr     r1, =0x55555555\n"
                "mcr     p15, 0, r1, c3, c0, 0\n"   // DACR
                // Set SMPEN before enabling caches and MMU
                "mrrc     p15, 1, r0, r1, c15\n"    // CPUECTLR
                "orr      r0, r0, #0x40\n"          // SMPEN bit
                "mcrr     p15, 1, r0, r1, c15\n"
                // Enable caches and MMU
                "mrc     p15, 0, r1, c1, c0, 0\n"   // SCTLR
                "orr     r1, r1, #(0x1 << 2)\n"     // C bit (data cache)
                "orr     r1, r1, #(0x1 << 12)\n"    // I bit (instruction cache)
                "orr     r1, r1, #0x1\n"            // M bit (MMU)
                "mcr     p15, 0, r1, c1, c0, 0\n"
                // Ensure all writes to system registers have taken place
                "dsb\n"
                "isb\n"
                "pop    {r0,r1}\n"
    );

}
*/
__weak void __attribute__ ((interrupt("UNIRQ"))) undef_handler(void){
    ERR();
}
__weak void __attribute__ ((interrupt("SVC"))) svc_handler (void){
    ERR();
}
__weak void __attribute__ ((interrupt("PFABORT"))) pf_abort_handler(void){
    ERR();
}
__weak void __attribute__ ((interrupt("DATAABORT"))) data_abort_handler(void){
    ERR();
}
__weak void __attribute__ ((interrupt("IRQ")))  irq_handler (void){
    ERR();
}
__weak void __attribute__ ((interrupt("FIQ"))) fiq_handler (void){
    ERR();
}

