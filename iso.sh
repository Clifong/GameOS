#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/gameos.kernel isodir/boot/gameos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "gameos" {
	multiboot /boot/gameos.kernel
}
EOF
grub-mkrescue -o gameos.iso isodir
