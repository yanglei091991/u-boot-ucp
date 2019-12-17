ENTRY(bootcode)

RAM_DATA_BASE = 0x020c0000;
SECTIONS
{
  . = 0x00000000;

  . = ALIGN(4);
  /* Code starts with vectors, then bootcode, then other code */
  .text :
  {
    *bootcode.o(boot)
    *vectors.o(vectors)
    *(.text*) /* remainder of code */
  } 

  .rodata : 
  {
   __rodata_start = .;
  . = ALIGN(4);
    *(.rodata*)
  . = ALIGN(4);
   __rodata_end = .;
  } 
  
  .eh_frame : 
  {
   __eh_frame_start = .;
  . = ALIGN(4);
    *(.eh_frame*)
  . = ALIGN(4);
   __eh_frame_end = .;
  }

  .ARM.exidx : 
  {
   __exidx_start = .;
  . = ALIGN(4);
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  . = ALIGN(4);
   __exidx_end = .;
  } 

  /* Data */
  .data RAM_DATA_BASE :AT(ADDR(.ARM.exidx) + SIZEOF(.ARM.exidx))
  { 
   __data_start = .;
  . = ALIGN(4);
    *(.data*)
    *(.init_array*) 
    *(.fini_array*)
    *(.got*)
  . = ALIGN(4);
   __data_end = .;
  } 

  /* Notes section
   * This is not used so we discard it. Although not used it needs to be
   * explicitly mentioned in the linker script as some toolchains will place
   * the notes section at adderss 0 if it is not explicitly mentioned. */
  /DISCARD/ : { *(.note*) }

  /* Uninitialized data */
  .bss RAM_DATA_BASE + SIZEOF(.data) : AT(LOADADDR(.data) + SIZEOF(.data)) 
  {
  __bss_start__ = .;
  . = ALIGN(4);
    *(.bss)  
    *(COMMON)
  __bss_end__   = .;
  . = ALIGN(4);
  } 
data_load_start = LOADADDR(.data);
data_size = SIZEOF(.data);
  . = ALIGN(4);
  __end__   = .;
}

