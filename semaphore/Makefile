.PHONY: all clean

all: sem.out semdes.out clean

sem.o: sem.c
	cc -c sem.c

semdes.o: semdes.c
	cc -c semdes.c

sem.out: sem.o
	cc -o sem.out sem.o

semdes.out: semdes.o
	cc -o semdes.out semdes.o

clean:
	rm sem.o semdes.o
