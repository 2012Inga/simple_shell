#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "main.h"

/**
 * _stat - Check the existence of files and directories and display the results.
 *
 * This function takes an array of command-line arguments and checks the existence
 * of the specified files and directories using the `stat` function. It then prints
 * whether each specified path is found or not found.
 *
 * @param ac: The number of command-line arguments.
 * @param av: An array of command-line argument strings.
 */

void _stat(int ac, char **av)
{
	unsigned int i;
	struct stat st;

	if (ac < 2)
	{
		printf("Usage: %s path_to_file ...\n", av[0]);
		return;
	}

	i = 1;
	while (av[i])
	{
		printf("%s:", av[i]);
		if (stat(av[i], &st) == 0)
		{
			printf(" FOUND\n");
		}
		else
		{
			printf(" NOT FOUND\n");
		}
		i++;
	}
}
