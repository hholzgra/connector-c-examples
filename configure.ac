AC_PREREQ([2.69])
AC_INIT([api-examples], [1.0], [hartmut@php.net])
AM_INIT_AUTOMAKE([1.11 tar-pax silent-rules -Wall -Werror])
AM_SILENT_RULES([yes])
AC_CONFIG_HEADERS(config.h)
AC_PROG_LIBTOOL

WITH_MYSQL()
MYSQL_USE_CLIENT_API()
MYSQL_SUBST()

AC_OUTPUT(Makefile)

