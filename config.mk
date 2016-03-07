#configure your build of uu

PREFIX=/usr/local

CC=cc

CFLAGS=-Wall -Wextra -pedantic -O2
LDFLAGS=-s

AWKTARGET=uu
CTARGET=fnuu

OBJS=fnuu.o deps/murmurhash/murmurhash.o
