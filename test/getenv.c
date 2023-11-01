#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

char *_getenv(const char *name) {
    if (name == NULL) {
        return NULL; /* Invalid input */
    }

    for (char **env = environ; *env != NULL; env++) {
        char *variable = *env;
        if (strncmp(variable, name, strlen(name)) == 0 && variable[strlen(name)] == '=') {
            return variable + strlen(name) + 1;
        }
    }
    return NULL; /* Variable not found */
}

int main() {
    char *path = _getenv("PATH");
    if (path != NULL) {
        printf("PATH = %s\n", path);
    } else {
        printf("PATH environment variable not found.\n");
    }
    return 0;
}
