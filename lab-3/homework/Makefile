CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address,undefined

libalgorithm.a: algorithm.o
	ar rcs $@ $^

algorithm.o: algorithm.c algorithm.h
	$(CC) $(CFLAGS) -c $< -o $@

calc: calc.c
	$(CC) $(CFLAGS) $< -o $@ -lm

%: %.c
	$(CC) $(CFLAGS) $< -o $@
