#!/bin/sh
aclocal
libtoolize --force
autoconf
automake --add-missing --copy
