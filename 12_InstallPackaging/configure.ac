#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Number guesser], [0.1], [vadia55@list.ru], [guess])
AM_INIT_AUTOMAKE([foreign subdir-objects])
DX_INIT_DOXYGEN([guess])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_REQUIRE_VERSION(0.21)
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])
AC_SUBST(GETTEXT_PACKAGE, "$PACKAGE")
ALL_LINGUAS="ru"

# Checks for programs.
AC_PROG_CC
IT_PROG_INTLTOOL([0.35.0])
AC_CHECK_PROG([PYTHON_CHECK], [python3], [yes], [no])
AS_IF([test "x$PYTHON_CHECK" = "xno"],
      [AC_MSG_ERROR([Python 3 is required to generate roman table])])

# Joint pkgconfig library/include check and variable definition.
PKG_CHECK_MODULES([CHECK],[check])
AC_SUBST(CK_VERBOSITY, verbose)
AC_ARG_VAR(CK_VERBOSITY, [Default: "verbose", can be "silent", "minimal" or "normal")])

#Enable gcov
AC_ARG_ENABLE([gcov],
	      [AS_HELP_STRING([--enable-gcov], [use Gcov to test the test suite])],
	      [], [enable_gcov=no])
AM_CONDITIONAL([COND_GCOV],[test '!' "$enable_gcov" = no])

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile po/Makefile.in src/Makefile Doxyfile tests/Makefile])
AC_OUTPUT
