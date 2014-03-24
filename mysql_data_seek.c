/* Copyright (C) 2005, 2006 Hartmut Holzgraefe

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
 * MySQL C client API example: mysql_data_seek()
 *
 * see also http://mysql.com/mysql_data_seek
 */

/* comment: why no return value? */
#include "config.h"

#include <stdlib.h>
#include <stdio.h>

#include <mysql.h>

int main(int argc, char **argv) 
{
  MYSQL *mysql = NULL;

  mysql = mysql_init(mysql);

  if (!mysql) {
    puts("Init faild, out of memory?");
    return EXIT_FAILURE;
  }
        
  if (!mysql_real_connect(mysql,       /* MYSQL structure to use */
			  MYSQL_HOST,  /* server hostname or IP address */ 
			  MYSQL_USER,  /* mysql user */
			  MYSQL_PWD,   /* password */
			  MYSQL_DB,    /* default database to use, NULL for none */
			  0,           /* port number, 0 for default */
			  NULL,        /* socket file or named pipe name */
			  CLIENT_FOUND_ROWS /* connection flags */ )) {
    puts("Connect failed\n");
  } else {                
    if (mysql_query(mysql, "SELECT * FROM world.Country")) {
      printf("Query failed: %s\n", mysql_error(mysql));
    } else {
      MYSQL_RES *result = mysql_store_result(mysql);

      if (result) {
	MYSQL_ROW row;
	int i;
	unsigned int num_fields = mysql_num_fields(result);
                                                                
	puts("Got a valid result set, looking for 3rd result row\n");

	mysql_data_seek(result, 3);
                          
	row = mysql_fetch_row(result);
                                
	if (row) {
	  for (i = 0; i < num_fields; i++) {
	    printf("%s, ", row[i]);
	  }
	  putchar('\n');
                                        
	  mysql_free_result(result);
	} else {
	  puts("result has less than 3 rows");
	}
      } else {
	printf("Couldn't get results set: %s\n", mysql_error(mysql));
      }
    }
  }
        
  mysql_close(mysql);

  return EXIT_SUCCESS;
}
