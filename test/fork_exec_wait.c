#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int num_children = 5;

    for (int i = 0; i < num_children; i++) {
        pid_t child_pid = fork(); /* Create a child process */

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            /* This code runs in the child process */
            printf("Child %d executing ls -l /tmp:\n", i + 1);

            char *command = "ls";
            char *args[] = {command, "-l", "/tmp", NULL};

            if (execvp(command, args) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else {
            /* This code runs in the parent process */
            int status;
            waitpid(child_pid, &status, 0); /* Wait for the child to exit */
            printf("Child %d has exited.\n", i + 1);
        }
    }

    return 0;
}
