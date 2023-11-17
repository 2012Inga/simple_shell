#include "main.h"


int main(void) {
    char *command = NULL;
    char *arg = NULL;
    char *env_var = NULL;
    char *variable;
    char *value;
    char *command_copy;
    bool oneline = isatty(STDIN_FILENO);
    pid_t child;

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

        command_copy = strdup(command);
        env_var = strtok(command_copy, " \t");
        if (strncmp(env_var, "setenv", 6) == 0) {
            variable = strtok(NULL, " \t");
            value = strtok(NULL, " \t");
            set_env_variable(variable, value);
        } else if (strncmp(env_var, "unsetenv", 8) == 0) {
            variable = strtok(NULL, " \t");
            unset_env_variable(variable);
        } else {
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
                        exit(EXIT_SUCCESS);
                    } else {
                        wait(NULL);
                    }
                }
            }
        }
        free(command_copy);
        free(command);
    }

    return 0;
}
