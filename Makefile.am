ACLOCAL_AMFLAGS = -I m4

AM_CFLAGS = @MYSQL_CFLAGS@ -Wall -Werror -Wno-unused-but-set-variable

LIBS = @MYSQL_LIBS@

bin_PROGRAMS =
bin_PROGRAMS += mysql_change_user
bin_PROGRAMS += mysql_character_set_name
bin_PROGRAMS += mysql_close
bin_PROGRAMS += mysql_dump_debug_info
bin_PROGRAMS += mysql_data_seek
bin_PROGRAMS += mysql_errno
bin_PROGRAMS += mysql_error
bin_PROGRAMS += mysql_fetch_field
bin_PROGRAMS += mysql_fetch_field_direct
bin_PROGRAMS += mysql_fetch_fields
bin_PROGRAMS += mysql_fetch_lengths
bin_PROGRAMS += mysql_fetch_row
bin_PROGRAMS += mysql_field_count
bin_PROGRAMS += mysql_free_result
bin_PROGRAMS += mysql_get_client_info
bin_PROGRAMS += mysql_get_client_version
bin_PROGRAMS += mysql_get_host_info
bin_PROGRAMS += mysql_get_proto_info
bin_PROGRAMS += mysql_get_server_info
bin_PROGRAMS += mysql_hex_string
bin_PROGRAMS += mysql_info
bin_PROGRAMS += mysql_init
bin_PROGRAMS += mysql_kill
bin_PROGRAMS += mysql_list_dbs
bin_PROGRAMS += mysql_list_fields
bin_PROGRAMS += mysql_list_processes
bin_PROGRAMS += mysql_list_tables
bin_PROGRAMS += mysql_num_fields
bin_PROGRAMS += mysql_num_rows
bin_PROGRAMS += mysql_options
bin_PROGRAMS += mysql_ping
bin_PROGRAMS += mysql_query
bin_PROGRAMS += mysql_real_connect
bin_PROGRAMS += mysql_real_escape_string
bin_PROGRAMS += mysql_real_query
bin_PROGRAMS += mysql_select_db
bin_PROGRAMS += mysql_set_local_infile_handler
bin_PROGRAMS += mysql_set_server_option
bin_PROGRAMS += mysql_shutdown
bin_PROGRAMS += mysql_sqlstate
bin_PROGRAMS += mysql_ssl_set
bin_PROGRAMS += mysql_stat
bin_PROGRAMS += mysql_stmt_bind_result
bin_PROGRAMS += mysql_stmt_close
bin_PROGRAMS += mysql_stmt_execute
bin_PROGRAMS += mysql_stmt_field_count
bin_PROGRAMS += mysql_stmt_free_result
bin_PROGRAMS += mysql_stmt_init
bin_PROGRAMS += mysql_stmt_prepare
bin_PROGRAMS += mysql_store_result
bin_PROGRAMS += mysql_thread_id
bin_PROGRAMS += mysql_use_result

# added in MySQL 4.1
if HAVE_MYSQL_GET_SERVER_VERSION
bin_PROGRAMS += mysql_get_server_version
endif

# TODO deprecated, removinde since when?
if HAVE_MYSQL_CREATE_DB
bin_PROGRAMS += mysql_create_db
endif

if HAVE_MARIADB_GET_INFOV
bin_PROGRAMS += mariadb_get_infov
endif HAVE_MARIADB_GET_INFOV
