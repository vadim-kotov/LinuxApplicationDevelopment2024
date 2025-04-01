AM_CPPFLAGS=-D'LOCALEDIR="$(localedir)"'

bin_PROGRAMS=guess

guess_SOURCES=src/guess.c src/roman_table.h

SUBDIRS=po src

@DX_RULES@

all-local: doxygen-doc man

man: guess
	mkdir -p doxygen-doc/man/man1
	help2man -N ./$< > doxygen-doc/man/man1/$<.1

install-data-local:
	mkdir -p $(DESTDIR)/$(docdir)
	cp -a doxygen-doc/html $(DESTDIR)/$(docdir)
	cp -a doxygen-doc/man $(DESTDIR)/$(docdir)

http:	doxygen-doc
	python3 -m http.server --directory $</html 5000

gitclean:
	git clean -xdf
