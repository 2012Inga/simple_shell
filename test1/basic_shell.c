#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/**
 * main - Entry point for the custom shell program.
 *
 * Description:
 * This function represents the primary logic of a custom shell program.
 * It reads user input, processes it, and executes the specified commands.
 * The shell displays a prompt, reads the user's command, and executes it.
 * If the command doesn't exist, it prints an error message.
 *
 * Return: Always returns 0 to indicate successful execution.
 */

extern char **environ; /* Declaration for environ */

int main(void) {
    char *command = NULL;
    size_t n_char = 0;
    int status, i;
    bool oneline = isatty(STDIN_FILENO);
    pid_t child;

    while (1) {
        if (oneline) {
            printf("#shell27$ ");
        }
        if (getline(&command, &n_char, stdin) == EOF) {
            if (oneline) {
                printf("\n");
            }
            break;
        }

        /* Parse the command and arguments */
        char *token;
        char *argv[64]; /* Maximum number of arguments */

        int argc = 0;

        token = strtok(command, " \n"); /* Tokenize by space and newline */
        while (token != NULL) {
            argv[argc] = token;
            argc++;
            token = strtok(NULL, " \n");
        }

        argv[argc] = NULL; /* NULL-terminate the argument array */
	
	/* Implement the exit built-in command */
	if(strcmp(argv[0], "exit") == 0){
	   free(command);
	   exit(0);
	   }

	/* Implement the env built-in command */
	if (strcmp(argv[0], "env") == 0){
	    char **env = environ;
    	    while (*env) {
		printf("%s\n", *env);
    		env++;
	    }
	}	    

        /* Iterate through directories in PATH */
        char *path = getenv("PATH");
        char *path_copy = strdup(path);
        char *dir = strtok(path_copy, ":");

        while (dir != NULL) {
            char full_path[1024]; /* Adjust the size as needed */
            snprintf(full_path, sizeof(full_path), "%s/%s", dir, argv[0]);

            /* Check if the command exists in the directory */
            if (access(full_path, X_OK) == 0) {
                child = fork();
                if (child < 0) {
                    printf("fork failed\n");
                } else if (child == 0) {
                    if (execvp(full_path, argv) == -1) {
                        printf("%s: Command execution error\n", argv[0]);
                        exit(1);
                    }
                } else {
                    wait(&status);
                }
                break;
            }

            dir = strtok(NULL, ":");
        }

        free(path_copy);
    }

    free(command);
    return 0;
}
