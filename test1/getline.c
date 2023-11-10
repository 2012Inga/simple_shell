#include "main.h"
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
char *_getline(void) {
    char *line = NULL;
    size_t line_size = BUFFER_SIZE;
    size_t line_length = 0;
    int ch;

    line = (char *)malloc(line_size);
    if (!line) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    while (1) {
        ch = getchar();
        if (ch == EOF) {
            free(line);
            return NULL; 
        } else if (ch == '\n') {
            line[line_length] = '\0';
            return line;
	} else {
            if (line_length >= line_size - 1) {
               
                line_size *= 2;
                char *new_line = (char *)realloc(line, line_size);
                if (!new_line) {
                    perror("Memory reallocation error");
                    free(line);
                    exit(EXIT_FAILURE);
                }
                line = new_line;
            }
            line[line_length++] = ch;
        }
    }}
