# connector-c-examples

A collection of MySQL/MariaDB C API examples

Disclaimer: these are my private example files, they are *not* official MySQL documents
and are not supported by MySQL AB in any way

## How to build

### Prequisites

This project uses autoconf, automake and libtool for its build system.

It also obviously depends on a MariaDB (or MySQL) client library, and the necessary header files, being installed.

E.g. for Ubuntu 18.04LTS ("bionic") the following minimum packages need to be installed:

```sh
sudo apt-get install gcc make autoconf automake libtool libmariadb-dev zlib1g-dev libssl-dev
```

### Build

For now the database host, user name and password are compiled into the example binaries. To override the defaults ("localhost", user "root" without password) you need to pass in different values at the configuration step:

```sh
# first generate the configure file
./autogen.sh

# configure the build
MYSQL_HOST=db.example.org MYSQL_USER=tester MYSQL_PWD=secret ./configure 

# build
make
```

### Run

After `make` has finished successfully, you can run any of the result binaries without any extra parameters, e.g:

```sh
$ ./mysql_store_result
Got a valid result set
```
