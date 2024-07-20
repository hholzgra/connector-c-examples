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
 * MariaDB Connector/C client API example: mysql_data_seek()
 *
 * see also:
 * * https://mariadb.com/kb/en/mysql_data_seek/
 * * https://github.com/mariadb-corporation/mariadb-connector-c/wiki/mysql_data_seek
 * * https://mysql.com/mysql_data_seek
 */

/* comment: why no return value? */
#include "config.h"

#include <stdlib.h>
#include <stdio.h>

#include <mysql.h>

#include "helpers.h"

int main(int argc, char **argv)
{
  MYSQL *mysql = helper_connect(argc, argv); /* see helper.h for actual code */

  if (mysql_query(mysql, "SELECT user,host FROM mysql.user")) {
    printf("Query failed: %s\n", mysql_error(mysql));
  } else {
    MYSQL_RES *result = mysql_store_result(mysql);

    if (result) {
      MYSQL_ROW row;
      int rownum = 3, i;
      unsigned int num_fields = mysql_num_fields(result);

      printf("Got a valid result set, looking for result row #%d\n", rownum);

      mysql_data_seek(result, rownum);

      row = mysql_fetch_row(result);

      if (row) {
	printf("  ROW: ");
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

  helper_end(mysql); /* see helper.h for actual code */

  return EXIT_SUCCESS;
}
