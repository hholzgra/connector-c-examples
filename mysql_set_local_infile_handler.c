/* Copyright (C) 2014 Hartmut Holzgraefe

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
 * MySQL C client API example: mysql_set_local_infile_handler()
 *
 * see also http://mysql.com/mysql_set_local_infile_handler
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mysql.h>

int line_count = 0;

int local_infile_init(void **ptr, const char *filename, void *userdata)
{
  printf("INIT %s\n", filename);

  line_count = 0;

  return 0;
}

int local_infile_read(void *ptr, char *buf, unsigned int buf_len)
{
  printf("READ %d\n", line_count);

  switch (line_count++) {
  case 0: strcpy(buf, "23,bar\n"); break;
  case 1: strcpy(buf, "42,bar\n"); break;
  default: return 0;
  }
  return strlen(buf);
}

void local_infile_end(void *ptr)
{
  printf("END\n");
}

int local_infile_error(void *ptr, char *error_msg, unsigned int error_msg_len)
{
  printf("somethings wrong\n");

  strcpy(error_msg, "somethings wrong");
  return 1234;
}

int main(int argc, char **argv) 
{
  MYSQL *mysql = NULL;
  int opt_local_infile = 1; 
  int stat;
        
  mysql = mysql_init(mysql);

  if (!mysql) {
    puts("Init faild, out of memory?");
    return EXIT_FAILURE;
  }

  mysql_options(mysql, MYSQL_OPT_LOCAL_INFILE, (char*) &opt_local_infile);

  if (!mysql_real_connect(mysql,              /* MYSQL structure to use */
			  MYSQL_HOST,         /* server hostname or IP address */ 
			  MYSQL_USER,         /* mysql user */
			  MYSQL_PWD,          /* password */
			  MYSQL_DB,           /* default database to use, NULL for none */
			  0,                  /* port number, 0 for default */
			  NULL,               /* socket file or named pipe name */
			  0                   /* client flags */
			  )) {
    fprintf(stderr, "Connect failed: %s\n", mysql_error(mysql));
    exit(EXIT_FAILURE);
  } else {
    puts("Connect OK\n");
  }

  mysql_set_local_infile_handler(mysql, local_infile_init, local_infile_read, local_infile_end, local_infile_error, NULL);

  stat = mysql_query(mysql, "LOAD DATA LOCAL INFILE '-' INTO TABLE test.foo FIELDS TERMINATED BY ','");

  if (stat) {
    fprintf(stderr, "stat: %d %d %s\n", stat, mysql_errno(mysql), mysql_error(mysql));
  }

  mysql_close(mysql);

  return EXIT_SUCCESS;
}

