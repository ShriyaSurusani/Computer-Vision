CC = gcc

INCLUDE = -I.

CFLAGS = -g

LDFLAGS = -L. -L/usr/lib

LDLIBS = -lc -lm

.c.o:
	$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $<

OBJECTS = \
pgm.o \
wavelets.o 

all: main

main: main.o wavelets.o pgm.o
	gcc main.o wavelets.o pgm.o -o main

main.o: main.c
	gcc -c main.c

filters.o: wavelets.c
	gcc -c wavelets.c
	
pgm.o: pgm.c
	gcc -c pgm.c

clean:
	rm -f *.o
	rm -rf main
