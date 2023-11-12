#include "main.h"
/**
 * Change the current working directory and update the PWD environment variable.
 *
 * @param directory The directory to change to.
 * @return 0 on success, -1 on failure.
 */
int change_directory(const char *directory) {
	char current_directory[BUFFER_SIZE];

	if (directory == NULL) {
	    directory = getenv("HOME");
    	    if (directory == NULL) {
		fprintf(stderr, "Error: HOME environment variable not set.\n");
		return -1;
	    }
	}
	
	if (chdir(directory) == -1) {
	    perror("Error changing directory");
	    return -1;
	}

	if (getcwd(current_directory, sizeof(current_directory)) == NULL) {
	    perror("Error getting current working directory");
    	    return -1;
	}

	/* Update the PWD environment variable */
	if (set_env_variable("PWD", CURRENT_DIRECTORY) == -1) {
	    fprintf(stderr, "Error updating PWD environment variable.\n");
	    return -1;
	}
	
	return 0;
}


/* Declaration of strtok_custom */
char *strtok_custom(char *str, const char *delim);

/**
 * Execute a shell command.
 *
 * This function takes a command string as input, tokenizes it into arguments,
 * and attempts to execute the command string using execv. If the command execution 
 * fails, it iterates through directories in the PATH environment variable to 
 * find and execute the command. If the command is "env," it prints the environment variables.
 *
 * @param command The command string to be executed.
 */

void execute_command(char *command) {
    char *token;
    char *argv[BUFFER_SIZE];
    int argc = 0;

    /* Check if the command is "cd" */
    if (argc == 1 || strcmp(argv[1], "~") == 0 || strcmp(argv[1], "$HOME") == 0) {
	    /* Change to the home directory */
	    if (change_directory(NULL) == -1) {
		fprintf(stderr, "Error changing to the home directory.\n");
	    }
    } else if (strcmp(argv[1], "-") == 0) {
	/* Change to the previous directory */
	char * previous_directory = getenv("OLDPWD");
	if (previous_directory == NULL) {
	    fprintf(stderr, "Error changing to the previous directory.\n");
	}
    }
} else {
    /* Change to the specified directory */
    if (change_directory(argv[1]) == -1) {
	fprintf(stderr, "Error changing to the specified firectory.\n");
    }
}

    
    /* Tokenize the command string into arguments */
    token = strtok(command, " \n");
    while (token != NULL) {
        argv[argc] = token;
        argc++;
        token = strtok(NULL, " \n");
    }

    argv[argc] = NULL; /* NULL-terminate the argument array */

	/* Check if the command is "env" */
     if (strcmp(argv[0], "env") == 0) {
        char **env = environ;
        while (*env) {
            printf("%s\n", *env);
            env++;
        }
    } else {
	    /* Attempt to execute the command using execvp */
        if (execvp(argv[0], argv) == -1) {
            char *path = getenv("PATH");
            char *path_copy = strdup(path);
            char *dir = strtok_custom(path_copy, ":");
<<<<<<< HEAD
	    /* Iterate through directories in PATH to find and execute the command*/	
=======

>>>>>>> feb65a97a4bd87ef681d7d9808b772660b0017c1
            while (dir != NULL) {
                char full_path[BUFFER_SIZE];
                snprintf(full_path, sizeof(full_path), "%s/%s", dir, argv[0]);

		/* Check if the command exists in the directory */
                if (access(full_path, X_OK) == 0) {
			/* Execute the command*/
                    if (execve(full_path, argv, environ) == -1) {
                        perror("Command execution error");
			free(path_copy);
			free(argv[0]); /* Free memory for each argument */
                        exit(EXIT_FAILURE);
                    }
                }
                dir = strtok_custom(NULL, ":");
            }

	    free(path_copy); /* Free the allocated memory for path_copy */
    	    free(argv[0]); /* Freememory for the command */		    
            perror("Command not found");
            exit(EXIT_FAILURE);
        }
    }
/* Free memory for the arguments */
     for (int i = 0; i < argc; i++) {
	     free(argv[i]);
     }
}
