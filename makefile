BINS=llwmuu ahashuu ihashuu
CC=gcc
CFLAGS=-Wall -s -O3 -funroll-loops

all: ${BINS}

%: %.c
	${CC} ${CFLAGS} $< -o $@

clean:
	rm -f ${BINS}
