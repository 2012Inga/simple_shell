#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_SIZE 1024

static char buffer[READ_SIZE];
static size_t buffer_size = 0;
static size_t buffer_position = 0;

/**
 * custom_getline - Read a line from standard input.
 *
 * Description:
 * This function reads a line from the standard input. It dynamically allocates
 * memory for the line and adjust the buffer size as needed. The function 
 * return a pointer to the read line or NULL if an error occurs.
 *
 * Return: A pointer to the reade line, or NULL if an error occurs.
 */

char *custom_getline(void) {
    size_t size = 0;
    char *line = NULL;
    char ch;

    while (1) {
        if (buffer_position == 0) {
            buffer_size = read(STDIN_FILENO, buffer, READ_SIZE);
            if (buffer_size <= 0) {
                if (line != NULL) {
                    free(line);
                }
                return NULL;
            }
	    buffer_position = 0;

        }

        ch = buffer[buffer_position];
        buffer_position++;

        if (ch == '\n' || ch == '\0') {
            line = (char *)realloc(line, size + 1);
            if (line == NULL) {
                return NULL;
            }
            line[size] = '\0';
            break;
        } else {
            line = (char *)realloc(line, size + 2);
            if (line == NULL) {
                return NULL;
            }
            line[size] = ch;
            size++;
        }
    }

    return line;
}

int main(void) {
    char *command = NULL;
    bool oneline = isatty(STDIN_FILENO);
    pid_t child;

    while (1) {
	if (oneline) {
	    printf("#shell27$ ");
    	    fflush(stdout); /* Ensure prompt is printed immediately */
	}

	ssize_t read_result = getline(&command, &buffer_size, stdin);

	if (read_result == -1) {
	    if (oneline) {
	        printf("\n");
	    }
	    free(command);
	    break;
	}

	/* Process the command and arguments */
	
	/* Rest buffer position and size for the next iteration */
	buffer_position = 0;
	buffer_size = 0;
    }
    
    free(command);
    return (0);
}
