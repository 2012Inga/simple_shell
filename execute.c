#include "main.h"

int set_env_variable(const char *variable, const char *value)
{
    if (setenv(variable, value, 1) == -1)
    {
        fprintf(stderr, "Error: Could not set environment variable %s\n", variable);
        return (-1);
    }
    return(0)
}

/**
 * Unset an environment variable.
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

void _buildInCmd(char **arg)
{
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

void execute_command(char *command)
{
    char *token;
    char *argv[BUFFER_SIZE];
    int argc = 0;
    char **env = environ;

    token = strtok(command, " \n");
    while (token != NULL)
    {
        argv[argc] = token;
        argc++;
        token = strtok(NULL, " \n");
    }

    argv[argc] = NULL;

    
    if (strcmp(argv[0], "exit") == 0)
    {
        free(command); /* Free memory for the command */
	exit(0); /* Exit the shell */
    } else if (strcmp(argv[0], "env") == 0)
    {
        while (*env)
	{
            printf("%s\n", *env);
            env++;
        }
    } else {
        if (execvp(argv[0], argv) == -1)
	{
            char *path = getenv("PATH");
            char *path_copy = strdup(path);
            char *dir = strtok(path_copy, ":");

            while (dir != NULL)
	    {
                char full_path[BUFFER_SIZE];
                snprintf(full_path, sizeof(full_path), "%s/%s", dir, argv[0]);
                if (access(full_path, X_OK) == 0)
		{
                    if (execve(full_path, argv, environ) == -1)
		    {
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

