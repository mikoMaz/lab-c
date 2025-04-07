CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address,undefined

bst_demo: bst.c bst_demo.c bst.h
	$(CC) $(CFLAGS) bst.c bst_demo.c -o bst_demo

stack: stack.c
	$(CC) $(CFLAGS) stack.c -o stack

%: %.c
	$(CC) $(CFLAGS) $< -o $@
