#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
int main(void)
{
	char *command = NULL;
	size_t n_char = 0;
	char *emp[] = {NULL, NULL};
	int status, i;
	bool oneline = isatty(STDIN_FILENO);
	pid_t child;

	while (1)
	{
		if (oneline)
		{
			printf("#shell27$ ");
		}
		if (getline(&command, &n_char, stdin) == EOF)
		{
			if (oneline)
			{
				printf("\n");
			}
			break;
		}

		/* Parse the command and arguments */
		char *token;
		char *argv[64]; /* Maximum number of arguments */

		int argc = 0;

		token = strtok(command, "\n" /* Tokenize by space and newline*/
		while (token != NULL)
		{
			argv[argc] = token;
			argc++;
			token = strtok(NULL, "\n");
		}

		argv[argc] = NULL; /* NULL - terminate the argument array*/

		child = fork();
		if (child < 0)
		{
			printf("fork failed");\
		}
		else if (child == 0)
		{

		i = 0;
		while (command[i])
		{

		emp[0] = strdup(command);
		child = fork()
			printf("fork failed");
		}
		else if (child == 0)
		{
			if (execve(emp[0], emp, environ) == -1)
			{
				printf("%s: Command not found\n", emp[0]);
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
	}

	free(command);
	return (0);
}
