#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"
/*
 * File description : path - checks the path if is valid
 * @path: use tokenizer path
 * Return : path with command on success
 */

void findFileInPath(const char *filename) {
    char *path = getenv("PATH");
    if (path == NULL) {
        printf("PATH environment variable not found.\n");
        return;
    }

    char *token = strtok(path, ":");

    while (token != NULL) {
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s/%s", token, filename);

        if (access(filepath, F_OK) == 0) {
            printf("%s\n", filepath);
            return;
        }

        token = strtok(NULL, ":");
    }

    printf("%s not found in PATH.\n", filename);
}

void _path(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s filename ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        findFileInPath(argv[i]);
    }

    return 0;
}
