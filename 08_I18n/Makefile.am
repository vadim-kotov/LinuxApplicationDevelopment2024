bin_PROGRAMS=guess
pkgdata_DATA=ru/LC_MESSAGES/guess.mo

ru/LC_MESSAGES/guess.mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

ru.po:	messages.pot
	msmerge -U $@ $<

messages.pot:	guess.c
	xgettext -k_ -c guess.c -o messages.pot
