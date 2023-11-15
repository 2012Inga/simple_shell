#include "main.h"
/**
  * set_env_variable - Set or modify an evironment variable.
  * @vaiable: The name of the environment variable.
  * @value: The value to set for the environment variable.
  *
  * Return: 0 on success, -1 on failure.
  */

int set_env_variable(const char *variable, const char *value)
{
    if (setenv(variable, value, 1) == -1)
{
        fprintf(stderr, "Error: Could not set environment variable %s\n", variable);
        return (-1);
    }
    return (0);
}

/**
 * unset_env_variable - Unset an environment variable.
 * @variable: The name of the environment variable to unset.
 * Command syntax: unsetenv VARIABLE
 * Prints an error message on stderr on failure.
 *
 * @param variable The name of the environment variable to unset.
 * @return 0 on success, -1 on failure.
 */
int unset_env_variable(const char *variable)
{
    if (unsetenv(variable) == -1)
{
        fprintf(stderr, "Error: Could not unset environment variable %s\n", variable);
        return (-1);
    }
    return (0);
}
/**
  *_buildInCmd - Handle built-in commands.
  * @arg: Array of arguments for the built-in command.
  */
void _buildInCmd(char **arg) {
    if (strcmp(arg[0], "exit") == 0)
{
        printf("Exiting shell .. \n");
        exit(0);
    } else if (strcmp(arg[0], "cd") == 0)
{
        if (arg[1] == NULL)
            chdir(getenv("HOME"));
        else
            chdir(arg[1]);
    }
    return;
}
/**
  * execute_command - Execute a shell command.
  * @command: The command string to be executed.
  */
void execute_command(char *command)
{
    char *token;
    char *argv[BUFFER_SIZE];
    int argc = 0;
    int i;
    /* Tokenize the command string into arguments */
    token = strtok(command, " \n");
    while (token != NULL)
{
        argv[argc] = strdup(token);
        argc++;
        token = strtok(NULL, " \n");
    }

    argv[argc] = NULL; /* NULL-terminate the argument array */

    /* Check if the command is "cd" */
    if (strcmp(argv[0], "cd") == 0)
{
        /* Change the current working directory */
        _buildInCmd(argv);
    } else {
        /* Handle other commands */
        if (strcmp(argv[0], "env") == 0)
{
            /* Print environment variables */
            char **env = environ;
            while (*env)
{
                printf("%s\n", *env);
                env++;
            }
        } else if (strcmp(argv[0], "setenv") == 0)
{
            /* Set environment variable */
            if (argc == 3)
{
                if (set_env_variable(argv[1], argv[2]) == -1)
{
                    exit(EXIT_FAILURE);
                }
            } else {
                fprintf(stderr, "Error: Incorrect syntax. Usage: setenv VARIABLE VALUE\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[0], "unsetenv") == 0)
{
            /* Unset environment variable */
            if (argc == 2) {
                if (unset_env_variable(argv[1]) == -1)
{
                    exit(EXIT_FAILURE);
                }
            } else {
                fprintf(stderr, "Error: Incorrect syntax. Usage: unsetenv VARIABLE\n");
                exit(EXIT_FAILURE);
            }
        } else {
            /* Attempt to execute the command using execvp */
            if (execvp(argv[0], argv) == -1)
{
                char *path = getenv("PATH");
                char *path_copy = strdup(path);
                char *dir = strtok_custom(path_copy, ":");

                /* Iterate through directories in PATH to find and execute the command */
                while (dir != NULL)
{
                    char full_path[BUFFER_SIZE];
                    snprintf(full_path, sizeof(full_path), "%s/%s", dir, argv[0]);

                    /* Check if the command exists in the directory */
                    if (access(full_path, X_OK) == 0)
{
                        /* Execute the command */
                        if (execve(full_path, argv, environ) == -1)
{
                            perror("Command execution error");
                            free(path_copy);
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
    for (i = 0; i < argc; i++)
{
        free(argv[i]);
    }

     /* Free the last NULL pointer in argv */
    free(argv[argc]);
}

