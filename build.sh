#!/bin/sh
set -e

#Support for command line options
for arg in "$@"
do
  echo $arg
done

. ./headers.sh

for PROJECT in $PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install)
done
