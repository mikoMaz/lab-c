CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address,undefined

calc: calc.c
	$(CC) $(CFLAGS) $< -o $@ -lm

%: %.c
	$(CC) $(CFLAGS) $< -o $@
