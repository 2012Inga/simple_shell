#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <errno.h>
extern char **environ;
#define BUFFER_SIZE 1024

char *_getline(void) {
    char *line = NULL;
    size_t line_size = BUFFER_SIZE;
    size_t line_length = 0;
    int ch;

    line = (char *)malloc(line_size);
    if (!line) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    while (1) {
        ch = getchar();
        if (ch == EOF) {
            free(line);
            return NULL; 
        } else if (ch == '\n') {
            line[line_length] = '\0';
            return line;
	} else {
            if (line_length >= line_size - 1) {
               
                line_size *= 2;
                char *new_line = (char *)realloc(line, line_size);
                if (!new_line) {
                    perror("Memory reallocation error");
                    free(line);
                    exit(EXIT_FAILURE);
                }
                line = new_line;
            }
            line[line_length++] = ch;
        }
    }}
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
            char *dir = strtok(path_copy, ":");

            while (dir != NULL) {
                char full_path[BUFFER_SIZE];
                snprintf(full_path, sizeof(full_path), "%s/%s", dir, argv[0]);
                if (access(full_path, X_OK) == 0) {
                    if (execve(full_path, argv, environ) == -1) {
                        perror("Command execution error");
                        exit(EXIT_FAILURE);
                    }
                }
                dir = strtok(NULL, ":");
            }

            
            perror("Command not found");
            exit(EXIT_FAILURE);
        }
    }
}
int main(void) {
    char *command = NULL;
    bool oneline = isatty(STDIN_FILENO);

    while (1) {
        if (oneline) {
            printf("#shell0.1.1$ ");
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
