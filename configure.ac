AC_PREREQ([2.69])
AC_INIT([connector-c-examples], [1.0.1], [hartmut@php.net])
AM_INIT_AUTOMAKE([1.11 tar-pax silent-rules -Wall -Werror])
AC_CONFIG_MACRO_DIRS([m4])
AM_SILENT_RULES([yes])

AC_PROG_CC

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([Makefile])

WITH_MYSQL()
MYSQL_USE_CLIENT_API()
MYSQL_SUBST()
LIBS=$MYSQL_LIBS
AC_CHECK_FUNCS(mariadb_get_infov,
	[AM_CONDITIONAL([HAVE_MARIADB_GET_INFOV], [true])],
	[AM_CONDITIONAL([HAVE_MARIADB_GET_INFOV], [false])]
	)

AC_OUTPUT()

