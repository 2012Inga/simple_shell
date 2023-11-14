#include "main.h"
#include "execute_command.h"

/**
 * execute_command - Execute multiple commands separated by ';'.
 * @command: The command string to be executed.
 */
void execute_command(char *command)
{
	char *token;
	char *commands[BUFFER_SIZE];
	int num_commands = 0;

	/* Tokenize the command string into commands separated by ';'*/
	token = strtok(command, ";");
	while (token != NULL)
	{
		commands[num_commands] = token;
		num_commands++;
		token = strtok(NULL, ";");
	}

	/* Execute each command */
	for (int i = 0; i < num_commands; i++)
	{
		/* Skip leading whitespaces */
		while (isspace((unsigned char)commands[i][0]))
			commands[i]++;

		/* Check if the command is not empty */
		if (commands[i][0] != '\0')
		{
			pid_t child;
			child = fork();
			if (child == -1)
			{
				perror("fork failed");
				exit(EXIT_FAILURE);
			}

			if (child == 0)
			{
				/* Child process executes the command */
				execute_single_command(commands[i]);
				exit(0);
			}
			else
			{
				/* Parent process waits for the child to finish */
				wait(NULL);
			}
		}
	}
}

/**
 * execute_single_command - Execute a single shell command.
 * @command: The command string to be executed.
 */
void execute_single_command(char *command)
{
	/* The implementation of execute_single_command remains the same */
	/* You can use the previous version of the execute_single_command function */
	/* and include the command handling logic for single commands. */
}
