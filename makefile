BINS=llwmuu ahashuu ihashuu
CC=gcc
CFLAGS=-Wall -g

all: ${BINS}

%: %.c
	${CC} ${CFLAGS} $< -o $@

clean:
	rm -f ${BINS}
