#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char** argv) {
    pid_t rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed");
        exit(-1);
    } else if (rc == 0) {
        close(STDOUT_FILENO);
        printf("printing otuput...\n");
    } else {
        printf("lalalala\n");
        wait(NULL);
    }

    return 0;
}