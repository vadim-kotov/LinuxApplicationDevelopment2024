.PHONY:	clean test
GENS = range
TESTS = *.out.txt
CFLAGS = -O0 -g

all: range

range:	range.c

test%:	range
	gdb --batch -quiet -x $@.gdb range | grep @@@ > $@.out.txt
	cmp $@.ref.txt $@.out.txt

test:	test1 test2

clean:
	rm -f $(TESTS) $(GENS)
