#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    int p1[2], p2[2];
    char* msg1 = "hello from child 1";
    char* msg2 = "hello from child 2";
    char* inbuf1[strlen(msg2) + 1];
    char* inbuf2[strlen(msg1) + 1];
    pid_t rc1, rc2;

    if (pipe(p1) < 0 || pipe(p2) < 0) {
        fprintf(stderr, "pipe failed\n");
        exit(-1);
    }

    rc1 = fork();
    if (rc1 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc1 == 0) {
        close(p1[0]);       // Child 1 doesn't read from pipe 1
        close(p2[1]);       // Child 2 doesn't write to pipe 2

        write(p1[1], msg1, strlen(msg1));
        close(p1[1]);

        ssize_t n = read(p2[0], inbuf1, strlen(msg2));
        if (n > 0) {
            inbuf1[n] = '\0';
            printf("Child 1 recieved: %s\n", inbuf1);
        }

        close(p2[0]);
        exit(0);
    }

    rc2 = fork();
    if (rc2 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(-1);
    } else if (rc2 == 0) {
        close(p2[0]);
        close(p1[1]);

        write(p2[1], msg2, strlen(msg2));
        close(p2[1]);

        ssize_t n = read(p1[0], inbuf2, strlen(msg1));
        if (n > 0) {
            inbuf2[n] = '\0';
            printf("Child 2 recieved: %s\n", inbuf2);
        }

        close(p2[0]);
        exit(0);
    }

    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);

    waitpid(rc1, NULL, 0);
    waitpid(rc2, NULL, 0);

    printf("parent process terminated\n");

    return 0;
}