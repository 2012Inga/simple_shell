#include "main.h"

<<<<<<< HEAD:test1/main.c
/**
 * main - The main function of the shell program.
 *
 * This funtion serves as the entry point of the shell program.
 * It handles user input, executes commands, and manages the shell loop.
 *
 * Return: Return 0 on successful execution.
 */

int main(void)
{
	char *command = NULL;
	bool oneline = isatty(STDIN_FILENO);
	pid_t child;
=======
int main(void) {
    char *command = NULL;
    bool oneline = isatty(STDIN_FILENO);
    pid_t child;
    int i; 
        char *token;
        char *argv[BUFFER_SIZE];
        int argc = 0; 

    while (1) {
        if (oneline) {
            printf("#shell4.1$ ");
        }
        command = _getline();
        if (command == NULL) {
            if (oneline) {
                printf("\n");
            }
            break;
        }
	if (strcmp(command, "exit") == 0){
		free(command);
		break;
	}

	/* Tokenize the command string into arguments */
>>>>>>> a78c186d64bdb42ad8bc20d6cacc0a595c53c3c2:main.c

	while (1)
	{
		if (oneline)
		{
			printf("#shell4.1$ ");
		}

		command = _getline();

		if (command == NULL)
		{
			if (oneline)
			{
				printf("\n");
			}
			break;
		}

		if (strcmp(command, "exit") == 0)
		{
			free(command);
			break;
		}

<<<<<<< HEAD:test1/main.c
		/* Tokenize the command string into arguments */
		char *token;
		char *argv[BUFFER_SIZE];
		int argc = 0;
=======
        /* Free memory for the arguments */
        for ( i = 0; i < argc; i++) {
            free(argv[i]);
        }
>>>>>>> a78c186d64bdb42ad8bc20d6cacc0a595c53c3c2:main.c

		token = strtok(command, " \n");
		while (token != NULL)
		{
			argv[argc] = strdup(token);
			argc++;
			token = strtok(NULL, " \n");
		}

		argv[argc] = NULL; /* NULL-terminate the argument array */

		if (strcmp(argv[0], "cd") == 0)
		{
			_buildInCmd(argv);
			printf("cd :\n");
		}
		else if (strcmp(argv[0], "setenv") == 0)
		{
			if (argc == 3)
			{
				if (set_env_variable(argv[1], argv[2]) == -1)
				{
					/* Handle error if needed */
				}
				else
				{
					fprintf(stderr, "Error: Incorrect syntax. Usage: setenv VARIABLE VALUE\n");
				}
			}
		}
		else if (strcmp(argv[0], "unsetenv") == 0)
		{
			if (argc == 2)
			{
				if (unset_env_variable(argv[1]) == -1)
				{
					fprintf(stderr, "Error: Incorrect syntax. Usage: setenv VARIABLE VALUE\n");
				}
			}
		}
		else if
		{
			 ((child = fork()) == -1)
			{
				perror("fork failed");
				free(command);
				exit(EXIT_FAILURE);
			}

			if (child == 0)
			{
				execute_command(command);
				free(command);
				exit(0);
			}
			else
			{
				wait(NULL);
			}
		}

		/* Free memory for the arguments */
		for (int i = 0; i < argc; i++)
		{
			free(argv[i]);
		}

		free(command);
	}

	return (0);
}
