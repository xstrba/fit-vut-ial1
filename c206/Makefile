
PRJ=c206
#
PROGS=$(PRJ)-test $(PRJ)-advanced-test
CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -lm

all: $(PROGS)

advanced: $(PRJ)-advanced-test

$(PRJ)-test: $(PRJ).c $(PRJ)-test.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-test.c

clean:
	rm -f *.o *.out $(PROGS)

$(PRJ)-advanced-test: $(PRJ).c $(PRJ)-advanced-test.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-advanced-test.c