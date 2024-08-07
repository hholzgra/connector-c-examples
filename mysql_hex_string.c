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
 * MariaDB Connector/C client API example: mysql_hex_string()
 *
 * see also:
 * * https://mariadb.com/kb/en/mysql_hex_string/
 * * https://github.com/mariadb-corporation/mariadb-connector-c/wiki/mysql_hex_string
 * * https://mysql.com/mysql_hex_string
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mysql.h>

#include "helpers.h"

/* TODO: is the target buffer length formula still true??? */

int main(int argc, char **argv) 
{
  MYSQL *mysql = helper_connect(argc, argv); /* see helper.h for actual code */
  
  const char *from = "Rüdiger's";
  char to[201];
  unsigned long len;
  
  len = mysql_hex_string(to, from, strlen(from));
  to[len] = '\0';
  printf("Hex encoded string for '%s' is: \"%s\" (%lu)\n", from, to, len);
  
  helper_end(mysql); /* see helper.h for actual code */
  
  return EXIT_SUCCESS;
}
