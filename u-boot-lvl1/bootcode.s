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

                //A53 to enable SMPEN 
                mrrc  p15,1,r0,r1,c15
                orr r0,r0,#0x40
                mcrr p15,1,r0,r1,c15
                
                // Only CPU0 starts  CPU1 sleep , cpu0 will wakeup cpu1 
                // cpu1 alive and enter into suspend state, wait sys_ctrl reg point
                mrc     p15, 0, r0, c0, c0, 5   // Read MPIDR
                ands    r0, r0, #0xFF           // r0 == CPU number
                cmp     r0, #1                  // cpu1 run
                beq     cpu1_jump

                // CRG reg init, wakeup cpu1
                ldr     r0, =DEV_ENA_REG2_ADDR 
                ldr     r1, [r0]
                mov     r2, #0xe07      // cpu1 wakeup reg config
                orr     r1, r1, r2
                str     r1, [r0]
                ldr     r0, =0xFFFFFFFF
                ldr     r1, =DEV_ENA_REG1_ADDR // 0x0367005c
                str     r0, [r1]
               
                 // cpu1 wakeup start
//                ldr r1, =DEV_ENA_REG2_ADDR // 0x03670060
//                ldr r1, [r1]
//                mov r2, #2
//                orr r1, r1, r2
//                ldr r3, =DEV_ENA_REG2_ADDR
//                str r1, [r3]
                // cpu1 wakeup end
                b     cpu_start


/**********************************************/
// cpu1 wfe
wfe_lable:
                wfe
                wfe
cpu1_jump:
                ldr r1, =CPU1_SYS_CTRL
                ldr r0, [r1]
                cmp r0, #0
                beq  wfe_lable
                bx r0 

/*********************************************/
cpu_start:
                // clear share mem 0-5
                mov r2, #0
                ldr r0, =SM5_START_ADDR // 128KB
				ldr r1, =SM5_END_ADDR
                bl copy_loop
                ldr r0, =SM4_START_ADDR // 64KB
				ldr r1, =SM4_END_ADDR
                bl copy_loop
                ldr r0, =SM03_START_ADDR // 1M
				ldr r1, =SM03_END_ADDR
                bl copy_loop
                // call c  main
                bl _arm_start
start_boot2:
                ldr r0, =BOOT2_START_ADDR /*boot2 entry point*/
                mov lr, r0
                mov pc, lr          /* jump to boot2 */
 
copy_loop:
				mov r3, r2
				str r3, [r0], #4
				cmp r0, r1
				bne copy_loop
                bx lr

				.end
				
