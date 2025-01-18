.PHONY:	clean test
TRASH = *.o
TESTS = *.txt
GENS = prog prog-a prog-so liboutput_static.a liboutput.so
CFLAGS = -Wall -fPIC

ARGS-test1 = ``
ARGS-test2 = 123
ARGS-test3 = qwe 123 rty

all:	liboutput_static.a liboutput.so prog prog-a prog-so test

fun.o prog.o:	outlib.h

.SECONDARY:	liboutput_static.a(fun.o const.o)

liboutput_static.a:	liboutput_static.a(fun.o const.o)

liboutput.so:	fun.o const.o
	$(CC) $^ -o $@ -shared	

prog:	prog.o fun.o const.o

prog-a:	prog.o liboutput_static.a
	$(CC) -L. $< -loutput_static -o $@

prog-so:	prog.o liboutput.so
	$(CC) -L. $< -loutput -o $@
	
test%:	prog prog-a prog-so
	./prog $(ARGS-$@) > $@.txt 2>&1
	./prog-a $(ARGS-$@) > $@-a.txt 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so $(ARGS-$@) > $@-so.txt 2>&1
	cmp $@.txt $@-a.txt
	cmp $@.txt $@-so.txt

test:	test1 test2 test3

clean:
	rm -f $(TRASH) $(GENS) $(TESTS)
