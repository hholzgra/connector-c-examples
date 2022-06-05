/* Copyright (C) 2005 - 2019 Hartmut Holzgraefe <hartmut@php.net>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
*/

/*
 * MySQL C client API example: mysql_real_connect()
 *
 * see also http://mysql.com/mysql_real_connect
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>

#include <mysql.h>

int main(int argc, char **argv) 
{
  MYSQL *mysql = NULL;
  const char *library;
  const char *version;
  unsigned int version_id;
  
  if (mysql_library_init(argc, argv, NULL)) {
    fprintf(stderr, "could not initialize MySQL client library\n");
    exit(1);
  }
 
  mysql = mysql_init(mysql);

  if (!mysql) {
    puts("Init faild, out of memory?");
    return EXIT_FAILURE;
  }
        
  mysql_options(mysql, MYSQL_READ_DEFAULT_FILE, (void *)"./my.cnf");

  /* no error handling here as mysql_ssl_set() always returns 0, 
     actual error handling happens in mysql_real_connect() later */
  mysql_ssl_set(mysql, "./ssl/client-key.pem", "./ssl/client-cert.pem", "./ssl/ca-cert.pem", NULL, NULL);
  
#ifdef HAVE_MARIADB_GET_INFOV
  mariadb_get_infov(mysql, MARIADB_TLS_LIBRARY, (void *)&library);
  printf("SSL client library: %s\n", library);
#endif /* HAVE_MARIADB_GET_INFOV */

  if (!mysql_real_connect(mysql,       /* MYSQL structure to use */
			  NULL,         /* server hostname or IP address */ 
			  NULL,         /* mysql user */
			  NULL,          /* password */
			  NULL,               /* default database to use, NULL for none */
			  0,           /* port number, 0 for default */
			  NULL,        /* socket file or named pipe name */
			  CLIENT_FOUND_ROWS /* connection flags */ )) {
    fprintf(stderr, "mysql_real_connect() failed: '%s'\n", mysql_error(mysql));
    puts("Connect failed\n");
  } else {
    puts("Connect OK\n");

#ifdef HAVE_MARIADB_GET_INFOV
    mariadb_get_infov(mysql, MARIADB_CONNECTION_TLS_VERSION, (void *)&version);
    printf("SSL version: %s\n", version);

    mariadb_get_infov(mysql, MARIADB_CONNECTION_TLS_VERSION_ID, (void *)&version_id);
    printf("SSL version ID: %d\n", version_id);
#endif /* HAVE_MARIADB_GET_INFOV */
  }

  mysql_close(mysql);

  mysql_library_end();
  
  return EXIT_SUCCESS;
}
