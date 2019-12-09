CC      = arm-eabi-gcc
AR      = arm-eabi-ar
CFLAGS := -g -march=armv8-a -mtune=cortex-a53  -DGCC -falign-functions=16 -fno-common -falign-jumps=8 -falign-loops=8 -fomit-frame-pointer -funroll-loops

SRCS = $(wildcard ext4*.c)
c_objs = $(filter %.o,$(patsubst %.c,%.o,$(SRCS)))
CFLAGS += -Wall -I../include -Os

boot_mmc_ext4.a: $(c_objs) mmc_dev.o loadfile.o malloc.o
	$(AR) r boot_mmc_ext4.a $^

lwext4.a: $(c_objs) malloc.o
	$(AR) r lwext4.a $^

main: main.o file_dev.o lwext4.a
	$(CC) $(CFLAGS) -o main $^

clean:
	bash -c "rm -f *.a main *.o"

.PHONY: clean
