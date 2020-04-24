CC=gcc
BINARY=gol
LIBS=-lncurses

all:
	$(CC) -o $(BINARY) game_of_life.c $(LIBS)
