CC=gcc
CFLAGS=-I.

test: test.o
	$(CC) -o test test.o
test.o: flash_led.c
	$(CC) -c -o test.o flash_led.c

.PHONY: clean
clean:
	rm -f test.o test