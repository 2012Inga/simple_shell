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

		i = 0;
		while (command[i])
		{
			if (command[i] == '\n')
			{
				command[i] = 0;
			}
			i++;
		}

		emp[0] = strdup(command);
		child = fork();
		if (child < 0)
		{
			printf("fork failed");
		}
		else if (child == 0)
		{
			if (execve(emp[0], emp, environ) == -1)
			{
				printf("%s: No such file or directory\n", emp[0]);
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
