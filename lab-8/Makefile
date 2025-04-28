CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address,undefined

chmod: chmod.c
	$(CC) $(CFLAGS) $< -o $@ -lm

%: %.c
	$(CC) $(CFLAGS) $< -o $@
