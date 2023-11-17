#include "main.h"

int main(void) {
    char *command = NULL;
    bool oneline = isatty(STDIN_FILENO);
    int status = 0;

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
            char *arg = strtok(command + 4, " \t");
            exit_arg(arg);
        } else {
            
            char *argv[1024];  // Adjust the size as needed
            int argc = 0;

            // Tokenize the command into arguments
            char *token = strtok(command, " \t\n");
            while (token != NULL) {
                argv[argc++] = token;
                token = strtok(NULL, " \t\n");
            }

           
            argv[argc] = NULL;

            
            status = handle_separator(argv, argc);

            
            free(command);
        }
    }

    return status;  
