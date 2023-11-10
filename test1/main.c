#include "main.h"

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
		break;
	}

        pid_t child;
        if ((child = fork()) == -1) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (child == 0) {
            execute_command(command);
            exit(0);
        } else {
            wait(NULL);
	    if (command == "exit"){
	    break;
	    }
        }

        free(command);
    }

    return 0;
}    
