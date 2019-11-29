//-----------------------------------------------------------------------------
// The confidential and proprietary information contained in this file may
// only be used by a person authorised under and to the extent permitted
// by a subsisting licensing agreement from ARM Limited.
//
//            (C) COPYRIGHT 2013-2016 ARM Limited.
//                ALL RIGHTS RESERVED
//
// This entire notice must be reproduced on all copies of this file
// and copies of this file may only be made by a person if such person is
// permitted to do so under the terms of a subsisting license agreement
// from ARM Limited.
//
//      SVN Information
//
//      Checked In          :  $
//
//      Revision            :  $
//
//      Release Information : CORTEXA53-r0p4-00rel1
//
//-------------------------------------------------------------------------------
// Description:
//
//   Set up translation tables for the execution_tb tests.  Short descriptor
//   format sections are used, each defining 1MB of the memory space.
//
//   The 1MB region containing the validation peripherals is marked as
//   strongly ordered.  The rest of the memory space is marked as normal
//   shareable memory.
//-------------------------------------------------------------------------------

//                .section pagetables, "ax", %progbits
//                .align 14       // Align on 16k boundary


//                .end

