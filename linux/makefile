CC=gcc
CFLAGS=-pedantic -ansi -std=iso9899:1999 -Wall

hetmani: main.o functions.o count.o
	$(CC) main.o functions.o count.o -o hetmani.out

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

functions.o:
	$(CC) $(CFLAGS) -c functions.c -o functions.o

count.o:
	$(CC) $(CFLAGS) -c count.c -o count.o

clean:
	rm -f *.o

test:
	./hetmani.out -n 7 -r 19 -o plik_test

.PHONY: clean
