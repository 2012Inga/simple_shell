#include "main.h"

/**
 * execute_single_command - Execute a single command in a child process.
 * @command: The command to execute.
 *
 * Description:
 * This function takes a command as input, forks a child process, and executes
 * the command in the child process. The parent process waits for the child to
 * complete.
 */
void execute_single_command(char *command)
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
		/* Child process */
		execute_command(command);
		exit(EXIT_SUCCESS);
	}
	else
	{
		/* Parent process */
		waitpid(child, NULL, 0);
	}
}

/**
 * execute_logical_operator - Execute a command based on the result of the previous one.
 * @command: The command to execute.
 * @prev_status: The exit status of the previous command.
 * @logical_operator: The logical operator (&& or || or ;).
 *
 * Description:
 * This function takes a command, the exit status of the previous command, and
 * a logical operator. It executes the command based on the result of the
 * previous one and returns the exit status of the executed command.
 *
 * Return:
 * The exit status of the executed command.
 */
int execute_logical_operator(char *command, int prev_status, char *logical_operator)
{
	int status;
	pid_t child;

	if ((strcmp(logical_operator, "&&") == 0 && prev_status == 0) ||
		(strcmp(logical_operator, "||") == 0 && prev_status != 0) ||
		(strcmp(logical_operator, ";") == 0))
	{
		/* Execute the command only if the condition is met */
		child = fork();
		if (child == -1)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}

		if (child == 0)
		{
			/* Child process */
			execute_command(command);
			exit(EXIT_SUCCESS);
		}
		else
		{
			/* Parent process */
			waitpid(child, &status, 0);
			return (status);
		}
	}

	/* Return the previous status if the condition is not met */
	return (prev_status);
}

/**
 * handle_separator - Execute commands separated by logical operators && or || or ;.
 * @argv: An array of command-line arguments.
 * @argc: The number of command-line arguments.
 *
 * Description:
 * This function takes an array of command-line arguments and the number of
 * arguments. It executes commands separated by logical operators &&, ||, or ;.
 * It returns the exit status of the last executed command.
 *  Return:
 * The exit status of the last executed command.
 */
int handle_separator(char *argv[], int argc)
{
	int status = 0;
	int i;

	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "&&") == 0 || strcmp(argv[i], "||") == 0)
		{
			/* Logical operator found */
			if (i + 1 < argc)
			{
				/* Execute command based on the logical operator */
				status = execute_logical_operator(argv[i + 1], status, argv[i]);
				i++; /* Skip the next argument */
			}
			else
			{
				/* Error: Logical operator without a following command */
				fprintf(stderr, "Syntax error: Logical operator without a following command\n");
				return (-1);
			}
		}
		else if (strcmp(argv[i], ";") == 0)
		{
			/* Semicolon found, execute the next command */
			if (i + 1 < argc)
			{
				execute_single_command(argv[i + 1]);
				status = 0; /* Reset status for semicolon separator */
				i++;       /* Skip the next argument */
			}
			else
			{
				/* Error: Semicolon without a following command */
				fprintf(stderr, "Syntax error: Semicolon without a following command\n");
				return (-1);
			}
		}
		else
		{
			/* Single command */
			execute_single_command(argv[i]);
		}
	}

	return (status);
}
