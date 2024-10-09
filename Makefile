CC=gcc
CFLAGS=-Wall -ansi
LFLAGS=-lSDL2
DFLAGS=-g
PROGS=prog
OBJS=

all: $(OBJS) $(PROGS)

prog: main.c $(OBJS)
	$(CC) $(CFLAGS) $(DFLAGS) $< -o $@ $(OBJS) $(LFLAGS)

clean:
	rm -f $(PROGS) *.o ~*

clean_mac:
	rm -rf $(PROGS) *.o ~* *.dSYM