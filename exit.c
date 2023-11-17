#include "main"

/**
 * exit function - Exits shell function.
 * @command: The command string to be executed.
 */
void exit_arg(char *arg)
{
	int status;

	if (arg == NULL)
	{
		status = 0;
	}
	else
	{
		status = atoi(arg);
	}

	exit(status);
}
