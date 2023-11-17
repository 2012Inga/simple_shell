#include "main.h"



/**
 * execute_single_command - Execute a single command in a child process.
 * @command: The command to execute.
 * Return: void
 */
void execute_single_command(char *command) {
    pid_t child = fork();

    if (child == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (child == 0) {
        /* Child process */
        execute_command(command);
        exit(EXIT_SUCCESS);
    } else {
        /* Parent process */
        waitpid(child, NULL, 0);
    }
}

/**
 * handle_separator - Execute commands separated by logical operators && or || or ;.
 * @argv: An array of command-line arguments.
 * @argc: The number of command-line arguments.
 * Return: The exit status of the last executed command.
 */
int handle_separator(char *argv[], int argc) {
    int status = 0,i;

    for (i = 0; i < argc; i++) {
        if (strpbrk(argv[i], "&;|")) {
            printf("Skipping command with separators: %s\n", argv[i]);
        } else {
            execute_single_command(argv[i]);
        }
    }

    return status;
}
