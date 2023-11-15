#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

/**
 * display_prompt - Display the shell prompt.
 * Description: This function prints the shell prompt.
 */
void display_prompt(void)
{
    printf("#cisfun$ ");
    fflush(stdout);
}

/**
 * parse_arguments - Tokenize the command into arguments.
 * @command: The command string to be parsed.
 * @arguments: An array to store the parsed arguments.
 * Description: This function tokenizes the command string into arguments.
 */
void parse_arguments(char *command, char *arguments[])
{
    int argc = 0;
    char *token = strtok(command, " ");

    while (token != NULL && argc < MAX_ARGUMENTS - 1)
    {
        arguments[argc] = strdup(token); /* Use strdup to allocate memory for each argument */
        argc++;
        token = strtok(NULL, " ");
    }

    arguments[argc] = NULL; /* Null-terminate the argument array */
}

/**
 * main - Simple shell program.
 * Return: Always 0.
 * Description: This is the main function of the simple shell program.
 */
int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];
    pid_t child_pid;

    while (1)
    {
        display_prompt();

        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            /* Handle end of file (Ctrl+D) */
            printf("\n");
            break;
        }

        /* Remove the newline character */
        command[strcspn(command, "\n")] = '\0';

        child_pid = fork();

        if (child_pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0)
        {
            /* Child process */
            parse_arguments(command, arguments);

            if (execvp(arguments[0], arguments) == -1)
            {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process */
            int status;
            waitpid(child_pid, &status, 0);

            if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
            {
                fprintf(stderr, "%s: command not found\n", arguments[0]);
            }

            /* Free the memory allocated for arguments */
            for (int i = 0; i < MAX_ARGUMENTS && arguments[i] != NULL; i++)
            {
                free(arguments[i]);
            }
        }
    }

    return (0);
}
