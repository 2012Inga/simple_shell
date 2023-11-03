#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

/* environ variables */
extern char **environ;
/**
 * signal - Set a function to handle a specific signal.
 *
 * @signum: The signal number to handle.
 * @handle: The signal handler to be called when the signal is received.
 *
 * Return: On success, the previous signal handler function is returned. On
 * error, SIG_ERR is returned.
 */
extern __sighandler_t signal(int signum, __sighandler_t handler);

/* From custom_getline.c */
/**
 * custom_getline - Read a line from a file stream and store it in a buffer.
 *
 * @line: A pointer to a buffer to store the line.
 * @len: A pointer to the size of the buffer.
 * @stream: The file stream to read from.
 *
 * Return: The number of characters read, or -1 on failure.
 */
ssize_t custom_getline(char **line, size_t *len, FILE *stream);

/* From fork_exec_wait.c */
/**
 * fork_exe_wait - Fork, execute a command, and wait for it to finish.
 *
 * @command: The command to be execute.
 *
 * Return: On success, the process ID of the child process is returned. On
 * failure, -1 is returned.
 */
pid_t fork_exec_wait(const char *command);

/* From custom_getenv.c */
/**
 * custom_getenv.c - Get the value of an environment variable.
 *
 * @name: The name of the environment variable.
 *
 * Return: A pointer to the value of the environment variable, or NULL if not found.
 */
char *custom_getenv(const char *name);

/* from stat.c */
/**
 * custom_stat - Check if a file exists.
 *
 * @path: The path to the file.
 *
 * Return:  of the file exists, -1 if not found or error occurs.
 */
int custom_stat(const char *path);

/*========Split_string.c=======*/
/**
 * split_string - Split a string into an array of substrings.
 *
 * @str: The input string to be split.
 * @delimiter: The delimiter character to use for splitting.
 *
 * Return: An array of substrings, or NULL IF memory allocation fails.
 */
char **split_string(const char *str, const char *delimiter);

/* fork */
/**
 * custom_fork - Fork a new process.
 *
 * Return: The process ID of the child process, or -1 on failure.
 */
pid_t custom_fork(void)

/* From tokenizer.c */
int tokenizer(char *input, char *tokens[]);

/* From strtok.c */
/**
 * splitString - Tokenize a string into individual tokens.
 *
 * @input: The input string to tokenize.
 * @delimiter: The delimiter to split the string.
 * @count: A pointer to an integer to store the number of tokens found.
 *
 * Return: An array of token strings.
 */
char **splitString(const char *input, const char *delimiter, int *count);

/**
 * _strtok - A sample function that demonstrates the usage of splitString.
 */
void _strtok(void);


#endif
