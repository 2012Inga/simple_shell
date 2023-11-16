#include "main.h"

int main(void)
{
    char *command = NULL;
    bool oneline = isatty(STDIN_FILENO);
    pid_t child;
    alias_list = NULL; /* Initialize the alias list */

    while (1) {
        if (oneline)
	{
            printf("#shell4.1$ ");
        }
        command = _getline();
        if (command == NULL)
	{
            if (oneline) {
                printf("\n");
            }
            break;
        }
        if (strcmp(command, "exit") == 0)
	{
            free(command);
            break;
        }

        /* Tokenize the command string into arguments */
        char *token;
        char *argv[BUFFER_SIZE];
        int argc = 0;

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
        } else if (strcmp(argv[0], "setenv") == 0)
	{
            if (argc == 3)
	    {
                if (set_env_variable(argv[1], argv[2]) == -1)
		{
                    /* Handle setenv error */
                } else
		{
                    fprintf(stderr, "Error: Incorrect syntax. Usage: setenv VARIABLE VALUE\n");
                }
            }
        } else if (strcmp(argv[0], "unsetenv") == 0)
	{
            if (argc == 2)
	    {
                if (unset_env_variable(argv[1]) == -1)
		{
                    fprintf(stderr, "Error: Incorrect syntax. Usage: setenv VARIABLE VALUE\n");
                }
            }
        } else if (strcmp(argv[0], "alias") == 0)
	{
            /* Handle alias command */
            if (argc == 1)
	    {
                /* Print all aliases */
                print_aliases();
            } else
	    {
                /* Handle alias definition */
                for (int i = 1; i < argc; i++)
		{
                    char *name = strtok(argv[i], "=");
                    char *value = strtok(NULL, "=");

                    /* If value is not provided, print the alias */
                    if (value == NULL)
		    {
                        /* Print the alias*/
                        print_aliases();
                    } else
		    {
                        /* Define or redefine the alias*/
                        add_alias(name, value);
                    }
                }
            }
        } else
	{
            /* Handle other commands*/

            if ((child = fork()) == -1)
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
            } else {
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

    /* Free memory for aliases */
    AliasNode *current = alias_list;
    while (current != NULL) {
        free(current->name);
        free(current->value);
        AliasNode *temp = current;
        current = current->next;
        free(temp);
    }

    return (0);
}
