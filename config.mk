#configure your build of uu

PREFIX=/usr/local

CC=cc

CFLAGS=-Wall -Wextra -pedantic -O2
LDFLAGS=-s

AWKTARGET=uu
BIN=fnuu bauu

OBJ=fnuu.o bauu.o deps/murmurhash/murmurhash.o
