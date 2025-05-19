CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address,undefined
LDFLAGS = -fsanitize=address,undefined

libexclusive.a: exclusive.o
	ar rcs $@ $^

exclusive.o: exclusive.c exclusive.h
	$(CC) $(CFLAGS) -c $< -o $@

%: %.c
	$(CC) $(CFLAGS) $< -o $@
