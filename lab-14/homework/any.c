#include "any.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int int_length(any_t any) {
    int x = *(int*)any.data;
    if (x == 0) return 1;
    int len = 0;
    if (x < 0) {
        len++;
        x = -x;
    }
    while (x > 0) {
        len++;
        x /= 10;
    }
    return len;
}

static void int_free(any_t any) {
    free(any.data);
}

static void int_print(any_t any) {
    printf("%d\n", *(int*)any.data);
}

static int str_length(any_t any) {
    return strlen((char*)any.data);
}

static void str_free(any_t any) {
    free(any.data);
}

static void str_print(any_t any) {
    printf("%s\n", (char*)any.data);
}

static any_vtable_t int_vtable = {
    .length = int_length,
    .free = int_free,
    .print = int_print
};

static any_vtable_t str_vtable = {
    .length = str_length,
    .free = str_free,
    .print = str_print
};

any_t any_from_int(int x) {
    any_t result;
    result.vtable = &int_vtable;
    result.data = malloc(sizeof(int));
    if (result.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    *(int*)result.data = x;
    return result;
}

any_t any_from_str(char const* s) {
    any_t result;
    result.vtable = &str_vtable;
    result.data = malloc(strlen(s) + 1);
    if (result.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strcpy((char*)result.data, s);
    return result;
}

int any_length(any_t any) {
    return any.vtable->length(any);
}

void any_free(any_t any) {
    any.vtable->free(any);
}

void any_print(any_t any) {
    any.vtable->print(any);
}
