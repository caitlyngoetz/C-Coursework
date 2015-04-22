

CC=gcc
CFLAGS=-Wall -O
#CFLAGS=-Wall -g
LFLAGS=-lpthread

all: seq-random thread-random

seq-random: seq-random.o timing.o
	$(CC) $(CFLAGS) -o $@ seq-random.o timing.o   $(LFLAGS)

thread-random: thread-random.o timing.o
	$(CC) $(CFLAGS) -o $@ thread-random.o timing.o   $(LFLAGS)
	
clean:
	/bin/rm -f *.o core a.out seq-random thread-random
