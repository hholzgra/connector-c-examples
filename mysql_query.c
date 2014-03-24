/* Copyright (C) 2005 MySQL AB

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
 * MySQL C client API example: mysql_query()
 *
 * see also http://mysql.com/mysql_query
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mysql.h>

static char *server_groups[] = {
  "embedded",
  "server",
  (char *)NULL
};

int main(int argc, char **argv) 
{
  MYSQL *mysql;
  int i;

  if (mysql_server_init(argc, argv, server_groups)) {
    fputs("server init failed", stderr);
    return EXIT_FAILURE;
  }

  mysql_thread_init(); 
  
  mysql = mysql_init(NULL); 
  mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "libmysqld_client");
  mysql_options(mysql, MYSQL_OPT_USE_EMBEDDED_CONNECTION, NULL);  
 
  if (!mysql_real_connect(mysql,       /* MYSQL structure to use */
                          MYSQL_HOST,         /* server hostname or IP address */ 
                          MYSQL_USER,         /* mysql user */
                          MYSQL_PWD,          /* password */
                          NULL,           /* default database to use, NULL for none */
                          0,           /* port number, 0 for default */
                          NULL,        /* socket file or named pipe name */
                          CLIENT_FOUND_ROWS /* connection flags */ )) {
    puts("Connect failed\n");
  } else {              

    for(i = 0; i < 10; i++) 
      { 
        printf("iteration %d\n", i); 
        MYSQL_STMT* stmt = mysql_stmt_init(mysql); 
        char* command = "SELECT 1 FROM i1"; 
        //char* command = "UPDATE T1 SET i1 = 1"; 
        mysql_stmt_prepare(stmt, command, strlen(command)); 
        mysql_stmt_execute(stmt); 
        mysql_stmt_store_result(stmt);
        while (!mysql_stmt_fetch(stmt)) {}
        mysql_stmt_free_result(stmt); 
        mysql_stmt_close(stmt); 
      } 

  }

  mysql_close(mysql); 
  
  return EXIT_SUCCESS; 
} 
 

