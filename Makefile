CC=g++
CFLAGS=-Wall -ansi -std=c++20
LFLAGS=-lSDL2
DFLAGS=-g
PROGS=prog
OBJS=vec.o

all: $(OBJS) $(PROGS)

prog: src/main.cpp $(OBJS)
	$(CC) $(CFLAGS) $(DFLAGS) $< -o $@ $(OBJS) $(LFLAGS)

vec.o: src/Util/Vec.cpp src/Util/Vec.h
	$(CC) $(CFLAGS) -c $(DFLAGS) $< -o $@

clean:
	rm -f $(PROGS) *.o ~*

clean_mac:
	rm -rf $(PROGS) *.o ~* *.dSYM
