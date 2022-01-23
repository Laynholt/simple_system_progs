.PHONY: all clean

all: cli.out ser.out clean

cli.o: cli.c
	cc -c cli.c

ser.o: ser.c
	cc -c ser.c

cli.out: cli.o
	cc -o cli.out cli.o

ser.out: ser.o
	cc -o ser.out ser.o

clean:
	rm cli.o ser.o
