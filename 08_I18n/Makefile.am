AM_CPPFLAGS=-D'LOCALEDIR="$(localedir)"'

bin_PROGRAMS=guess

guess_SOURCES=src/guess.c

SUBDIRS=po

#ru/LC_MESSAGES/guess.mo: ru.po
#	mkdir -p `dirname $@`
#	msgfmt $< -o $@
#
#ru.po:	messages.pot
#	msgmerge -U $@ $<

#messages.pot:	guess.c
#	xgettext -k_ -c guess.c -o messages.pot
