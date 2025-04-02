SUBDIRS=po src tests

AM_CPPFLAGS=-D'LOCALEDIR="$(localedir)"'

guess_SOURCES=src/guess.c src/libroman.c src/roman_table.h

CFLAGS = -Wall -Wextra
if COND_GCOV
CFLAGS += -O0 -g -fprofile-arcs -ftest-coverage
endif

bin_PROGRAMS = guess

@DX_RULES@

all-local: doxygen-doc $(man_MANS)

checklog: check
	cat tests/*.log
if COND_GCOV
	gcov -o src libroman -t -f -b | grep -e 'Lines executed' -e 'blocks executed'
endif

gcov: check
	gcov -o src libroman -t -k -b | egrep -v '[[:digit:]]:[ /][*]'

man_MANS=man/guess.1

man/guess.1: guess
	mkdir -p man
	help2man -N ./$< > man/$<.1

CLEANFILES = $(man_MANS)

#man: guess
#	mkdir -p doxygen-doc/man/man1
#	help2man -N ./$< > doxygen-doc/man/man1/$<.1

#install-data-local:
#	mkdir -p $(DESTDIR)/$(docdir)
#	cp -a doxygen-doc/html $(DESTDIR)/$(docdir)
#	cp -a doxygen-doc/man $(DESTDIR)/$(docdir)

#uninstall-local:
#	rm -rf $(DESTDIR)/$(docdir)/html
#	rm -rf $(DESTDIR)/$(docdir)/man

http:	doxygen-doc
	python3 -m http.server --directory $</html 5000

gitclean:
	git clean -xdf
