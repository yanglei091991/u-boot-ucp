// Stack definitions.  Each CPU gets a chunk of the global stack space.
.equ CPU_STACK_SIZE, 0x1000 // 4k
.equ STACK_SIZE,     CPU_STACK_SIZE // 4k
.equ HEAP_SIZE,      0x1000 // 4k
.equ CLUSTER_STACK_SIZE,  0x4000 // 16K
.equ EXCEPTION_STACK_SIZE, 0x0400
.equ BOOT1_STACK_TOP, 0x020cff00
.equ CPU1_RESET_ADDR, 0x03670060
.equ CPU1_SYS_CTRL, 0x03690058
