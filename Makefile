# variables
CC=gcc
CFLAGS=-Wall -Werror
OUTPUT=$@

# targets
%: %.c
	$(CC) $(CFLAGS) $@.c -o $(OUTPUT)