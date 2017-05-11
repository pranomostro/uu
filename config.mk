PREFIX=/usr/local

CC=cc

CFLAGS=-Wall -Wextra -std=c99 -pedantic -O2
LDFLAGS=-s

NBT=uu
BT=fnuu bauu
NBO=nal.o reallocarray.o murmurhash.o

BIN=$(NBT) $(BT)
MAN=$(NBT:=.1)
OBJ=$(BT:=.o) $(NBO)
CONF=config.h config.mk
