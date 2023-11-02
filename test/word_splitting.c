#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
char **splitString(const char *input, const char *delimiter, int *count) {
    char *str = strdup(input);
    if (str == NULL) {
        return NULL;
    }

    char **tokens = (char **)malloc(strlen(str) * sizeof(char *));
    if (tokens == NULL) {
        free(str);
        return NULL;
    }

    int tokenCount = 0;
    char *token = strtok(str, delimiter);

    while (token != NULL) {
        tokens[tokenCount] = strdup(token);
        tokenCount++;

        token = strtok(NULL, delimiter);
    }

    free(str);
    tokens = (char **)realloc(tokens, tokenCount * sizeof(char *));
    *count = tokenCount;

    return tokens;
}

void string_split() {
    // Example usage of the splitString function
    const char *input = "This is a sample string";
    const char *delimiter = " ";
    int count;
    char **words = splitString(input, delimiter, &count);

    if (words == NULL) {
        printf("Memory allocation error.\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("Word %d: %s\n", i + 1, words[i]);
        free(words[i]);
    }

    free(words);
    return 0;
}
