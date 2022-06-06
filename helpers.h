#ifndef _HELPERS_H
#define _HELPERS_H 1

#include <stdlib.h>
#include <stdio.h>

#include <mysql.h>

MYSQL *helper_connect(int argc, char **argv)
{
  MYSQL *mysql = NULL;

  if (mysql_library_init(argc, argv, NULL)) {
    fprintf(stderr, "could not initialize MySQL client library\n");
    exit(1);
  }
 
  mysql = mysql_init(mysql);

  if (!mysql) {
    fprintf(stderr, "Init faild, out of memory?");
    exit(EXIT_FAILURE);
  }
        
  mysql_options(mysql, MYSQL_READ_DEFAULT_FILE, (void *)"./my.cnf");

  if (!mysql_real_connect(mysql, /* MYSQL structure to use */
                          NULL,  /* server hostname or IP address */ 
                          NULL,  /* mysql user */
                          NULL,  /* password */
                          NULL,  /* default database to use, NULL for none */
                          0,     /* port number, 0 for default */
                          NULL,   /* socket file or named pipe name */
                          CLIENT_FOUND_ROWS /* connection flags */ )) {
    fprintf(stderr, "Connect failed\n");
    mysql_library_end();
    exit(EXIT_FAILURE);
  }

  return mysql;
}

void helper_end(MYSQL *mysql)
{
  mysql_close(mysql);
  mysql_library_end();
}

#endif /* _HELPERS_H */
