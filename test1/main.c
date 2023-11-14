#include "main.h"
#include "execute_command.h"

int main(void) {
    char *command = NULL;
    bool oneline = isatty(STDIN_FILENO);

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

        pid_t child;
        if ((child = fork()) == -1) {
            perror("fork failed");
	    free(command);
            exit(EXIT_FAILURE);
        }

        if (child == 0) {
            execute_single_command(command); /* Use execute_single_command */
	    free(command); /* Free the memory in the child process */
            exit(0);
        } else {
            wait(NULL);
	    if (strcmp(command, "exit") == 0){
	    break;
	    }
        }

        free(command); /* Free the memory in the parent process */
    }

    return 0;
}    
