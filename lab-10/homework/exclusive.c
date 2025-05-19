#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "exclusive.h"

#define MAX_PID_STR 16

void exclusive(char const* lock) {
    int fd;
    pid_t pid = getpid();
    char pid_str[MAX_PID_STR];
    char read_pid_str[MAX_PID_STR];
    struct stat statbuf;

    while (1) {
        fd = open(lock, O_CREAT | O_EXCL | O_WRONLY, 0644);
        if (fd >= 0) {
            break;
        }

        if (errno == EEXIST) {
            fd = open(lock, O_RDONLY);
            if (fd < 0) {
                usleep(100000);
                continue;
            }

            ssize_t n = read(fd, read_pid_str, MAX_PID_STR - 1);
            close(fd);
            if (n <= 0) {
                usleep(100000);
                continue;
            }
            read_pid_str[n] = '\0';

            pid_t other_pid = atoi(read_pid_str);
            if (other_pid <= 0) {
                usleep(100000);
                continue;
            }

            char proc_path[32];
            snprintf(proc_path, sizeof(proc_path), "/proc/%d", other_pid);

            if (stat(proc_path, &statbuf) == 0) {
                usleep(100000);
                continue;
            }

            continue;
        }

        perror("exclusive: open");
        exit(EXIT_FAILURE);
    }

    snprintf(pid_str, MAX_PID_STR, "%d", pid);
    if (write(fd, pid_str, strlen(pid_str)) < 0) {
        perror("exclusive: write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
}
