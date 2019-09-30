SRCS = $(wildcard ext4*.c)
c_objs = $(filter %.o,$(patsubst %.c,%.o,$(SRCS)))
CFLAGS += -g -Wall -I../include -Os

lwext4.a: $(c_objs) malloc.o
	ar r lwext4.a $(c_objs) malloc.o

main: main.o file_dev.o lwext4.a
	$(CC) $(CFLAGS) -o main main.o file_dev.o lwext4.a

clean:
	bash -c "rm -f lwext4.a main *.o *.gcov *.gcda *.gcno"

.PHONY: clean
