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
 * MariaDB Connector/C client API example: mysql_list_tables()
 *
 * see also http://mysql.com/mysql_list_tables
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>

#include <mysql.h>

#include "helpers.h"

int main(int argc, char **argv) 
{
  MYSQL *mysql = helper_connect(argc, argv); /* see helper.h for actual code */
  MYSQL_RES *result = mysql_list_tables(mysql, "%" /* fetch all */);

  if (!result) {
    printf("Couldn't get process list: %s\n", mysql_error(mysql));
  } else {
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
      printf("%s\n", row[0]);
    }
    
    mysql_free_result(result);
  }
        
  helper_end(mysql); /* see helper.h for actual code */

  return EXIT_SUCCESS;
}
