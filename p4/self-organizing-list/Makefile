
INSTALL=..
INCLUDE=$(INSTALL)/include -I.
LIBS=$(INSTALL)/lib
LFLAGS=-L$(LIBS) -lmylib
CC=gcc
CFLAGS=-Wall -g  -I$(INCLUDE)




PROGS=wf  

all: $(PROGS) 

wf: wf.c WordObj.c 
	$(CC) $(CFLAGS) -o $@ $^  $(LFLAGS)

clean:
	rm --force list *.o $(PROGS)


