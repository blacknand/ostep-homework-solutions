#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int agrc, char **argv) {
    printf("Initial parent process pid: %d\n", (int) getpid());
    int x = 10;
    int* x_ptr = &x;
    int rc = fork();
    printf("Initial value of x: %d\n", *x_ptr);
    if (rc < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(0);
    } else if (rc == 0) {
        printf("Child process created, pid: %d\n", (int) getpid());
        printf("Value of x inside of child process: %d\n", *x_ptr); 
        *x_ptr = 15;
        printf("Updated value of x from child process: %d\n", *x_ptr); 
        sleep(1);
    } else {
        int wc = wait(NULL);
        printf("Parent access value of x: %d\n", *x_ptr);
        *x_ptr = 20;
        printf("Updated value of x from parent process: %d\n", *x_ptr);
    }
    return 0;
}