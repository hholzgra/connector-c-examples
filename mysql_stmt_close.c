/* Copyright (C) 2005 - 2024 Hartmut Holzgraefe <hartmut@php.net>

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
 * MariaDB Connector/C client API example: mysql_stmt_close()
 *
 * see also:
 * * https://mariadb.com/kb/en/mysql_stmt_close/
 * * https://github.com/mariadb-corporation/mariadb-connector-c/wiki/mysql_stmt_close
 * * https://mysql.com/mysql_stmt_close
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>

#include <mysql.h>

int main(int argc, char **argv) 
{
  MYSQL *mysql = NULL;

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
    puts("Connect failed\n");
  } else {
    MYSQL_STMT *stmt;

    stmt = mysql_stmt_init(mysql);

    if (stmt) {
      puts("Statement init OK!");
    } else {
      printf("Statement init failed: %s\n", mysql_error(mysql));
    }


    if (stmt && mysql_stmt_close(stmt)) {
      printf("Statement close failed: %s\n", mysql_stmt_error(stmt));
    } else {
      puts("Statement close OK!");
    }
  }
        
  mysql_close(mysql);

  mysql_library_end();
  
  return EXIT_SUCCESS;
}
