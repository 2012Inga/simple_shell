#include "main"

/**
 * exit_arg - Exit the program with the specified status.
 * @arg: The exit status as a string.
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
