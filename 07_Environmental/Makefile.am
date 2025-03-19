CFLAGS=-Wall

bin_PROGRAMS=rhasher

rhasher_SOURCES=src/rhasher.c

rhasher_LDADD=$(LIBREADLINE)

TESTS = tests/test.sh

gitclean:
	git clean -xdf
