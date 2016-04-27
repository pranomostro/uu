#configure your build of uu

PREFIX=/usr/local

CC=cc

CFLAGS=-Wall -Wextra -pedantic -O2 -s

AWKTARGET=uu
BIN=fnuu bauu

OBJ=fnuu.o bauu.o nal.o deps/murmurhash/murmurhash.o
