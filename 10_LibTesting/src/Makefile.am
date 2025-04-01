CFLAGS = -std=c99 -Wall -Wextra
if COND_GCOV
CFLAGS += -O0 -g -fprofile-arcs -ftest-coverage
else
CFLAGS += -O3 -g3
endif

lib_LTLIBRARIES = libbuf.la

gcov:
	gcov -o .libs libbuf -t -k -b | egrep -v '[[:digit:]]:[ /][*]'

covperc:
	gcov -o .libs libbuf -t -f -b | grep -e 'Lines executed' -e 'blocks executed'
