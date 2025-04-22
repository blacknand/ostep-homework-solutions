#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    pid_t rc = fork(), stat;

    if (rc < 0) {
        perror("fork failed");
        exit(-1);
    } else if (rc == 0) {
        int r = 0;
        for (int i = 0; i <= 1000; i++) r++;
        printf("r: %d\n", r);
    } else {
        waitpid(rc, &stat, 0);    // will not wait for child process
        // wait(NULL);
        printf("parent finished\n");
    }
    return 0;
}