//-----------------------------------------------------------------------------
// The confidential and proprietary information contained in this file may
// only be used by a person authorised under and to the extent permitted
// by a subsisting licensing agreement from ARM Limited.
//
//            (C) COPYRIGHT 2013-2014 ARM Limited.
//                ALL RIGHTS RESERVED
//
// This entire notice must be reproduced on all copies of this file
// and copies of this file may only be made by a person if such person is
// permitted to do so under the terms of a subsisting license agreement
// from ARM Limited.
//
//      SVN Information
//
//      Checked In          : $Date: 2014-07-02 16:52:21 +0100 (Wed, 02 Jul 2014) $
//
//      Revision            : $Revision: 283836 $
//
//      Release Information : CORTEXA53-r0p4-00rel1
//
//-----------------------------------------------------------------------------

// Enable UAL syntax
.syntax unified

        .section vectors, "ax", %progbits
        
        // Weakly import replacement handlers.  This allows a test to redefine
        // handlers.  If it doesn't, the default ones below will be used.
        .weak  undef_handler
        .weak  svc_handler
        .weak  pf_abort_handler
        .weak  data_abort_handler
        .weak  irq_handler
        .weak  fiq_handler

//------------------------------------------------------------------------------
// Vector table
//------------------------------------------------------------------------------
.global vector_table
vector_table:
        ldr     pc, reset_handler_addr          // Reset
        ldr     pc, undef_handler_addr          // Undef
        ldr     pc, svc_handler_addr            // SVC
        ldr     pc, pf_abort_handler_addr       // Prefetch abort
        ldr     pc, data_abort_handler_addr     // Data abort
        nop                                     // Not used
        ldr     pc, irq_handler_addr            // IRQ
        ldr     pc, fiq_handler_addr            // FIQ


//------------------------------------------------------------------------------
// Handler addresses
//------------------------------------------------------------------------------

reset_handler_addr:      .word     bootcode
undef_handler_addr:      .word     def_undef_handler
svc_handler_addr:        .word     def_svc_handler
pf_abort_handler_addr:   .word     def_pf_abort_handler
data_abort_handler_addr: .word     def_data_abort_handler
irq_handler_addr:        .word     def_irq_handler
fiq_handler_addr:        .word     def_fiq_handler

.balign	4
def_undef_handler:
def_svc_handler:
def_pf_abort_handler:
def_data_abort_handler:
def_irq_handler:
def_fiq_handler:
1:
	b	1b			/* hang and never return */

                .end

