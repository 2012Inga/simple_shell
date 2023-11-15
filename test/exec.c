#include <stdio.h>
#include <unistd.h>
#include "main.h"

/**
 * my_execve - Execute a program
 *
 * @param filename: The name of the file to execute.
 * @param argv: An array of pointers to null-terminated strings representing
 *               the arguments to the program.
 *
 * Return: On success, this function does not return. On failure, it returns -1
 *         and sets `errno` to indicate the error.
 */
int my_execve(const char *filename, char *const argv[])
{
    printf("Before execve\n");
    if (execve(filename, argv, NULL) == -1)
    {
        perror("Error:");
    }
    printf("After execve\n");
    return 0;
}

int main(void)
{
    char *argv[] = {"/bin/ls", "-l", "/usr/", "/ls -l", NULL};
    my_execve(argv[0], argv);

    return 0;
}
