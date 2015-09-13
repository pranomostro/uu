#Makefile for uu.

PREFIX = /usr/local
TARGET = uu

CC = gcc
CFLAGS = -Wall -std=c99 -pedantic
LIBS =
DEPSDIR = deps/murmurhash
OFILES = uu.o ${DEPSDIR}/murmurhash.o

all: ${TARGET}

${TARGET}: ${OFILES}
	${CC} ${LIBS} ${OFILES} -o ${TARGET}

uu.o: uu.c
	${CC} ${CFLAGS} -c $<

${DEPSDIR}/murmurhash.o: ${DEPSDIR}/murmurhash.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -rf ${TARGET} ${OFILES}

install: all
	mkdir -p ${PREFIX}/bin ${PREFIX}/share/man/man1
	cp ${TARGET} ${PREFIX}/bin
	cp ${TARGET}.1 ${PREFIX}/share/man/man1
	chmod 755 ${PREFIX}/bin/${TARGET}
	chmod 644 ${PREFIX}/share/man/man1/${TARGET}.1

uninstall:
	rm -f ${PREFIX}/bin/${TARGET}
	rm -f ${PREFIX}/share/man/man1/${TARGET}.1
