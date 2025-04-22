#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "failed\n");
        exit(-1);
    } else if (rc == 0) {
        printf("Child process created\n");
    } else {
        sleep(1);
        printf("Parent process\n");
    }
    return 0;
}