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
        command = _getline();
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
            _buildInCmd(command);
            if ((child = fork()) == -1) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }

            if (child == 0) {
                execute_command(command);
            } else {
                wait(NULL);
            }
        }

        free(command);
    }

    return 0;
}
