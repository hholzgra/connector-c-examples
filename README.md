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

```sh
# first generate the configure file
./autogen.sh

# configure the build
./configure 

# build
make
```

### Run

Create a local `my.cnf` file with client connection information in the build directory:

```
[client]
host=db.example.org
user=tester
password=secret
database=test
```

With the access information in place you can run every example program without any
further parameters, e.g.:


```sh
$ ./mysql_store_result
Got a valid result set
```
