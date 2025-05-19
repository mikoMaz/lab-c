CC = gcc
CFLAGS = -Wall -Wextra

parallel: parallel.c
	$(CC) $(CFLAGS) $< -o $@ -lm

%: %.c
	$(CC) $(CFLAGS) $< -o $@
