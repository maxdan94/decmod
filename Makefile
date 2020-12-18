CC=gcc
CFLAGS=-O9

all: dm ReadFromFile main

dm : dm.c
	$(CC) $(CFLAGS) -c -o dm.p dm.c

ReadFromFile : ReadFromFile.c
	$(CC) $(CFLAGS) -c -o ReadFromFile.p ReadFromFile.c

main : ReadFromFile.o dm.o
	$(CC) $(CFLAGS) -o dm ReadFromFile.o dm.o

clean:
	rm *.o dm
