SRCS = $(wildcard ext4*.c)
c_objs = $(filter %.o,$(patsubst %.c,%.o,$(SRCS)))
CFLAGS += -g -Wall -I../include -D CONFIG_USE_DEFAULT_CFG=1 -Os

lwext4.a: $(c_objs)
	ar r lwext4.a $(c_objs)

clean:
	rm $(c_objs) lwext4.a

.PHONY: clean
