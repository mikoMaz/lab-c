CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-lssl -lcrypto

all: redo redo-ifchange

redo redo-ifchange: redo.c hash.c
	$(CC) $(CFLAGS) -o $@ redo.c hash.c $(LDFLAGS)

clean:
	rm -f redo redo-ifchange *.o *.redo
