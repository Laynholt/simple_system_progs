.PHONY: all clean

all: cli.out ser.out clean

shrm.o: shrm.c shrm.h entity.h
	cc -c shrm.c

cli.o: cli.c
	cc -c cli.c

ser.o: ser.c
	cc -c ser.c

cli.out: cli.o shrm.o
	cc -o cli.out cli.o shrm.o

ser.out: ser.o shrm.o
	cc -o ser.out ser.o shrm.o

clean:
	rm ser.o cli.o shrm.o
