AC_PREREQ([2.69])
AC_INIT([api-examples], [1.0], [hartmut@php.net])
AM_INIT_AUTOMAKE([1.11 tar-pax silent-rules -Wall -Werror])
AC_CONFIG_MACRO_DIRS([m4])
AM_SILENT_RULES([yes])

AC_PROG_CC

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([Makefile])

WITH_MYSQL()
MYSQL_USE_CLIENT_API()
MYSQL_SUBST()

AC_OUTPUT()

