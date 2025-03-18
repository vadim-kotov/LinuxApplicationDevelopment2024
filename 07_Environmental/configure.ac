#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([rhasher], [0.1], [vadia55@list.ru])
AC_CONFIG_SRCDIR([src/rhasher.c])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash], [rhash_msg], [], [RHash is needed])
AC_CHECK_LIB([readline], [readline])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h strings.h])
AC_CHECK_HEADER([rhash.h])

# Optional clues
AC_ARG_ENABLE([readline],
	      AS_HELP_STRING([--enable-readline], [Enables readline]),
	      AC_DEFINE(READLINE, [], [Enables readline])
	      )

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strcasecmp strerror])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
