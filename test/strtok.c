#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
char **splitString(const char *input, const char *delimiter, int *count) {
    int tokenCount = 0;
    char **tokens = NULL;
    int maxTokens = 10; // Initial array size, can be adjusted based on your needs

    *count = 0;

    tokens = (char **)malloc(maxTokens * sizeof(char *));
    if (tokens == NULL) {
        return NULL;
    }

    char *str = strdup(input);
    if (str == NULL) {
        free(tokens);
        return NULL;
    }

    char *token = strtok(str, delimiter);
    while (token != NULL) {
        tokens[tokenCount] = strdup(token);
        tokenCount++;

        if (tokenCount >= maxTokens) {
            maxTokens *= 2;
            tokens = (char **)realloc(tokens, maxTokens * sizeof(char *));
            if (tokens == NULL) {
                free(str);
                return NULL;
            }
        }

        token = strtok(NULL, delimiter);
    }

    free(str);
    tokens[tokenCount] = NULL; // Null-terminate the array

    *count = tokenCount;

    return tokens;
}

void _strtok() {
    const char *input = "This is a sample string";
    const char *delimiter = " ";
    int count;
    char **words = splitString(input, delimiter, &count);

    if (words == NULL) {
        printf("Memory allocation error.\n");
        return 1;
    }

    for (int i = 0; words[i] != NULL; i++) {
        printf("Word %d: %s\n", i + 1, words[i]);
        free(words[i]);
    }

    free(words);
    return 0;
}
