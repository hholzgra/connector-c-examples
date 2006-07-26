#!/bin/sh
cp Makefile.base Makefile.am
echo -n "bin_PROGRAMS = " >> Makefile.am
for file in mysql*.c
do
  echo -n " "`basename $file .c` >> Makefile.am
done
aclocal
autoheader
libtoolize --force
autoconf
automake --add-missing --copy
