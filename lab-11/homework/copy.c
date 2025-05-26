#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>

#define MiB (1024 * 1024)

static unsigned ln = 1;

void Line(int l) {
    int m = l - ln;
    ln = l;
    if (m < 0) {
        printf("\r\33[%dA", -m);
    } else {
        putchar('\r');
        while (m-- > 0) putchar('\n');
    }
}

struct copy_args {
    char const *from, *to;
    size_t howmuch;
    int line;
};

void* copy(void *arg) {
    struct copy_args *args = (struct copy_args *)arg;
    int src = open(args->from, O_RDONLY);
    int dst = open(args->to, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    assert(src >= 0);
    assert(dst >= 0);

    for (size_t i = 0; i < args->howmuch; ++i) {
        char c;
        read(src, &c, sizeof(c));
        write(dst, &c, sizeof(c));
        Line(args->line);
        printf("%zu: %s -> %s: %2zu%%", pthread_self(), args->from, args->to, i * 100 / args->howmuch);
        fflush(stdout);
    }

    close(src);
    close(dst);
    return NULL;
}

int main() {
    pthread_t thread;
    size_t line = 1;

    struct copy_args args[] = {
        { "/dev/random", "output1", 1 * MiB },
        { "/dev/random", "output2", 0.7 * MiB },
    };

    pthread_t threads[sizeof(args) / sizeof(*args)] = {};

    for (size_t i = 0; i < sizeof(args) / sizeof(*args); ++i) {
        args[i].line = line++;
#if defined(SEQUENTIAL)
        copy(&args[i]);
#else
        pthread_create(&threads[i], NULL, copy, &args[i]);
#endif
    }

#if !defined(SEQUENTIAL)
    for (size_t i = 0; i < sizeof(threads) / sizeof(*threads); ++i) {
        pthread_join(threads[i], NULL);
    }
#endif

    Line(line);
    fflush(stdout);
    return 0;
}
