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

#include <mysql.h>

static char *server_groups[] = {
  "embedded",
  "server",
  (char *)NULL
};

int main(int argc, char **argv) 
{
  MYSQL *mysql = NULL;
  int i;
  char query[256];

  if (mysql_server_init(argc, argv, server_groups)) {
	fputs("server init failed", stderr);
	return EXIT_FAILURE;
  }

  mysql_thread_init(); 
  
  MYSQL* handle = mysql_init(NULL); 
   mysql_options(handle, MYSQL_READ_DEFAULT_GROUP, "libmysqld_client");
   mysql_options(handle, MYSQL_OPT_USE_EMBEDDED_CONNECTION, NULL);  mysql_real_connect(handle, NULL, NULL, NULL, "test", 0, NULL, 0); 
  for(i=0; 1; i++) 
  { 
	printf("iteration %d\n", i); 
	MYSQL_STMT* stmt = mysql_stmt_init(handle); 
	char* command = "SELECT 1 FROM i1"; 
//char* command = "UPDATE T1 SET i1 = 1"; 
	mysql_stmt_prepare(stmt, command, strlen(command)); 
	mysql_stmt_execute(stmt); 
 	mysql_stmt_store_result(stmt);
	while (!mysql_stmt_fetch(stmt)) {}
	mysql_stmt_free_result(stmt); 
	mysql_stmt_close(stmt); 
  } 
  mysql_close(handle); 
  
} 
 

