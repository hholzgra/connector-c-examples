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
 * MariaDB Connector/C client API example: mysql_info()
 *
 * see also:
 * * https://mariadb.com/kb/en/mysql_info/
 * * https://github.com/mariadb-corporation/mariadb-connector-c/wiki/mysql_info
 * * https://mysql.com/mysql_info
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>

#include <mysql.h>

#include "helpers.h"

/* TODO: add dummy UPDATE statement */

int main(int argc, char **argv) 
{
  MYSQL *mysql = helper_connect(argc, argv); /* see helper.h for actual code */

  printf("MySQL Info: %s\n", mysql_info(mysql));

  helper_end(mysql); /* see helper.h for actual code */
  
  return EXIT_SUCCESS;
}
