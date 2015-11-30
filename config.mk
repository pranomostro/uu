#configure your build of uu

PREFIX=/usr/local

CC=gcc

CFLAGS=-Wall -Wextra -std=c99 -pedantic -O2
LDFLAGS=-s

AWKTARGET=uu
CTARGET=fnuu

OBJS=fnuu.o deps/murmurhash/murmurhash.o
