#include "main.h"
int main(int argc, char *argv[])
{
    char *command = NULL;
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

       
        if ((child = fork()) == -1) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (child == 0) {
            execute_command(command);
            exit(argc > 1 ? atoi(argv[1]): 0); /* Use custom status if provided */
        } else {
            wait(NULL);
	    if (strcmp(command,"exit")==0){
	    break;
	    }
        }

        free(command);
    }

    return (0);
}
