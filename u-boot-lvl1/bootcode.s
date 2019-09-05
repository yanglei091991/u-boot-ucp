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

                // Initialize the stack pointer
                ldr     r13, =stack_top
                add     r13, r13, #4
                mrc     p15, 0, r0, c0, c0, 5   // MPIDR
                and     r0, r0, #0xff           // r0 == CPU number
                mov     r2, #CPU_STACK_SIZE
                mul     r1, r0, r2
                sub     r13, r13, r1

                // Enable interrupts
                cpsie   if

                .ifdef IK_MODE
                // All CPUs start the test code. The select_cpu function in the integration kit
                // will determine which CPU run 
                b       cpu_start
                .else
                // Only CPU0 starts the test code.  Other CPUs sleep and will be enabled
                // in individual tests where required.
                mrc     p15, 0, r0, c0, c0, 5   // Read MPIDR
                ands    r0, r0, #0xFF           // r0 == CPU number
                beq     cpu_start
                .endif

                // If the CPU is not CPU0 then enter WFI
wfi_loop:       wfi
                b       wfi_loop


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
cpu_start:
				// boot_level_1 code relocation
				ldr r0, =0x020c0000 
				ldr r1, =bootcode 
				ldr r2, _bss_start_ofs

copy_loop:
				ldr r3, [r1], #4
				str r3, [r0], #4
				cmp r1, r2
				bne copy_loop

				/*
				 * fix .rel.dyn relocations
				 */
relocate:
				ldr r6, =0x020c0000     /*boot1 relocate addr*/
				ldr	r0, _TEXT_BASE		/* r0 <- Text base */
				sub	r9, r6, r0		/* r9 <- relocation offset */
				ldr	r10, _dynsym_start_ofs	/* r10 <- sym table ofs */
				add	r10, r10, r0		/* r10 <- sym table in FLASH */
				ldr	r2, _rel_dyn_start_ofs	/* r2 <- rel dyn start ofs */
				add	r2, r2, r0		/* r2 <- rel dyn start in FLASH */
				ldr	r3, _rel_dyn_end_ofs	/* r3 <- rel dyn end ofs */
				add	r3, r3, r0		/* r3 <- rel dyn end in FLASH */
fixloop:
				ldr	r0, [r2]		/* r0 <- location to fix up, IN FLASH! */
				add	r0, r0, r9		/* r0 <- location to fix up in RAM */
				ldr	r1, [r2, #4]
				and	r7, r1, #0xff
				cmp	r7, #23			/* relative fixup? */
				beq	fixrel
				cmp	r7, #2			/* absolute fixup? */
				beq	fixabs
				/* ignore unknown type of fixup */
				b	fixnext
fixabs:
				/* absolute fix: set location to (offset) symbol value */
				mov	r1, r1, LSR #4		/* r1 <- symbol index in .dynsym */
				add	r1, r10, r1		/* r1 <- address of symbol in table */
				ldr	r1, [r1, #4]		/* r1 <- symbol value */
				add	r1, r1, r9		/* r1 <- relocated sym addr */
				b	fixnext
fixrel:
				/* relative fix: increase location by offset */
				ldr	r1, [r0]
				add	r1, r1, r9
fixnext:
				str	r1, [r0]
				add	r2, r2, #8		/* each rel.dyn entry is 8 bytes */
				cmp	r2, r3
				blo	fixloop

run_on_ram:
				ldr	r0, _arm_start_ofs
				adr	r1, bootcode
                add	r0, r0, r9
                blx r0
//				add	lr, r0, r1
//				add	lr, lr, r9
				/* jump to _arm_start */
//				mov	pc, lr
start_boot2:
                ldr r0, =0x4ee0000 /*boot2 entry point*/
                mov lr, r0
                mov pc, lr          /* jump to boot2 */


.global _TEXT_BASE
_TEXT_BASE:
				.word bootcode	
.global	_arm_start_ofs	
_arm_start_ofs:
				.word _arm_start - bootcode
.global _rel_dyn_start_ofs
_rel_dyn_start_ofs:
				.word __rel_dyn_start - bootcode
.global _rel_dyn_end_ofs
_rel_dyn_end_ofs:
				.word __rel_dyn_end - bootcode
.global _dynsym_start_ofs
_dynsym_start_ofs:
				.word __dynsym_start - bootcode
.global _bss_start_ofs
_bss_start_ofs:
				.word __bss_start__ - bootcode


				.end
				
