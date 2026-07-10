#!/bin/sh
set -e

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

. ./iso.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom gameos.iso