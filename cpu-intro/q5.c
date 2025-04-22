#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    int rc = fork();

    if (rc < 0) {
        perror("fork failed");
        exit(-1);
    } else if (rc == 0) {
        int r = 0;
        wait(NULL);
        for (int i = 0; i <= 1000; i++) r++;
        printf("r: %d\n", r);
    } else {
        wait(NULL);
        printf("parent finished\n");
    }
    return 0;
}