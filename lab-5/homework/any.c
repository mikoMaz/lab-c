#include "any.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

any_t any_from_int(int x) {
    any_t result;
    result.type = ANY_INT;
    result.value.i = x;
    return result;
}

any_t any_from_str(char const* s) {
    any_t result;
    result.type = ANY_STR;
    result.value.s = strdup(s);
    return result;
}

any_t* any_add(any_t *target, any_t rhs) {
    if (target->type == ANY_INT && rhs.type == ANY_INT) {
        target->value.i += rhs.value.i;
    } else if (target->type == ANY_STR && rhs.type == ANY_STR) {
        size_t len1 = strlen(target->value.s);
        size_t len2 = strlen(rhs.value.s);
        char* new_str = malloc(len1 + len2 + 1);
        strcpy(new_str, target->value.s);
        strcat(new_str, rhs.value.s);
        free(target->value.s);
        target->value.s = new_str;
    } else if (target->type == ANY_STR && rhs.type == ANY_INT) {
        char num_str[32];
        snprintf(num_str, sizeof(num_str), "%ld", rhs.value.i);
        size_t len1 = strlen(target->value.s);
        size_t len2 = strlen(num_str);
        char* new_str = malloc(len1 + len2 + 1);
        strcpy(new_str, target->value.s);
        strcat(new_str, num_str);
        free(target->value.s);
        target->value.s = new_str;
    } else if (target->type == ANY_INT && rhs.type == ANY_STR) {
        char num_str[32];
        snprintf(num_str, sizeof(num_str), "%ld", target->value.i);
        size_t len2 = strlen(rhs.value.s);
        char* new_str = malloc(strlen(num_str) + len2 + 1);
        strcpy(new_str, num_str);
        strcat(new_str, rhs.value.s);
        target->type = ANY_STR;
        target->value.s = new_str;
    }
    return target;
}

any_t* any_mul(any_t *target, any_t rhs) {
    if (target->type == ANY_INT && rhs.type == ANY_INT) {
        target->value.i *= rhs.value.i;
    } else if (target->type == ANY_STR && rhs.type == ANY_STR) {
        size_t len1 = strlen(target->value.s);
        size_t len2 = strlen(rhs.value.s);
        char* new_str = malloc(len1 + len2 + 1);
        strcpy(new_str, target->value.s);
        strcat(new_str, rhs.value.s);
        free(target->value.s);
        target->value.s = new_str;
    } else if (target->type == ANY_STR && rhs.type == ANY_INT) {
        if (rhs.value.i <= 0) return target;
        size_t len = strlen(target->value.s);
        size_t new_len = len * rhs.value.i;
        char* new_str = malloc(new_len + 1);
        new_str[0] = '\0';
        for (int64_t i = 0; i < rhs.value.i; i++) {
            strcat(new_str, target->value.s);
        }
        free(target->value.s);
        target->value.s = new_str;
    } else if (target->type == ANY_INT && rhs.type == ANY_STR) {
        if (target->value.i <= 0) {
            target->type = ANY_STR;
            target->value.s = strdup("");
            return target;
        }
        size_t len = strlen(rhs.value.s);
        size_t new_len = len * target->value.i;
        char* new_str = malloc(new_len + 1);
        new_str[0] = '\0';
        for (int64_t i = 0; i < target->value.i; i++) {
            strcat(new_str, rhs.value.s);
        }
        target->type = ANY_STR;
        target->value.s = new_str;
    }
    return target;
}

void any_free(any_t a) {
    if (a.type == ANY_STR) {
        free(a.value.s);
    }
}

void any_print(any_t a) {
    if (a.type == ANY_INT) {
        printf("%ld\n", a.value.i);
    } else if (a.type == ANY_STR) {
        printf("%s\n", a.value.s);
    }
}
