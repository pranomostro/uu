BINS=llwmuu ahashuu ihashuu bhashuu
CC=gcc
CFLAGS=-Wall -s

all: ${BINS}

%: %.c
	${CC} ${CFLAGS} $< -o $@

clean:
	rm -f ${BINS}
