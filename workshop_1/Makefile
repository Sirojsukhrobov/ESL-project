CC = gcc
CFLAGS = -Wall

all: main

main: main.o vector.o
	$(CC) $(CFLAGS) -o main main.o vector.o

main.o: main.c vector.h
	$(CC) $(CFLAGS) -c main.c

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c

clean:
	rm -f *.o main
