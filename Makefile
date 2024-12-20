CC=g++
CFLAGS=-Wall -ansi -std=c++20
LFLAGS=-lSDL2
DFLAGS=-g
PROGS=prog
OBJS=vec.o obj.o help.o test.o

all: $(OBJS) $(PROGS)

prog: src/main.cpp $(OBJS)
	$(CC) $(CFLAGS) $(DFLAGS) $< -o $@ $(OBJS) $(LFLAGS)

vec.o: src/Util/Vec.cpp src/Util/Vec.h
	$(CC) $(CFLAGS) -c $(DFLAGS) $< -o $@

obj.o: src/Objects/Object.cpp src/Objects/Object.h
	$(CC) $(CFLAGS) -c $(DFLAGS) $< -o $@

help.o: src/Util/Helpers.cpp src/Util/Helpers.h
	$(CC) $(CFLAGS) -c $(DFLAGS) $< -o $@

test.o: src/Objects/test.cpp src/Objects/test.h
	$(CC) $(CFLAGS) -c $(DFLAGS) $< -o $@


clean:
	rm -f $(PROGS) *.o ~*

clean_mac:
	rm -rf $(PROGS) *.o ~* *.dSYM
