CFLAGS=-Wall -Wextra

all: lab0

lab%: lab%.c

lab1.c: lab0.c 01.patch
	patch $< -i 01.patch -o $@

lab2.c: lab1.c 02.patch
	patch $< -i 02.patch -o $@

lab3.c: lab2.c 03.patch
	patch $< -i 03.patch -o $@

run: lab0 lab1 lab2 lab3
	./lab0
	./lab1 10
	./lab2 ' @' 11
	./lab3 666 ' #' 12

clean:
	rm -f lab1.c lab2.c lab3.c lab0 lab1 lab2 lab3
