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
 * MySQL C client API example: mysql_stmt_bind_result()
 *
 * see also http://mysql.com/mysql_stmt_bind_result
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <mysql.h>

#define STRING_SIZE 50

#define SELECT_SAMPLE "SELECT col1, col2, col3, col4 FROM test_table WHERE !SLEEP(10)"

int main(int argc, char **argv) {
  MYSQL_STMT    *stmt;
  MYSQL_BIND    bind[4];
  MYSQL_RES     *prepare_meta_result;
  MYSQL_TIME    ts;
  unsigned long length[4];
  int           param_count, column_count, row_count;
  short         small_data;
  int           int_data;
  char          str_data[STRING_SIZE];
  my_bool       is_null[4];
  my_bool       error[4];
  MYSQL *mysql = NULL;
  int j;
  my_bool reconnect = 1;

  mysql = mysql_init(mysql);
  
  if (!mysql) {
    puts("Init faild, out of memory?");
    return EXIT_FAILURE;
  }
  
  mysql_options(mysql, MYSQL_OPT_RECONNECT, &reconnect);

  if (!mysql_real_connect(mysql,       /* MYSQL structure to use */
                          MYSQL_HOST,         /* server hostname or IP address */ 
                          MYSQL_USER,         /* mysql user */
                          MYSQL_PWD,          /* password */
                          MYSQL_DB,           /* default database to use, NULL for none */
                          0,           /* port number, 0 for default */
                          NULL,        /* socket file or named pipe name */
                          CLIENT_FOUND_ROWS /* connection flags */ )) {
    puts("Connect failed\n");
    return EXIT_FAILURE;
  }
  
  printf("connection id: %ld\n", mysql_thread_id(mysql));

  /* Prepare a SELECT query to fetch data from test_table */
  stmt = mysql_stmt_init(mysql);
  if (!stmt)
    {
      fprintf(stderr, " mysql_stmt_init(), out of memory\n");
      exit(0);
    }
  if (mysql_stmt_prepare(stmt, SELECT_SAMPLE, strlen(SELECT_SAMPLE)))
    {
      fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
      fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      exit(0);
    }
  fprintf(stdout, " prepare, SELECT successful\n");

  /* Get the parameter count from the statement */
  param_count= mysql_stmt_param_count(stmt);
  fprintf(stdout, " total parameters in SELECT: %d\n", param_count);

  if (param_count != 0) /* validate parameter count */
    {
      fprintf(stderr, " invalid parameter count returned by MySQL\n");
      exit(0);
    }

  /* Fetch result set meta information */
  prepare_meta_result = mysql_stmt_result_metadata(stmt);
  if (!prepare_meta_result)
    {
      fprintf(stderr,
	      " mysql_stmt_result_metadata(), returned no meta information\n");
      fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      exit(0);
    }

  /* Get total columns in the query */
  column_count= mysql_num_fields(prepare_meta_result);
  fprintf(stdout, " total columns in SELECT statement: %d\n", column_count);

  if (column_count != 4) /* validate column count */
    {
      fprintf(stderr, " invalid column count returned by MySQL\n");
      exit(0);
    }

  /* Bind the result buffers for all 4 columns before fetching them */

  memset(bind, 0, sizeof(bind));

  /* INTEGER COLUMN */
  bind[0].buffer_type= MYSQL_TYPE_LONG;
  bind[0].buffer= (char *)&int_data;
  bind[0].is_null= &is_null[0];
  bind[0].length= &length[0];
  bind[0].error= &error[0];

  /* STRING COLUMN */
  bind[1].buffer_type= MYSQL_TYPE_STRING;
  bind[1].buffer= (char *)str_data;
  bind[1].buffer_length= STRING_SIZE;
  bind[1].is_null= &is_null[1];
  bind[1].length= &length[1];
  bind[1].error= &error[1];

  /* SMALLINT COLUMN */
  bind[2].buffer_type= MYSQL_TYPE_SHORT;
  bind[2].buffer= (char *)&small_data;
  bind[2].is_null= &is_null[2];
  bind[2].length= &length[2];
  bind[2].error= &error[2];

  /* TIMESTAMP COLUMN */
  bind[3].buffer_type= MYSQL_TYPE_TIMESTAMP;
  bind[3].buffer= (char *)&ts;
  bind[3].is_null= &is_null[3];
  bind[3].length= &length[3];
  bind[3].error= &error[3];

  /* Bind the result buffers */
  if (mysql_stmt_bind_result(stmt, bind))
    {
      fprintf(stderr, " mysql_stmt_bind_result() failed\n");
      fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      exit(0);
    }

  for (j=0; j<3; j++) {
    /* Execute the SELECT query */
    if (mysql_stmt_execute(stmt))
      {
        fprintf(stderr, " mysql_stmt_execute(), failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      } else {

      /* Now buffer all results to client */
      if (mysql_stmt_store_result(stmt))
	{
	  fprintf(stderr, " mysql_stmt_store_result() failed\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	  exit(0);
	}

      /* Fetch all rows */
      row_count= 0;
      fprintf(stdout, "Fetching results ...\n");
      while (!mysql_stmt_fetch(stmt))
	{
	  row_count++;
	  fprintf(stdout, "  row %d\n", row_count);

	  /* column 1 */
	  fprintf(stdout, "   column1 (integer)  : ");
	  if (is_null[0])
	    fprintf(stdout, " NULL\n");
	  else
	    fprintf(stdout, " %d(%ld)\n", int_data, length[0]);

	  /* column 2 */
	  fprintf(stdout, "   column2 (string)   : ");
	  if (is_null[1])
	    fprintf(stdout, " NULL\n");
	  else
	    fprintf(stdout, " %s(%ld)\n", str_data, length[1]);

	  /* column 3 */
	  fprintf(stdout, "   column3 (smallint) : ");
	  if (is_null[2])
	    fprintf(stdout, " NULL\n");
	  else
	    fprintf(stdout, " %d(%ld)\n", small_data, length[2]);

	  /* column 4 */
	  fprintf(stdout, "   column4 (timestamp): ");
	  if (is_null[3])
	    fprintf(stdout, " NULL\n");
	  else
	    fprintf(stdout, " %04d-%02d-%02d %02d:%02d:%02d (%ld)\n",
		    ts.year, ts.month, ts.day,
		    ts.hour, ts.minute, ts.second,
		    length[3]);
	  fprintf(stdout, "\n");
	}

      /* Validate rows fetched */
      fprintf(stdout, " total rows fetched: %d\n", row_count);
      if (row_count != 2)
	{
	  fprintf(stderr, " MySQL failed to return all rows\n");
	  exit(0);
	}
    }
  }

  /* Free the prepared result metadata */
  puts("freeing metadata\n");
  mysql_free_result(prepare_meta_result);

  /* Close the statement */
  puts("closing statement\n");
  if (mysql_stmt_close(stmt))
    {
      fprintf(stderr, " failed while closing the statement\n");
      fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      exit(0);
    }

  printf("connection id: %ld\n", mysql_thread_id(mysql));
  puts("closing connection\n");
  mysql_close(mysql);

  return EXIT_SUCCESS;
}
