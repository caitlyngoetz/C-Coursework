
INSTALL=..
INCLUDE=$(INSTALL)/include -I.
LIBS=$(INSTALL)/lib
LFLAGS=-L$(LIBS) -lmylib
CC=gcc
CFLAGS=-Wall -g  -I$(INCLUDE)





PROGS=wf WordObj

all: $(PROGS)


wf: wf.o
	$(CC) $(CFLAGS) -o $@ $^  $(LFLAGS)
WordObj: WordObj.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	rm --force list *.o $(PROGS)


