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
 * MySQL C client API example: mysql_errno()
 *
 * see also http://mysql.com/mysql_errno
 */

/*
 * MySQL C client API examples: mysql_errno() 
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>

#include <mysql.h>

int main(int argc, char **argv) 
{
  MYSQL *mysql = NULL;
  MYSQL *con;

  mysql = mysql_init(mysql);

  if (!mysql) {
    puts("Init faild, out of memory?");
    return EXIT_FAILURE;
  }
  
  con = mysql_real_connect(mysql,            /* MYSQL structure to use */
                           "nosuchhost",     /* server hostname or IP address */ 
                           "nosuchuser",     /* mysql user */
                           "",               /* password */
                           "nosuchdb",       /* default database to use */
                           0,                /* port number, 0 for default */
                           NULL,             /* socket file or named pipe name */
                           CLIENT_FOUND_ROWS /* connection flags */ ); 

  printf("MySQL errno for failed connect: %u \n", mysql_errno(mysql));
  /* the error information is not reset by mysql_errno() */
  printf("MySQL errno for failed connect: %u \n", mysql_errno(mysql));
  
  mysql_close(mysql);

  return EXIT_SUCCESS;
}
