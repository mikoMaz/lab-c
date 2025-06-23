#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <libgen.h>
#include <errno.h>
#include "hash.h"

#define TEMP_SUFFIX "---redoing"
#define REDO_DB ".redo"

void die(const char *msg) {
    perror(msg);
    exit(1);
}

int file_exists(const char *path) {
    struct stat st;
    return stat(path, &st) == 0;
}

char *get_basename_no_ext(const char *filename) {
    char *base = strdup(filename);
    if (!base)
        die("strdup");
    char *dot = strrchr(base, '.');
    if (dot && dot != base)
        *dot = '\0';
    return base;
}

void run_script(const char *target) {
    char script_name[512];
    snprintf(script_name, sizeof(script_name), "%s.do", target);
    if (!file_exists(script_name)) {
        fprintf(stderr, "No build script: %s\n", script_name);
        exit(1);
    }

    char *basename_no_ext = get_basename_no_ext(target);
    char temp_file[512];
    snprintf(temp_file, sizeof(temp_file), "%s%s", target, TEMP_SUFFIX);

    int fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
        die("open temp_file");

    if (dup2(fd, STDOUT_FILENO) < 0)
        die("dup2");
    close(fd);

    pid_t pid = fork();
    if (pid < 0)
        die("fork");
    if (pid == 0) {
        const char *old_path = getenv("PATH");
        char new_path[4096];
        if (old_path) {
            snprintf(new_path, sizeof(new_path), "./:%s", old_path);
        } else {
            snprintf(new_path, sizeof(new_path), "./");
        }
        setenv("PATH", new_path, 1);

        setenv("REDO_TARGET", target, 1);

        char script_path[512];
        if (strchr(script_name, '/') == NULL) {
            snprintf(script_path, sizeof(script_path), "./%s", script_name);
        } else {
            strncpy(script_path, script_name, sizeof(script_path));
            script_path[sizeof(script_path)-1] = '\0';
        }

        execlp("sh", "sh", "-e", script_path, target, basename_no_ext, temp_file, (char *)NULL);
        perror("execlp");
        exit(1);
    }

    int status;
    waitpid(pid, &status, 0);
    free(basename_no_ext);

    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        if (rename(temp_file, target) < 0)
            die("rename");
    } else {
        unlink(temp_file);
        exit(1);
    }
}

int is_target_up_to_date(const char *target, char **deps, int dep_count) {
    if (!file_exists(target))
        return 0;

    FILE *f = fopen(REDO_DB, "r");
    if (!f)
        return 0;

    char *line = NULL;
    size_t line_len = 0;
    int found_deps = 0;
    char (*saved_hashes)[256] = malloc(dep_count * sizeof(*saved_hashes));
    char (*dep_files)[256] = malloc(dep_count * sizeof(*dep_files));
    if (!saved_hashes || !dep_files) {
        if (saved_hashes) free(saved_hashes);
        if (dep_files) free(dep_files);
        fclose(f);
        die("malloc");
    }
    int dep_idx = 0;

    while (getline(&line, &line_len, f) != -1) {
        char file[256], hash_saved[256];
        if (sscanf(line, "%255s %255s", file, hash_saved) == 2) {
            for (int i = 0; i < dep_count; ++i) {
                if (strcmp(file, deps[i]) == 0 && dep_idx < dep_count) {
                    strncpy(dep_files[dep_idx], file, sizeof(dep_files[dep_idx]));
                    dep_files[dep_idx][sizeof(dep_files[dep_idx])-1] = '\0';
                    strncpy(saved_hashes[dep_idx], hash_saved, sizeof(saved_hashes[dep_idx]));
                    saved_hashes[dep_idx][sizeof(saved_hashes[dep_idx])-1] = '\0';
                    dep_idx++;
                    found_deps++;
                    break;
                }
            }
        }
    }
    free(line);
    fclose(f);

    if (found_deps != dep_count) {
        free(saved_hashes);
        free(dep_files);
        return 0;
    }

    for (int i = 0; i < dep_count; ++i) {
        if (!file_exists(dep_files[i])) {
            free(saved_hashes);
            free(dep_files);
            return 0;
        }

        char hash_now[65];
        if (hash_file(dep_files[i], hash_now) < 0) {
            free(saved_hashes);
            free(dep_files);
            return 0;
        }

        if (strcmp(hash_now, saved_hashes[i]) != 0) {
            free(saved_hashes);
            free(dep_files);
            return 0;
        }
    }

    free(saved_hashes);
    free(dep_files);
    return 1;
}

void update_redo_db(const char *target, char **deps, int dep_count) {
    FILE *f = fopen(REDO_DB, "r");
    char temp_file[512];
    snprintf(temp_file, sizeof(temp_file), "%s.tmp", REDO_DB);
    FILE *temp = fopen(temp_file, "w");
    if (!temp)
        die("fopen .redo.tmp");

    if (f) {
        char *line = NULL;
        size_t line_len = 0;
        while (getline(&line, &line_len, f) != -1) {
            char file[256], hash[256];
            if (sscanf(line, "%255s %255s", file, hash) == 2) {
                int is_dep = 0;
                for (int i = 0; i < dep_count; ++i) {
                    if (strcmp(file, deps[i]) == 0) {
                        is_dep = 1;
                        break;
                    }
                }
                if (!is_dep)
                    fprintf(temp, "%s %s\n", file, hash);
            }
        }
        free(line);
        fclose(f);
    }

    for (int i = 0; i < dep_count; ++i) {
        if (!file_exists(deps[i]))
            continue;
        char hash[65];
        if (hash_file(deps[i], hash) == 0) {
            fprintf(temp, "%s %s\n", deps[i], hash);
        }
    }

    fclose(temp);

    if (rename(temp_file, REDO_DB) < 0)
        die("rename .redo");
}

int main(int argc, char **argv) {
    char *prog = basename(argv[0]);

    if (strcmp(prog, "redo") == 0) {
        if (argc < 2) {
            fprintf(stderr, "Usage: redo <target>\n");
            return 1;
        }
        run_script(argv[1]);
    } else if (strcmp(prog, "redo-ifchange") == 0) {
        if (argc < 2) {
            fprintf(stderr, "Usage: redo-ifchange <dep>...\n");
            return 1;
        }

        const char *target = getenv("REDO_TARGET");
        if (!target) {
            fprintf(stderr, "REDO_TARGET not set!\n");
            return 1;
        }

        if (is_target_up_to_date(target, &argv[1], argc - 1)) {
            exit(1);
        } else {
            update_redo_db(target, &argv[1], argc - 1);
            exit(0);
        }
    } else {
        fprintf(stderr, "Unknown mode: %s\n", prog);
        return 1;
    }

    return 0;
}
