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


//----------------------------------------------------------------------------
// Handler strings
//----------------------------------------------------------------------------

// The default handlers print an error message and terminate the simulation
// by writing the EOT character to the tube.  The error strings are defined
// here.
undef_exception_str:      .asciz "undefined instruction\n"
svc_exception_str:        .asciz "SVC\n"
pf_abort_exception_str:   .asciz "prefetch abort\n"
data_abort_exception_str: .asciz "data abort\n"
irq_exception_str:        .asciz "IRQ\n"
fiq_exception_str:        .asciz "FIQ\n"

// Ensure 4-byte alignment for following code
.balign 4


//------------------------------------------------------------------------------
// Default handlers
//
//   The default handlers all contain one branch to a weakly-imported exception
//   handler label followed by default handler code.  This allows tests to
//   define their own handlers, with fall-back default handlers if they do not.
//
//   When a test defines a replacement handler, it must end with an excpetion
//   return instruction so that the default handler code is never executed.
//
//   When a test does not define a replacement handler, the branch to the
//   weakly-imported symbol in the default handler is effectively a NOP and
//   the default handler code is therefore executed.
//
//   The default handlers all print an "Unexpected exception" error message
//   and terminate the simulation by writing the EOT character to the tube.
//------------------------------------------------------------------------------

def_undef_handler:      b       undef_handler
                        ldr     r0, =undef_exception_str
                        b       unexpected_handler

def_svc_handler:        b       svc_handler
                        ldr     r0, =svc_exception_str
                        b       unexpected_handler

def_pf_abort_handler:   b       pf_abort_handler
                        ldr     r0, =pf_abort_exception_str
                        b       unexpected_handler

def_data_abort_handler: b       data_abort_handler
                        ldr     r0, =data_abort_exception_str
                        b       unexpected_handler

def_irq_handler:        b       irq_handler
                        ldr     r0, =irq_exception_str
                        b       unexpected_handler

def_fiq_handler:        b       fiq_handler
                        ldr     r0, =fiq_exception_str
                        b       unexpected_handler

// Generic unexpected handler routine.  This prints an error message and
// terminates the simulation by writing the EOT character to the tube.
// Expects r0 to contain a pointer to a string that is the name of the
// exception.  As this is a terminal routine, no registers are preserved.
unexpected_handler:
                ldr     r1, =#0x13000000        // Tube address
                ldr     r2, =unexpected_str     // Message
                bl      print
                mov     r2, r0
                bl      print
                ldr     r2, =fail_str
                bl      print

                // Write EOT character to terminate the simulation
                mov     r2, #0x4
                strb    r2, [r1]
                b       .

                // Print a string to the tube
                //   Expects: r1 -> tube
                //            r2 -> message
                //   Modifies r3
print:          ldrb    r3, [r2], #1
                cmp     r3, #0
                strbne  r3, [r1]
                bne     print
                bx      lr

                .balign 4
unexpected_str: .asciz "Unexpected exception: "
fail_str:       .asciz "** TEST FAILED **\n"

                .end

