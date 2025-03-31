#ifndef ANY_H
#define ANY_H

#include <stdint.h>

typedef enum {
    ANY_INT,
    ANY_STR
} any_type_t;

typedef struct any {
    any_type_t type;
    union {
        int64_t i;
        char* s;
    } value;
} any_t;

any_t any_from_int(int x);
any_t any_from_str(char const* s);
any_t* any_add(any_t *target, any_t rhs);
any_t* any_mul(any_t *target, any_t rhs);
void any_free(any_t a);
void any_print(any_t a);

#endif
