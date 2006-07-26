#!/bin/sh
aclocal
autoheader
libtoolize --force
autoconf
automake --add-missing --copy
