#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    int fd = open("q2.c_output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork_failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("Accessing fire descriptor from child process (%d): %d\n", (int) getpid(), fd);
        char msg[] = "Writing from child proecss\n";
        ssize_t w_op = write(fd, msg, sizeof(msg) / sizeof(msg[0]));
    } else {
        printf("Accessing fire descriptor from parent process (%d): %d\n", (int) getpid(), fd);
        char msg[] = "Writing from parent process\n";
        ssize_t w_op = write(fd, msg, sizeof(msg) / sizeof(msg[0]));
    }
    return 0;
}