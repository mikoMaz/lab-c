CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address,undefined

libmath.a: math.o
	ar rcs $@ $^

math.o: math.c math.h
	$(CC) $(CFLAGS) -c $< -o $@

###

c89: c89.c
	$(CC) $(CFLAGS) -std=c89 $< -o $@

guess_a_number: guess_a_number.c
	$(CC) $(CFLAGS) $< random.a -o $@

window: window.c
	$(CC) $(CFLAGS) $< -o $@ -Iraylib/include -Lraylib/lib -lraylib

%: %.c
	$(CC) $(CFLAGS) $< -o $@
