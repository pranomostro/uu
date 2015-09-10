BINS=bhashuu
CC=gcc
CFLAGS=-Wall -Wextra -s -O3

all: ${BINS}

%: %.c
	${CC} ${CFLAGS} $< -o $@

clean:
	rm -f ${BINS}
