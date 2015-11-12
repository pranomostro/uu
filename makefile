#Makefile for uu.

PREFIX = /usr/local
TARGET = uu

CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -s -O3
LDFLAGS =
OFILES = fnuu.o murmurhash.o

all: ${TARGET}

${TARGET}: ${OFILES}
	${CC} ${LDFLAGS} ${OFILES} -o fn${TARGET}

fnuu.o: fnuu.c
	${CC} ${CFLAGS} -c $<

murmurhash.o: murmurhash.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -rf fn${TARGET} ${OFILES}

install: all
	mkdir -p ${PREFIX}/bin ${PREFIX}/share/man/man1
	cp fn${TARGET} ${PREFIX}/bin
	cp ${TARGET} ${PREFIX}/bin
	cp ${TARGET}.1 ${PREFIX}/share/man/man1
	chmod 755 ${PREFIX}/bin/fn${TARGET}
	chmod 755 ${PREFIX}/bin/${TARGET}
	chmod 644 ${PREFIX}/share/man/man1/${TARGET}.1

uninstall:
	rm -f ${PREFIX}/bin/fn${TARGET}
	rm -f ${PREFIX}/bin/${TARGET}
	rm -f ${PREFIX}/share/man/man1/${TARGET}.1
