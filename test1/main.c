#include "main.h"

int main(void) {
    char *command = NULL;
    bool oneline = isatty(STDIN_FILENO);
    pid_t child;
    while (1) {
        if (oneline) {
            printf("#shell4.1$ ");
        }
        command = _getline();
        if (command == NULL) {
            if (oneline) {
                printf("\n");
            }
            break;
        }
	if (strcmp(command, "exit") == 0){
		free(command);
		break;
	}

	// Tokenize the command string into arguments
        char *token;
        char *argv[BUFFER_SIZE];
        int argc = 0;

        token = strtok(command, " \n");
        while (token != NULL) {
            argv[argc] = strdup(token);
            argc++;
            token = strtok(NULL, " \n");
        }

        argv[argc] = NULL; /* NULL-terminate the argument array */

        if (strcmp(argv[0], "cd") == 0) {
            _buildInCmd(argv);
            printf("cd :\n");
        } else {
            
            if ((child = fork()) == -1) {
                perror("fork failed");
                free(command);
                exit(EXIT_FAILURE);
            }

            if (child == 0) {
                execute_command(command);
                free(command);
                exit(0);
            } else {
                wait(NULL);
            }
        }

        // Free memory for the arguments
        for (int i = 0; i < argc; i++) {
            free(argv[i]);
        }

        free(command);
    }

    return 0;
}
