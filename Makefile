CC = gcc
CFLAGS = -Wall -Wpedantic -Wrestrict -g

all:
	$(CC) $(CFLAGS) fastfib.c -o fastfib -lgmp
