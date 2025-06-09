#ifndef ANY_H
#define ANY_H

typedef struct any any_t;

typedef struct {
    int (*length)(any_t);
    void (*free)(any_t);
    void (*print)(any_t);
} any_vtable_t;

struct any {
    any_vtable_t* vtable;
    void* data;
};

any_t any_from_int(int x);
any_t any_from_str(char const* s);

int any_length(any_t any);
void any_free(any_t any);
void any_print(any_t any);

#endif
