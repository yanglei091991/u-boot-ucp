SRCS = $(wildcard ext4*.c)
c_objs = $(filter %.o,$(patsubst %.c,%.o,$(SRCS)))
CFLAGS += -g -Wall -I../include -Os
CFLAGS += -DCONFIG_USE_DEFAULT_CFG=1

lwext4.a: $(c_objs)
	ar r lwext4.a $(c_objs)

main: main.o file_dev.o lwext4.a
	$(CC) $(CFLAGS) -o main main.o file_dev.o lwext4.a

clean:
	rm $(c_objs) lwext4.a

.PHONY: clean
