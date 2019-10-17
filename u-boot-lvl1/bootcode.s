// Enable UAL syntax
.syntax unified

                .section boot, "ax", %progbits
                .global bootcode
		
// Load stack definitions
.include "boot_defs.hs"

//-------------------------------------------------------------------------------
// Generic boot code
//-------------------------------------------------------------------------------

bootcode:
                // Initialise the register bank
                mov     r0,  #0
                mov     r1,  #0
                mov     r2,  #0
                mov     r3,  #0
                mov     r4,  #0
                mov     r5,  #0
                mov     r6,  #0
                mov     r7,  #0
                mov     r8,  #0
                mov     r9,  #0
                mov     r10, #0
                mov     r11, #0
                mov     r12, #0
                mov     r14, #0

                // -----------------------------------------------------------------------------
                // Variable definitions
                // -----------------------------------------------------------------------------
                
                // Values to set I and F bits in cpsr register
                .equ I_BIT                   , 0x80
                .equ F_BIT                   , 0x40
                // Values for different modes in cpsr register
                .equ MODE_IRQ                , 0x12
                .equ MODE_ABT                , 0x17
                .equ MODE_UND                , 0x1b
                .equ MODE_SYS                , 0x1f


                ldr     r0, = BOOT1_STACK_TOP  // stack_top imported from space allocated in stackheap.S
                mrc     p15, 0, r1, c0, c0, 5
                and     r1, r1, #0xff          // r1 = CPU number
                mov     r2, #(CPU_STACK_SIZE)
                mul     r1, r1, r2             // CPU_STACK_SIZE x cpu number

//               Use Cluster No to calculate stack pointer
                mrc     p15, 0, r2, c0, c0, 5
                and     r2, r2, #0xFF00          // mask bits of cluster number
                asr     r2, r2, #8               // r2 = Cluster number
                mov     r3, #(CLUSTER_STACK_SIZE)// r3 = Total stack needed for cluster
                mul     r2, r3, r2               // Cluster num X cluster stack size

                add     r1, r1, r2               // prev cluster mem + prev cpu mem
                sub     r0, r0, r1               // subtract offset for all clusters and cpus before


//                // Initialize the stack pointer
//                ldr     r13, =stack_top
//                add     r13, r13, #4
//                mrc     p15, 0, r0, c0, c0, 5   // MPIDR
//                and     r0, r0, #0xff           // r0 == CPU number
//                mov     r2, #CPU_STACK_SIZE
//                mul     r1, r0, r2
//                sub     r13, r13, r1


//               Exception stack pointers

//               Enter each mode in turn and initialise stack pointer
//               CPSR_c used to avoid altering condition codes
                msr CPSR_c, #MODE_IRQ|I_BIT|F_BIT
                mov     r13, r0
                sub     r0, r0, #EXCEPTION_STACK_SIZE
                msr CPSR_c, #MODE_ABT|I_BIT|F_BIT
                mov     r13, r0
                sub     r0, r0, #EXCEPTION_STACK_SIZE
                msr CPSR_c, #MODE_UND|I_BIT|F_BIT
                mov     r13, r0
                sub     r0, r0, #EXCEPTION_STACK_SIZE
                msr CPSR_c, #MODE_SYS|I_BIT|F_BIT
                mov     r13, r0

// -----------------------------------------------------------------------------
// Ensure all writes to system registers have taken place
// -----------------------------------------------------------------------------
                dsb sy
                isb sy
                // Enable interrupts
                cpsie   ifa

                .ifdef IK_MODE
                // All CPUs start the test code. The select_cpu function in the integration kit
                // will determine which CPU run 
                b       cpu_start
                .else
                // Only CPU0 starts the test code.  Other CPUs sleep and will be enabled
                // in individual tests where required.
                mrc     p15, 0, r0, c0, c0, 5   // Read MPIDR
                ands    r0, r0, #0xFF           // r0 == CPU number
                cmp     r0, #1                  // cpu1 run
                beq     cpu1_jump
                // cpu1 wakeup start
                ldr r1, =CPU1_RESET_ADDR
                ldr r1, [r1]
                mov r2, #2
                orr r1, r1, r2
                ldr r3, =CPU1_RESET_ADDR
                str r1, [r3]
                // cpu1 wakeup end
                b     cpu_start
                .endif

                // If the CPU is not CPU0 then enter WFI
//wfi_loop:       wfi
//                b       wfi_loop


