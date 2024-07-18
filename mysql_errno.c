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
 * MariaDB Connector/C client API example: mysql_errno()
 *
 * see also http://mysql.com/mysql_errno
 */

/*
 * MariaDB Connector/C client API examples: mysql_errno() 
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>

#include <mysql.h>

#include "helpers.h"

int main(int argc, char **argv) 
{
  MYSQL *mysql = helper_connect(argc, argv); /* see helper.h for actual code */

  mysql_query(mysql, "this is not valid SQL");
  
  printf("MySQL errno: %u \n", mysql_errno(mysql));
  /* the error information is not reset by calls to mysql_errno() */
  printf("MySQL errno: %u \n", mysql_errno(mysql));
  
  helper_end(mysql); /* see helper.h for actual code */

  return EXIT_SUCCESS;
}
