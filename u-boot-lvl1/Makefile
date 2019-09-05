CC      = arm-eabi-gcc
AS      = arm-eabi-as
LD      = arm-eabi-gcc
AR      = arm-eabi-ar
OBJCOPY = arm-eabi-objcopy
OBJDUMP = arm-eabi-objdump

CFLAGS 		:= -g -march=armv8-a -mtune=cortex-a53  -DGCC -falign-functions=16 -fno-common -falign-jumps=8 -falign-loops=8 -fomit-frame-pointer -funroll-loops -fPIE
ASFLAGS   := -march=armv8-a
LDFLAGS   := 

SRCS = $(wildcard *.s *.c)
c_objs = $(filter %.o,$(patsubst %.c,%.o,$(SRCS)))
s_objs = $(filter %.o,$(patsubst %.s,%.o,$(SRCS)))

boot.bin: $(c_objs) $(s_objs)
	${LD} -Wl,-pie,-T boot.ld $^ -o boot.elf
	${OBJCOPY} -O binary -S boot.elf $@
	${OBJDUMP} -D -m arm boot.elf > boot.dis
	./gen_ihex.sh
	
%.o:%.c
	${CC} $(CFLAGS) -c -o $@ $<

%.o:%.s
	${AS} $(ASFLAGS) -o $@ $<

clean:
	rm -f *.o *.bin *.elf *.dis *.ihex
	
