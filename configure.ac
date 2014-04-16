#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT(avgcalc, 0.1, erik@ibiblio.org)
AM_INIT_AUTOMAKE(avgcalc, 0.1)
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

AM_GNU_GETTEXT([external])
AC_CHECK_PROG(MSGFMT, msgfmt, /usr/bin/msgfmt) 
# Checks for library functions.
AC_FUNC_STRTOD
AC_CHECK_FUNCS([pow setlocale sqrt strerror gettext])

AC_OUTPUT( Makefile src/Makefile doc/Makefile man/Makefile intl/Makefile po/Makefile )

