#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

struct test {
    int8_t a;
    int8_t b;
    int8_t c;
    int8_t d;
    int64_t e;
    int64_t f;
};

struct test2 {
    int64_t e;
    int64_t f;
    int8_t a;
    int8_t b;
    int8_t c;
    int8_t d;
};

struct test3 {
    int8_t a;
    int64_t e;
    int8_t b;
    int64_t f;
    int8_t c;
    int8_t d;
};

int main() {
    printf("Rozmiar struktury test: %zu bajtów\n", sizeof(struct test));
    printf("a: %zu\n", offsetof(struct test, a));
    printf("b: %zu\n", offsetof(struct test, b));
    printf("c: %zu\n", offsetof(struct test, c));
    printf("d: %zu\n", offsetof(struct test, d));
    printf("e: %zu\n", offsetof(struct test, e));
    printf("f: %zu\n", offsetof(struct test, f));
    printf("\n");

    printf("Rozmiar struktury test2: %zu bajtów\n", sizeof(struct test2));
    printf("e: %zu\n", offsetof(struct test2, e));
    printf("f: %zu\n", offsetof(struct test2, f));
    printf("a: %zu\n", offsetof(struct test2, a));
    printf("b: %zu\n", offsetof(struct test2, b));
    printf("c: %zu\n", offsetof(struct test2, c));
    printf("d: %zu\n", offsetof(struct test2, d));
    printf("\n");

    printf("Rozmiar struktury test3: %zu bajtów\n", sizeof(struct test3));
    printf("a: %zu\n", offsetof(struct test3, a));
    printf("e: %zu\n", offsetof(struct test3, e));
    printf("b: %zu\n", offsetof(struct test3, b));
    printf("f: %zu\n", offsetof(struct test3, f));
    printf("c: %zu\n", offsetof(struct test3, c));
    printf("d: %zu\n", offsetof(struct test3, d));

    return 0;
}
