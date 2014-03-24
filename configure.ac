AC_PREREQ([2.69])
AC_INIT([api-examples], [1.0], [hartmut@skysql.com])
AM_INIT_AUTOMAKE([1.11 tar-pax silent-rules -Wall -Werror])
AM_SILENT_RULES([yes])
AC_CONFIG_HEADERS(config.h)
AC_PROG_LIBTOOL

WITH_MYSQL()
MYSQL_USE_CLIENT_API()
MYSQL_SUBST()

if test "x$MYSQL_HOST" = "x"
then
	MYSQL_HOST="127.0.0.1"
fi

if test "x$MYSQL_USER" = "x"
then
	MYSQL_USER="root"
fi

if test "x$MYSQL_DB" = "x"
then
	MYSQL_DB="world"
fi

AC_ARG_VAR(MYSQL_HOST,     [mysql host     [default=127.0.0.1]])
AC_ARG_VAR(MYSQL_DB,       [mysql database [default=test]])
AC_ARG_VAR(MYSQL_USER,     [mysql user     [default=root]])
AC_ARG_VAR(MYSQL_PWD,      [mysql password [default=]])

AC_DEFINE_UNQUOTED([MYSQL_HOST], ["$MYSQL_HOST"],[mysql host])
AC_DEFINE_UNQUOTED([MYSQL_DB],   ["$MYSQL_DB"]  ,[mysql database])
AC_DEFINE_UNQUOTED([MYSQL_USER], ["$MYSQL_USER"],[mysql user])
AC_DEFINE_UNQUOTED([MYSQL_PWD],  ["$MYSQL_PWD"] ,[mysql password])

AC_OUTPUT(Makefile)

