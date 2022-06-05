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

/* mariadb_get_infov convenience wrapper macros
   these will retrieve and print the value for a given info type */

#define STRING_INFO(x)     if (mariadb_get_infov(mysql, x, (void *)&string_info)) { \
      printf("Couldn't get %s\n", #x);					\
    } else { \
      printf("%-40s: %s\n", #x, string_info);	\
    } 

#define UINT_INFO(x)     if (mariadb_get_infov(mysql, x, (void *)&uint_info)) { \
      printf("Couldn't get %s\n", #x);					\
    } else { \
      printf("%-40s: %d\n", #x, uint_info);	\
    } 

int main(int argc, char **argv) 
{
  MYSQL *mysql = NULL;
  const char *string_info;
  unsigned int uint_info;
  
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

    /* TODO there are many more options, see e.g. 
       https://mariadb.com/kb/en/mariadb_get_infov/
    */
    
    STRING_INFO(MARIADB_TLS_LIBRARY);
    STRING_INFO(MARIADB_CONNECTION_TLS_VERSION);
    UINT_INFO(MARIADB_CONNECTION_TLS_VERSION_ID);

    STRING_INFO(MARIADB_CLIENT_VERSION);
    UINT_INFO(MARIADB_CLIENT_VERSION_ID);

    STRING_INFO(MARIADB_CONNECTION_HOST);
    STRING_INFO(MARIADB_CONNECTION_INFO);
    STRING_INFO(MARIADB_CONNECTION_SERVER_TYPE);
  }

  mysql_close(mysql);

  mysql_library_end();
  
  return EXIT_SUCCESS;
}
