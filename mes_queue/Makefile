.PHONY: all clean

all: cli.out ser.out clean

msg_q.o: msg_q.c msg_q.h
	cc -c msg_q.c

cli.o: cli.c
	cc -c cli.c

ser.o: ser.c
	cc -c ser.c

cli.out: cli.o msg_q.o
	cc -o cli.out cli.o msg_q.o

ser.out: ser.o msg_q.o
	cc -o ser.out ser.o msg_q.o

clean:
	rm cli.o ser.o msg_q.o
