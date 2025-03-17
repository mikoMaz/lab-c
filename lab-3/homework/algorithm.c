/* algorithm.c */
#include "algorithm.h"

void swap_ints(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void swap(void *a, void *b, size_t size) {
    void *c = malloc(size);
    
    memcpy(c, a, size);
    memcpy(a, b, size);
    memcpy(b, c, size);

    free(c);
}
