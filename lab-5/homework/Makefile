CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address,undefined
LDFLAGS = -fsanitize=address,undefined

libany.a: any.o
	ar rcs $@ $^

any.o: any.c any.h
	$(CC) $(CFLAGS) -c $< -o $@

q_sqrt: q_sqrt.c
	$(CC) $(CFLAGS) $< -o $@

struct_size: struct_size.c
	$(CC) $(CFLAGS) $< -o $@

test: test.o libany.a
	$(CC) $(LDFLAGS) test.o -L. -lany -o test

test.o: test.c any.h
	$(CC) $(CFLAGS) -c $< -o $@

%: %.c
	$(CC) $(CFLAGS) $< -o $@