//-------------------------------------------------------------------------------
// Start the test
//-------------------------------------------------------------------------------
                // If IK_MODE is set, all CPUs can reach this cpu_start label. 
                // If IK_MODE is not set (which is default for execution TB), only 
                // CPU0 reaches this label (the others are in WFI).  The label
                // for the start of the test depends on whether it's a C or an
                // assember test.  Weakly import the labels for each and to
                // determine the correct one.  Note that the linker translates
                // any branches to non-existant weakly-imported labels to NOPs.
                
//                mov r0, #0
//                ldr r1, =#100000
//timer_loop:
//                add r0, r0, #1 
//                cmp r0, r1
//                bne timer_loop
//my_loop:
//                b my_loop

/**********************************************/
wfe_lable:
                wfe
cpu1_jump:
                ldr r1, =CPU1_SYS_CTRL
                ldr r0, [r1]
                cmp r0, #0
                beq  wfe_lable
                bx r0 

/*********************************************/

cpu_start:
				// boot_level_1 code relocation
//				ldr r0, =0x020c0000
//				ldr r1, =bootcode 
//				ldr r2, _bss_start_ofs
//copy_loop:
//				ldr r3, [r1], #4
//				str r3, [r0], #4
//				cmp r1, r2
//				bne copy_loop

				/*
				 * fix .rel.dyn relocations
				 */
//relocate:
//				ldr r6, =0x020c0000     /*boot1 relocate addr*/
//				ldr	r0, _TEXT_BASE		/* r0 <- Text base */
//				sub	r9, r6, r0		/* r9 <- relocation offset */
//				ldr	r10, _dynsym_start_ofs	/* r10 <- sym table ofs */
//				add	r10, r10, r0		/* r10 <- sym table in FLASH */
//				ldr	r2, _rel_dyn_start_ofs	/* r2 <- rel dyn start ofs */
//				add	r2, r2, r0		/* r2 <- rel dyn start in FLASH */
//				ldr	r3, _rel_dyn_end_ofs	/* r3 <- rel dyn end ofs */
//				add	r3, r3, r0		/* r3 <- rel dyn end in FLASH */
//fixloop:
//				ldr	r0, [r2]		/* r0 <- location to fix up, IN FLASH! */
//				add	r0, r0, r9		/* r0 <- location to fix up in RAM */
//				ldr	r1, [r2, #4]
//				and	r7, r1, #0xff
//				cmp	r7, #23			/* relative fixup? */
//				beq	fixrel
//				cmp	r7, #2			/* absolute fixup? */
//				beq	fixabs
//				/* ignore unknown type of fixup */
//				b	fixnext
//fixabs:
//				/* absolute fix: set location to (offset) symbol value */
//				mov	r1, r1, LSR #4		/* r1 <- symbol index in .dynsym */
//				add	r1, r10, r1		/* r1 <- address of symbol in table */
//				ldr	r1, [r1, #4]		/* r1 <- symbol value */
//				add	r1, r1, r9		/* r1 <- relocated sym addr */
//				b	fixnext
//fixrel:
//				/* relative fix: increase location by offset */
//				ldr	r1, [r0]
//				add	r1, r1, r9
//fixnext:
//				str	r1, [r0]
//				add	r2, r2, #8		/* each rel.dyn entry is 8 bytes */
//				cmp	r2, r3
//				blo	fixloop
//
//run_on_ram:
//				ldr	r0, _arm_start_ofs
//				adr	r1, bootcode
//                add	r0, r0, r9
//                blx r0
//				add	lr, r0, r1
//				add	lr, lr, r9
				/* jump to _arm_start */
//				mov	pc, lr
                bl _arm_start
start_boot2:
                ldr r0, =0x04e60000 /*boot2 entry point*/
                mov lr, r0
                mov pc, lr          /* jump to boot2 */


.global _TEXT_BASE
_TEXT_BASE:
				.word bootcode	
.global	_arm_start_ofs	
_arm_start_ofs:
				.word _arm_start - bootcode
//.global _rel_dyn_start_ofs
//_rel_dyn_start_ofs:
//				.word __rel_dyn_start - bootcode
//.global _rel_dyn_end_ofs
//_rel_dyn_end_ofs:
//				.word __rel_dyn_end - bootcode
//.global _dynsym_start_ofs
//_dynsym_start_ofs:
//				.word __dynsym_start - bootcode
//.global _bss_start_ofs
//_bss_start_ofs:
//				.word __bss_start__ - bootcode

				.end
				
