SUBDIRS = src tests

checklog: check
	cat tests/*.log
if COND_GCOV
	$(MAKE) $(MAKEFLAGS) -C src covperc
endif

gcov: check
	$(MAKE) $(MAKEFLAGS) -C src gcov

gitclean:
	git clean -xdf
