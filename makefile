BINS=bhashuu
CC=gcc
CFLAGS=-Wall -Wextra -O3 -s

all: ${BINS}

%: %.c
	${CC} ${CFLAGS} $< -o $@

clean:
	rm -f ${BINS}
