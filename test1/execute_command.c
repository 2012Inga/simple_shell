#include "main.h"

/**
 * Set or modify an environment variable.
 * Command syntax: setenv VARIABLE VALUE
 * Prints an error message on stderr on failure.
 *
 * @param variable The name of the environment variable.
 * @param value The value to set for the environment variable.
 * @return 0 on success, -1 on failure.
 */
int set_env_variable(const char *variable, const char *value) {
    if (setenv(variable, value, 1) == -1) {
        fprintf(stderr, "Error: Could not set environment variable %s\n", variable);
        return -1;
    }
    return 0;
}

/**
 * Unset an environment variable.
 * Command syntax: unsetenv VARIABLE
 * Prints an error message on stderr on failure.
 *
 * @param variable The name of the environment variable to unset.
 * @return 0 on success, -1 on failure.
 */
int unset_env_variable(const char *variable) {
    if (unsetenv(variable) == -1) {
        fprintf(stderr, "Error: Could not unset environment variable %s\n", variable);
        return -1;
    }
    return 0;
}

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
    if (set_env_variable("PWD", current_directory) == -1) {
        fprintf(stderr, "Error updating PWD environment variable.\n");
        return -1;
    }

    return 0;
}

/**
 * Execute a shell command.
 * This function takes a command string as input, tokenizes it into arguments,
 * and attempts to execute the command string using execv. If the command execution
 * fails, it iterates through directories in the PATH environment variable to
 * find and execute the command. If the command is "env," it prints the environment variables.
 * If the command is "setenv" or "unsetenv," it calls the corresponding functions.
 * If the command is "cd," it changes the current working directory.
 *
 * @param command The command string to be executed.
 */
void execute_command(char *command) {
    char *token;
    char *argv[BUFFER_SIZE];
    int argc = 0;

    /* Tokenize the command string into arguments */
    token = strtok(command, " \n");
    while (token != NULL) {
        argv[argc] = token;
        argc++;
        token = strtok(NULL, " \n");
    }

    argv[argc] = NULL; /* NULL-terminate the argument array */

    /* Check if the command is "cd" */
    if (strcmp(argv[0], "cd") == 0) {
        /* Change the current working directory */
        if (argc == 1 || strcmp(argv[1], "~") == 0 || strcmp(argv[1], "$HOME") == 0) {
            /* Change to the home directory */
            if (change_directory(NULL) == -1) {
                fprintf(stderr, "Error changing to the home directory.\n");
            }
        } else if (strcmp(argv[1], "-") == 0) {
            /* Change to the previous directory */
            char *previous_directory = getenv("OLDPWD");
            if (previous_directory == NULL) {
                fprintf(stderr, "Error changing to the previous directory.\n");
            } else {
                if (change_directory(previous_directory) == -1) {
                    fprintf(stderr, "Error changing to the previous directory.\n");
                }
            }
        } else {
            /* Change to the specified directory */
            if (change_directory(argv[1]) == -1) {
                fprintf(stderr, "Error changing to the specified directory.\n");
            }
        }
    } else {
        /* Handle other commands */
        if (strcmp(argv[0], "env") == 0) {
            /* Print environment variables */
            char **env = environ;
            while (*env) {
                printf("%s\n", *env);
                env++;
            }
        } else if (strcmp(argv[0], "setenv") == 0) {
            /* Set environment variable */
            if (argc == 3) {
                if (set_env_variable(argv[1], argv[2]) == -1) {
                    exit(EXIT_FAILURE);
                }
            } else {
                fprintf(stderr, "Error: Incorrect syntax. Usage: setenv VARIABLE VALUE\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[0], "unsetenv") == 0) {
            /* Unset environment variable */
            if (argc == 2) {
                if (unset_env_variable(argv[1]) == -1) {
                    exit(EXIT_FAILURE);
                }
            } else {
                fprintf(stderr, "Error: Incorrect syntax. Usage: unsetenv VARIABLE\n");
                exit(EXIT_FAILURE);
            }
        } else {
            /* Attempt to execute the command using execvp */
            if (execvp(argv[0], argv) == -1) {
                char *path = getenv("PATH");
                char *path_copy = strdup(path);
                char *dir = strtok_custom(path_copy, ":");

                /* Iterate through directories in PATH to find and execute the command */
                while (dir != NULL) {
                    char full_path[BUFFER_SIZE];
                    snprintf(full_path, sizeof(full_path), "%s/%s", dir, argv[0]);

                    /* Check if the command exists in the directory */
                    if (access(full_path, X_OK) == 0) {
                        /* Execute the command */
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
                perror("Command not found");

                free(argv[0]); /* Free memory for the command */
                exit(EXIT_FAILURE);
            }
        }
    }

    /* Free memory for the arguments */
    for (int i = 0; i < argc; i++) {
        free(argv[i]);
    }
}

