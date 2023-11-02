#include <stdio.h>
#include <stdlib.h>
#include "main.h"

extern char **environ;

/**
 * my_environ - Print and manipulate environment variables.
 */
void my_environ(void)
{
	char **env;

	/* Print all environment variables */
	for (env = environ; *env; env++)
		printf("%s\n", *env);

	/* Set or modify an environment variable */
	setenv("MY_VARIABLE", "Hello, World!", 1); /* Overwrite if it already exists */

	/* Access the value of an environment variable */
	char *value = getenv("MY_VARIABLE");
	if (value != NULL)
		printf("MY_VARIABLE = %s\n", value);
	else
		printf("MY_VARIABLE is not set.\n");

	/* Unset an environment variable */
	unsetenv("MY_VARIABLE");

	/* Check if an environment variable exists */
	if (getenv("MY_VARIABLE") == NULL)
		printf("MY_VARIABLE is unset.\n");
}
