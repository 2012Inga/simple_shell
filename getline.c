#include "main.h"

/**
 * custom_getline - Read a line from standard input.
 *
 * Description:
 * This function reads a line from the standard input. It dynamically allocates
 * memory for the line and adjusts the buffer size as needed. The function 
 * returns a pointer to the read line or NULL if an error occurs.
 *
 * Return: A pointer to the read line, or NULL if an error occurs.
 */
char *custom_getline(void) 
{
	char *line = NULL;        /* Pointer to the line being read */
	size_t line_size = BUFFER_SIZE;   /* Initial size of the buffer */
	size_t line_length = 0;    /* Length of the current line */
	int ch;                     /* Variable to store each character read */
	char *new_line;             /* Pointer for reallocated memory */

	/* Allocate memory for the initial line buffer */
	line = (char *)malloc(line_size);
	if (!line) {
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	/* Loop to read characters from standard input */
	while (1) {
		ch = getchar();
		if (ch == EOF) {
			free(line); /* Free memory before returning NULL */
			return NULL; 
		} else if (ch == '\n') { /* Check for newline character */
			line[line_length] = '\0'; /* Null-terminate the line */
			return line;
		} else {
			/* Check if the buffer is full and reallocate if needed */
			if (line_length >= line_size - 1) {
				line_size *= 2; /* Double the buffer size */ 
				new_line = (char *)realloc(line, line_size);
				if (!new_line) {
					perror("Memory reallocation error");
					free(line);
					exit(EXIT_FAILURE);
				}
				line = new_line;
			}

			/* Store the character in the line buffer */ 
			line[line_length++] = ch;
		}
	}
}

