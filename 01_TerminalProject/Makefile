SRC=Show.c
EXE=Show
CC=cc
LIBS=-lncurses
CFLAGS=-Wall

%:	%.c
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

all:	Show

clean:
	rm -f o oo $(EXE) *.o
