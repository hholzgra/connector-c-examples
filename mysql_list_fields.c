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
 * MySQL C client API example: mysql_list_fields()
 *
 * see also http://mysql.com/mysql_list_fields
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>

#include <mysql.h>

/* TODO: doesn't return any fields? broken? */

int main(int argc, char **argv) 
{
  MYSQL *mysql = NULL;

  mysql = mysql_init(mysql);

  if (!mysql) {
    puts("Init faild, out of memory?");
    return EXIT_FAILURE;
  }
        
  if (!mysql_real_connect(mysql,       /* MYSQL structure to use */
			  MYSQL_HOST,         /* server hostname or IP address */ 
			  MYSQL_USER,         /* mysql user */
			  MYSQL_PWD,          /* password */
			  MYSQL_DB,           /* default database to use, NULL for none */
			  0,           /* port number, 0 for default */
			  NULL,        /* socket file or named pipe name */
			  CLIENT_FOUND_ROWS /* connection flags */ )) {
    puts("Connect failed\n");
  } else {                
    MYSQL_RES *result = mysql_list_fields(mysql, "City", "%" /* fetch all */);

    if (!result) {
      printf("Couldn't get field list: %s\n", mysql_error(mysql));
    } else {
      MYSQL_ROW row;
                        
      while ((row = mysql_fetch_row(result))) {
	puts(row[0]);
      }

      mysql_free_result(result);
    }
  }
        
  mysql_close(mysql);

  return EXIT_SUCCESS;
}
