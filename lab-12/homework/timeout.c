#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

void print_usage() {
    fprintf(stderr, "Usage: ./timeout <seconds> <program> [args...]\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        print_usage();
    }

    int timeout = atoi(argv[1]);
    if (timeout <= 0) {
        fprintf(stderr, "Error: Timeout must be a positive integer\n");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        execvp(argv[2], &argv[2]);
        perror("Exec failed");
        exit(1);
    }

    int status;
    pid_t result;
    int time_passed = 0;

    while (time_passed < timeout) {
        result = waitpid(pid, &status, WNOHANG);
        if (result == pid) {
            return WEXITSTATUS(status);
        }
        sleep(1);
        time_passed++;
    }

    if (kill(pid, SIGTERM) == -1) {
        perror("SIGTERM failed");
        exit(1);
    }

    time_passed = 0;
    while (time_passed < 5) {
        result = waitpid(pid, &status, WNOHANG);
        if (result == pid) {
            return WEXITSTATUS(status);
        }
        sleep(1);
        time_passed++;
    }

    if (kill(pid, SIGKILL) == -1) {
        perror("SIGKILL failed");
        exit(1);
    }

    waitpid(pid, &status, 0);
    fprintf(stderr, "Process terminated with SIGKILL\n");
    return 1;
}
