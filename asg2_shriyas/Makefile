CC = gcc

INCLUDE = -I.

CFLAGS = -g

LDFLAGS = -L. -L/usr/lib

LDLIBS = -lc -lm

.c.o:
	$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $<

OBJECTS = \
pgm.o \
filters.o 

all: main

main: main.o filters.o pgm.o
	gcc main.o filters.o pgm.o -o main

main.o: main.c
	gcc -c main.c

filters.o: filters.c
	gcc -c filters.c
	
pgm.o: pgm.c
	gcc -c pgm.c

clean:
	rm -f *.o
	rm -rf main
