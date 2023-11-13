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

/**
 * Set or modify an environment variable.
 * Command syntax: setenv VARIABLE VALUE
 * Prints an error message on stderr on failure.
 *
 * @param variable The name of the environment variable.
 * @param value The value to set for the environment variable.
 * @return 0 on success, -1 on failure.
 */


#define BUFFER_SIZE 1024

/* Function to read a line from standard input */
char *_getline(void);

/**
 * Split a string into an array of tokens based on a delimiter.
 *
 * @param input The input string to be split.
 * @param delimiter The delimiter used for splitting the string.
 * @param count Pointer to an integer to store the number of tokens.
 * @return An array of strings (tokens).
 */
char **splitString(const char *input, const char *delimiter, int *count);

/**
 * Custom implementation of strtok function.
 *
 * @param str The string to tokenize.
 * @param delim The delimiter character.
 * @return A pointer to the next token, or NULL if there are no more tokens.
 */
char *strtok_custom(char *str, const char *delim);

/**
 * Execute a shell command.
 *
 * This function takes a command string as input, tokenizes it into arguments,
 * and attempts to execute the command string using execv. If the command execution
 * fails, it iterates through directories in the PATH environment variable to
 * find and execute the command. If the command is "env," it prints the environment variables.
 *
 * @param command The command string to be executed.
 */


/**
 * Set or modify an environment variable.
 * Command syntax: setenv VARIABLE VALUE
 * Prints an error message on stderr on failure.
 *
 * @param variable The name of the environment variable.
 * @param value The value to set for the environment variable.
 * @return 0 on success, -1 on failure.
 */
int set_env_variable(const char *variable, const char *value);

/**
 * Unset an environment variable.
 * Command syntax: unsetenv VARIABLE
 * Prints an error message on stderr on failure.
 *
 * @param variable The name of the environment variable to unset.
 * @return 0 on success, -1 on failure.
 */
int unset_env_variable(const char *variable);

/* Get line function */
char *_getline(void);

char **splitString(const char *input, const char *delimiter, int *count);
char *strtok_custom(char *str, const char *delim);

int set_env_variable(const char *variable, const char *value);
int unset_env_variable(const char *variable);
void execute_command(char *command);

/**
 * Change the current working directory and update the PWD environment variable.
 *
 * @param directory The directory to change to.
 * @return 0 on success, -1 on failure.
 */
int change_directory(const char *directory);

/** Execute a shell command.
 * This function handles various shell commands, including the cd command.
 *
 * @param command The command string to be executed.
 */
void execute_command(char *command);

#endif /* MAIN_H */
