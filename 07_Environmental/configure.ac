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

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h strings.h])
AC_CHECK_HEADER([rhash.h])

# Optional clues
AC_ARG_WITH([readline], 
	    [AS_HELP_STRING([--with-readline], [enable readline])],
            [],
            [with_readline=no])
          
LIBREADLINE=
AS_IF([test "x$with_readline" != xno], 
      [AC_CHECK_LIB([readline], [main],
		    [AC_SUBST([LIBREADLINE], ["-lreadline"])
		    AC_DEFINE([READLINE], [1], [Define if you have libreadline])],
              [AC_MSG_FAILURE(
                 [--with-readline was given, but test for readline failed])]
	      )])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strcasecmp strerror])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
