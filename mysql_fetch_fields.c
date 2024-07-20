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
 * MariaDB Connector/C client API example: mysql_fetch_fields()
 *
 * see also:
 * * https://mariadb.com/kb/en/mysql_fetch_fields/
 * * https://github.com/mariadb-corporation/mariadb-connector-c/wiki/mysql_fetch_fields
 * * https://mysql.com/mysql_fetch_fields
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>

#include <mysql.h>

#include "helpers.h"

int main(int argc, char **argv)
{
  MYSQL *mysql = helper_connect(argc, argv); /* see helper.h for actual code */

  mysql_query(mysql, "SET NAMES utf8");
  if (mysql_query(mysql, "SELECT LPAD(i, 7, ' ') as t FROM test.f LIMIT 1")) {
    printf("Query failed: %s\n", mysql_error(mysql));
  } else {
    MYSQL_RES *result = mysql_store_result(mysql);
    
    if (!result) {
      printf("Couldn't get results set: %s\n", mysql_error(mysql));
    } else {
      MYSQL_FIELD *fields;
      
      fields = mysql_fetch_fields(result);
      
      if (!fields) {
	printf("Faild fetching fields: %s\n", mysql_error(mysql));
      } else {
	unsigned int i, num_fields = mysql_num_fields(result);
	
	for (i = 0; i < num_fields; i++) {
	  printf("FIELD #%d\n", i);
	  printf("  %-20s %s\n", "Field name", fields[i].name);
#if MYSQL_VERSION_ID >= 40100
	  printf("  %-20s %s\n", "Original name", fields[i].org_name);
#endif
	  printf("  %-20s %s\n", "From table", fields[i].table);
	  printf("  %-20s %s\n", "Original name", fields[i].org_table);
	  printf("  %-20s %s\n", "Database", fields[i].db);
#if MYSQL_VERSION_ID >= 40100
	  printf("  %-20s %s\n", "Catalog", fields[i].catalog);
#endif
	  printf("  %-20s %s\n", "Default", fields[i].def);
	  printf("  %-20s %lu\n", "CREATE field length", fields[i].length);
	  printf("  %-20s %lu\n", "MAX field lengt", fields[i].max_length);
#if MYSQL_VERSION_ID >= 40100
	  printf("  %-20s %u\n", "Field name length", fields[i].name_length);
	  printf("  %-20s %u\n", "Original name length", fields[i].org_name_length);
	  printf("  %-20s %u\n", "Table name length", fields[i].table_length);
	  printf("  %-20s %u\n", "Original name length", fields[i].org_table_length);
	  printf("  %-20s %u\n", "DB name length", fields[i].db_length);
	  printf("  %-20s %u\n", "Catalog name length", fields[i].catalog_length);
	  printf("  %-20s %u\n", "Default length", fields[i].def_length);
#endif
	  /* TODO: decimals */
	  printf("\n");
	  }
      }
    }
  }

  helper_end(mysql); /* see helper.h for actual code */

  return EXIT_SUCCESS;
}
