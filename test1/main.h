#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>

extern char **environ;

#define BUFFER_SIZE 1024

/* Get line function */
char *_getline(void);

char **splitString(const char *input, const char *delimiter, int *count);
char *strtok_custom(char *str, const char *delim);

void execute_command(char *command);



/* Basic_shell */

#endif
