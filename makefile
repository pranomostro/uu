BINS=bhashuu
CC=gcc
CFLAGS=-Wall -Wextra -O3 -s

all: bhashuu

bhashuu: bhashuu.c deps/murmurhash/murmurhash.c deps/murmurhash/murmurhash.h
	${CC} ${CFLAGS} bhashuu.c deps/murmurhash/murmurhash.c -o bhashuu
clean:
	rm -f ${BINS}
