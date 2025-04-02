TESTS_ENVIRONMENT = CK_VERBOSITY=$(CK_VERBOSITY)
TESTS = upstream
check_PROGRAMS = upstream

%.c: %.ts
	checkmk $< > $@

AM_CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LDADD = $(top_builddir)/src/libroman.o @CHECK_LIBS@
if COND_GCOV
LDADD += -lgcov
endif
