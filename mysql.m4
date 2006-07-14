dnl
dnl configure.in helper macros
dnl 
 
AC_DEFUN([WITH_MYSQL], [ 
  AC_MSG_CHECKING(for mysql_config executable)

  AC_ARG_WITH(mysql, [  --with-mysql=PATH	path to mysql_config binary or mysql prefix dir], [
	if test -x $withval -a -f $withval
    then
      MYSQL_CONFIG=$withval
    elif test -x $withval/bin/mysql_config -a -f $withval/bin/mysql_config
    then 
     MYSQL_CONFIG=$withval/bin/mysql_config
    fi
  ], [
	if test -x /usr/local/mysql/bin/mysql_config -a -f /usr/local/mysql/bin/mysql_config
    then
      MYSQL_CONFIG=/usr/local/mysql/bin/mysql_config
    elif test -x /usr/bin/mysql_config -a -f /usr/bin/mysql_config
    then
      MYSQL_CONFIG=/usr/bin/mysql_config
    fi
  ])

  if test "x$MYSQL_CONFIG" = "x" 
  then
    AC_MSG_RESULT(not found)
    exit 3
  else
    AC_PROG_CC
 
    CFLAGS="$CFLAGS "`$MYSQL_CONFIG --cflags` 

    LDFLAGS="$LDFLAGS "`$MYSQL_CONFIG --libs_r`
    
    AC_MSG_RESULT($MYSQL_CONFIG)
  fi

  
])
