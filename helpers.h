/* Copyright (C) 2022 - 2024 Hartmut Holzgraefe <hartmut@php.net>

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

#ifndef _HELPERS_H
#define _HELPERS_H 1

#include <stdlib.h>
#include <stdio.h>

#include <mysql.h>

MYSQL *helper_connect(int argc, char **argv)
{
  MYSQL *mysql = NULL;

  if (mysql_library_init(argc, argv, NULL)) {
    fprintf(stderr, "could not initialize MySQL client library\n");
    exit(1);
  }
 
  mysql = mysql_init(mysql);

  if (!mysql) {
    fprintf(stderr, "Init faild, out of memory?");
    exit(EXIT_FAILURE);
  }
        
  mysql_options(mysql, MYSQL_READ_DEFAULT_FILE, (void *)"./my.cnf");

  if (!mysql_real_connect(mysql, /* MYSQL structure to use */
                          NULL,  /* server hostname or IP address */ 
                          NULL,  /* mysql user */
                          NULL,  /* password */
                          NULL,  /* default database to use, NULL for none */
                          0,     /* port number, 0 for default */
                          NULL,   /* socket file or named pipe name */
                          CLIENT_FOUND_ROWS /* connection flags */ )) {
    fprintf(stderr, "Connect failed\n");
    mysql_library_end();
    exit(EXIT_FAILURE);
  }

  return mysql;
}

void helper_end(MYSQL *mysql)
{
  mysql_close(mysql);
  mysql_library_end();
}

#endif /* _HELPERS_H */
