PREFIX=/usr/local

CC=cc

CFLAGS=-Wall -Wextra -std=c99 -pedantic -O2
LDFLAGS=-s

NBT=uu
BT=fnuu bauu
NBO=nal.o reallocarray.o murmurhash.o

MAN=uu.1
CONF=config.h config.mk
OBJ=$(BT:=.o) $(NBO)
BIN=$(NBT) $(BT)
