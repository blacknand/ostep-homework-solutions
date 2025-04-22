#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    char line[256];
    int i;
    int op = -1;
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("Enter exec() function:\n");
        if (fgets(line, sizeof(line), stdin)) {
            printf("Recieved input: %s\n", line);
            if (1 == sscanf(line, "%d", &i)) {
                int op = (int) i;
            }
        }

        if (op != -1) {
            char* argl[] = {"ls", "-l", NULL};
            char* envp[] = {"HOME=/custom/home", "PATH=/bin:/usr/bin", NULL};
            switch (op) {
                case 1:
                    execv("/ls/bin", argl);
                    break;
                case 2:
                    execl("/ls/bin", "ls", "-l", NULL);
                    break;
                case 3:
                    execle("/ls/bin", "ls", "-l", NULL, envp);
                    break;
                case 4:
                    execlp("ls", "-l", NULL);
                    break;
                case 5:
                    execvp("ls", argl);
                    break;
            }
        }
    } else {
        wait(NULL);
        printf("This should not execute\n");
    }
}