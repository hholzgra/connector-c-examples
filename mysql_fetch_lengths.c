/* Copyright (C) 2005 - 2022 Hartmut Holzgraefe <hartmut@php.net>

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
 * MariaDB Connector/C client API example: mysql_fetch_lengths()
 *
 * see also:
 * * https://mariadb.com/kb/en/mysql_fetch_lengths/
 * * https://github.com/mariadb-corporation/mariadb-connector-c/wiki/mysql_fetch_lengths
 * * https://mysql.com/mysql_fetch_lengths
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>

#include <mysql.h>

#include "helpers.h"

int main(int argc, char **argv)
{
  MYSQL *mysql = helper_connect(argc, argv); /* see helper.h for actual code */

  if (mysql_query(mysql, "SELECT * FROM City LIMIT 10")) {
    printf("Query failed: %s\n", mysql_error(mysql));
  } else {
    MYSQL_RES *result = mysql_store_result(mysql);
    
    if (!result) {
      printf("Couldn't get results set: %s\n", mysql_error(mysql));
    } else {
      MYSQL_ROW row;
      unsigned int num_fields = mysql_num_fields(result);
      
      while ((row = mysql_fetch_row(result)))
	{
	  int i;
	  unsigned long *lengths = mysql_fetch_lengths(result);
	  
	  for(i = 0; i < num_fields; i++) {
	    printf("[%.*s] ", (int) lengths[i], row[i] ? row[i] : "NULL");
	  }
	  printf("\n");
	  
	}             
    }
  }
        
  helper_end(mysql); /* see helper.h for actual code */

  return EXIT_SUCCESS;
}
