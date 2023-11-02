#include <stdio.h>
#include <stdlib.h>
#include "main.h"
ssize_t custom_getline(char **line, size_t *len, FILE *stream) {
    if (*line == NULL) {
        *len = 128; // Initial buffer size
        *line = (char *)malloc(*len);
        if (*line == NULL) {
            return -1; // Allocation error
        }
    }

    int ch;
    size_t pos = 0;

    while (1) {
        ch = fgetc(stream);

        if (ch == EOF) {
            if (pos == 0) {
                free(*line);
                *line = NULL;
                *len = 0;
            }
            return -1; // End-of-file or error
        }

        if (pos >= *len - 1) {
            size_t new_len = *len * 2;
            char *new_line = (char *)realloc(*line, new_len);
            if (new_line == NULL) {
                return -1; // Reallocation error
            }
            *line = new_line;
            *len = new_len;
        }

        (*line)[pos++] = (char)ch;

        if (ch == '\n') {
            (*line)[pos] = '\0';
            return pos;
        }
    }
}

void _getline() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1) {
        printf("$ ");
        fflush(stdout);

        read = custom_getline(&line, &len, stdin);

        if (read == -1) {
            if (feof(stdin)) {
                // Reached end-of-file (Ctrl+D)
                break;
            } else {
                // Error while reading
                perror("custom_getline");
                exit(EXIT_FAILURE);
            }
        }

        printf("You entered: %s", line);
    }

    free(line);
    return 0;
}
