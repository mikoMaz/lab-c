#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <libgen.h>

#define MAX_LINE 1024
#define MAX_ARGS 128

char *replace_token(const char *src, const char *pattern, const char *replacement) {
    char *result = malloc(strlen(src) * 2 + 1);
    char *insert_point = result;
    const char *tmp = src;
    size_t pattern_len = strlen(pattern);
    size_t repl_len = strlen(replacement);

    while ((tmp = strstr(tmp, pattern))) {
        size_t len = tmp - src;
        strncpy(insert_point, src, len);
        insert_point += len;
        strncpy(insert_point, replacement, repl_len);
        insert_point += repl_len;
        tmp += pattern_len;
        src = tmp;
    }
    strcpy(insert_point, src);
    return result;
}

char *remove_extension(const char *filename) {
    char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) return strdup(filename);
    size_t len = dot - filename;
    char *result = malloc(len + 1);
    strncpy(result, filename, len);
    result[len] = '\0';
    return result;
}

char *build_command(char **argv, const char *line) {
    char *cmd = strdup("");
    char *base = strdup(basename((char *)line));
    char *dir = strdup(dirname(strdup(line)));
    char *noext = remove_extension(base);

    for (int i = 1; argv[i]; i++) {
        char *part = replace_token(argv[i], "{}", line);
        char *tmp = replace_token(part, "{.}", noext);
        free(part);
        part = replace_token(tmp, "{/}", base);
        free(tmp);
        tmp = replace_token(part, "{//}", dir);
        free(part);
        cmd = realloc(cmd, strlen(cmd) + strlen(tmp) + 2);
        strcat(cmd, tmp);
        strcat(cmd, " ");
        free(tmp);
    }

    free(base);
    free(dir);
    free(noext);
    return cmd;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
        return 1;
    }

    char line[MAX_LINE];
    pid_t children[1024];
    int count = 0;

    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;
        char *cmd = build_command(argv, line);
        pid_t pid = fork();
        if (pid == 0) {
            execl("/bin/sh", "sh", "-c", cmd, (char *)NULL);
            perror("execl");
            exit(1);
        } else if (pid > 0) {
            children[count++] = pid;
        } else {
            perror("fork");
        }
        free(cmd);
    }

    for (int i = 0; i < count; i++) {
        waitpid(children[i], NULL, 0);
    }

    return 0;
}
