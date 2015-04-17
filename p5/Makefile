

CC=gcc
CFLAGS=-Wall -O
#CFLAGS=-Wall -g
LFLAGS=

all: seq-random thread-random

seq-random: seq-random.o timing.o
	$(CC) $(CFLAGS) -o $@ seq-random.o timing.o   $(LFLAGS)

thread-random: thread-random.c
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	/bin/rm -f *.o core a.out seq-random
	/bin/rm -f *.o core a.out thread-random
