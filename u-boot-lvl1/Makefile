CC      = arm-none-eabi-gcc
AS      = arm-none-eabi-as
LD      = arm-none-eabi-gcc
AR      = arm-none-eabi-ar
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump

CFLAGS 		:= -g -march=armv8-a -mtune=cortex-a53  -DGCC -falign-functions=16 -fno-common -falign-jumps=8 -falign-loops=8 -fomit-frame-pointer -funroll-loops -Os
ASFLAGS   := -g -march=armv8-a
LDFLAGS   := 

SRCS = $(wildcard *.s *.c)
c_objs = $(filter %.o,$(patsubst %.c,%.o,$(SRCS)))
s_objs = $(filter %.o,$(patsubst %.s,%.o,$(SRCS)))

boot.bin: $(c_objs) $(s_objs) lwext4/boot_mmc_ext4.a
	${LD} -Wl,-T boot.ld $^ -o boot.elf
	${OBJCOPY} -O binary -S boot.elf $@
	${OBJDUMP} -D -m arm boot.elf > boot.dis
	./gen_ihex.sh
	
%.o:%.c
	${CC} $(CFLAGS) -c -o $@ $<

%.o:%.s
	${AS} $(ASFLAGS) -o $@ $<

lwext4/boot_mmc_ext4.a: lwext4
	make -C lwext4 boot_mmc_ext4.a

clean:
	rm -f *.o *.bin *.elf *.dis *.ihex
	make -C lwext4 clean
