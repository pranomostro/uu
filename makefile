BINS=bhashuu
CC=gcc
CFLAGS=-Wall -Wextra -g

all: ${BINS}

%: %.c
	${CC} ${CFLAGS} $< -o $@

clean:
	rm -f ${BINS}
