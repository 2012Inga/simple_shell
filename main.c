#include "main.h"

int main(void) {
    char *command = NULL;
    bool oneline = isatty(STDIN_FILENO);
    pid_t child;
    char *arg;

    while (1) {
        if (oneline) {
            printf("#shell27$ ");
        }

        command = custom_getline();
        if (command == NULL) {
            if (oneline) {
                printf("\n");
            }
            break;
        }

        if (strncmp(command, "exit", 4) == 0) {
            arg = strtok(command + 4, " \t");
            exit_arg(arg);
        } else {
            if (strncmp(command, "cd", 2) == 0) {
                _buildInCmd(command);
            } else {
                if ((child = fork()) == -1) {
                    perror("fork failed");
                    exit(EXIT_FAILURE);
                }

                if (child == 0) {
                    execute_command(command);
                    free(command);
                    exit(EXIT_SUCCESS);
                } else {
                    wait(NULL);
                }
            }
        }

        free(command);
    }

    return 0;
}
