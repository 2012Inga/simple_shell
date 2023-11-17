#include "main.h"

int main(void) {
    char *command = NULL;
    bool oneline = isatty(STDIN_FILENO);
    int status = 0;
    int argc;
    char *token;
char *argv[1024];
    
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
            
           
            argc = 0;

            token = strtok(command, " \t\n");
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
}
