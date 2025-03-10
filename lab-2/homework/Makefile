CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address,undefined

c89: c89.c
	$(CC) $(CFLAGS) -std=c89 $< -o $@

guess_a_number: guess_a_number.c
	$(CC) $(CFLAGS) $< random.a -o $@

%: %.c
	$(CC) $(CFLAGS) $< -o $@
