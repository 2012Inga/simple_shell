#include "main.h"
void execute_command(char *command) {
    char *token;
    char *argv[BUFFER_SIZE];
    int argc = 0;

    token = strtok(command, " \n");
    while (token != NULL) {
        argv[argc] = token;
        argc++;
        token = strtok(NULL, " \n");
    }

    argv[argc] = NULL;


     if (strcmp(argv[0], "env") == 0) {
        char **env = environ;
        while (*env) {
            printf("%s\n", *env);
            env++;
        }
    } else {
        if (execvp(argv[0], argv) == -1) {
            char *path = getenv("PATH");
            char *path_copy = strdup(path);
            char *dir = strtok_custom(path_copy, ":");

            while (dir != NULL) {
                char full_path[BUFFER_SIZE];
                snprintf(full_path, sizeof(full_path), "%s/%s", dir, argv[0]);
                if (access(full_path, X_OK) == 0) {
                    if (execve(full_path, argv, environ) == -1) {
                        perror("Command execution error");
                        exit(EXIT_FAILURE);
                    }
                }
                dir = strtok_custom(NULL, ":");
            }


            perror("Command not found");
            exit(EXIT_FAILURE);
        }
    }
}
