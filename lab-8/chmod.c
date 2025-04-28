#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>


enum action {
    ADD = '+',
    DEL = '-',
    SET = '='
};

enum permissions {
    USER_READ = S_IRUSR,
    USER_WRITE = S_IWUSR,
    USER_EXEC = S_IXUSR,
    GROUP_READ = S_IRGRP,
    GROUP_WRITE = S_IWGRP,
    GROUP_EXEC = S_IXGRP,
    OTHER_READ = S_IROTH,
    OTHER_WRITE = S_IWOTH,
    OTHER_EXEC = S_IXOTH
};

void parse(const char *decl, enum permissions *perm, enum action *action) {
    *perm = 0;
    if (strlen(decl) < 3) {
        fprintf(stderr, "Error: Invalid expression '%s'\n", decl);
        exit(1);
    }

    int apply_user = 0, apply_group = 0, apply_other = 0;
    if (strchr("ugoa", decl[0]) == NULL) {
        fprintf(stderr, "Error: Invalid target '%c' in expression '%s'\n", decl[0], decl);
        exit(1);
    }
    if (decl[0] == 'u') apply_user = 1;
    else if (decl[0] == 'g') apply_group = 1;
    else if (decl[0] == 'o') apply_other = 1;
    else if (decl[0] == 'a') apply_user = apply_group = apply_other = 1;

    // +, -, =
    if (strchr("+-=", decl[1]) == NULL) {
        fprintf(stderr, "Error: Invalid action '%c' in expression '%s'\n", decl[1], decl);
        exit(1);
    }
    *action = (enum action)decl[1];

    // r, w, x
    for (size_t i = 2; i < strlen(decl); i++) {
        if (decl[i] == 'r') {
            if (apply_user) *perm |= USER_READ;
            if (apply_group) *perm |= GROUP_READ;
            if (apply_other) *perm |= OTHER_READ;
        } else if (decl[i] == 'w') {
            if (apply_user) *perm |= USER_WRITE;
            if (apply_group) *perm |= GROUP_WRITE;
            if (apply_other) *perm |= OTHER_WRITE;
        } else if (decl[i] == 'x') {
            if (apply_user) *perm |= USER_EXEC;
            if (apply_group) *perm |= GROUP_EXEC;
            if (apply_other) *perm |= OTHER_EXEC;
        } else {
            fprintf(stderr, "Error: Invalid permission '%c' in expression '%s'\n", decl[i], decl);
            exit(1);
        }
    }
}

enum permissions apply(enum permissions old, enum permissions new, enum action how) {
    if (how == SET) {
        return new;
    } else if (how == ADD) {
        return old | new;
    } else {
        return old & ~new;
    }
}

enum permissions get(const char *path) {
    struct stat st;
    if (stat(path, &st) == -1) {
        fprintf(stderr, "Error: Cannot access '%s': %s\n", path, strerror(errno));
        exit(1);
    }
    if (!S_ISREG(st.st_mode) && !S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Error: '%s' is not a regular file or directory\n", path);
        exit(1);
    }
    return (enum permissions)(st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
}

void set(const char *file, enum permissions perm) {
    if (chmod(file, (mode_t)perm) == -1) {
        fprintf(stderr, "Error: Cannot set permissions for '%s': %s\n", file, strerror(errno));
        exit(1);
    }
}

void print(enum permissions perm) {
    printf(" ");
    printf("%c", (perm & USER_READ) ? 'r' : '-');
    printf("%c", (perm & USER_WRITE) ? 'w' : '-');
    printf("%c", (perm & USER_EXEC) ? 'x' : '-');
    printf("%c", (perm & GROUP_READ) ? 'r' : '-');
    printf("%c", (perm & GROUP_WRITE) ? 'w' : '-');
    printf("%c", (perm & GROUP_EXEC) ? 'x' : '-');
    printf("%c", (perm & OTHER_READ) ? 'r' : '-');
    printf("%c", (perm & OTHER_WRITE) ? 'w' : '-');
    printf("%c", (perm & OTHER_EXEC) ? 'x' : '-');
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <expression> <file1> [<file2> ...]\n", argv[0]);
        return 1;
    }

    enum permissions perm;
    enum action action;

    parse(argv[1], &perm, &action);

    for (int i = 2; i < argc; i++) {
        enum permissions old_perm = get(argv[i]);
        enum permissions new_perm = apply(old_perm, perm, action);
        set(argv[i], new_perm);
        printf("%s:", argv[i]);
        print(new_perm);
    }

    return 0;
}
