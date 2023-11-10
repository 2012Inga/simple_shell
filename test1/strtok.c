#include "main.h" 

<<<<<<< HEAD
/* Prototype for strtok_custom */
char *strtok_custom(char *str, const char *delim);

/**
 * splitString - Split a string into an array of tokens based on a delimiter.
 * @input: The input string to be split.
=======
/* @input: The input string to be split.
>>>>>>> 027bbab46fac9450c87aa466cb7412a520086f69
 * @delimiter: The delimiter used for splitting the string.
 * @count: Pointer to an integer to store the number of tokens.
 *
 * Return: An array of strings (tokens).
 */
char **splitString(const char *input, const char *delimiter, int *count) {
    int tokenCount = 0;
    char **tokens = NULL;
    int maxTokens = 10; /* Initial array size, can be adjusted based on your needs */

    *count = 0;

    tokens = (char **)malloc(maxTokens * sizeof(char *));
    if (tokens == NULL) {
        return NULL; /* Memory allocation error */
    }

    char *str = strdup(input);
    if (str == NULL) {
        free(tokens);
        return NULL; /* Memory allocation error */
    }

    char *token = strtok_custom(str, delimiter);
    while (token != NULL) {
        tokens[tokenCount] = strdup(token);
        tokenCount++;

        if (tokenCount >= maxTokens) {
            maxTokens *= 2;
            tokens = (char **)realloc(tokens, maxTokens * sizeof(char *));
            if (tokens == NULL) {
                free(str);
                return NULL; /* Memory allocation error */
            }
        }

        token = strtok_custom(NULL, delimiter);
    }

    free(str);
    tokens[tokenCount] = NULL; /* Null-terminate the array */

    *count = tokenCount;

    return tokens;
}

/**
 * strtok_custom - Custom implementation of strtok function.
 * @str: The string to tokenize.
 * @delim: The delimiter character.
 *
 * Return: A pointer to the next token, or NULL if there are no more tokens.
 */
char *strtok_custom(char *str, const char *delim) {
    static char *lastToken = NULL; /* Stores the last token between calls */
    char *token;
    char *strPointer;

    if (str != NULL) {
        lastToken = str;
    } else if (lastToken == NULL) {
        return NULL;
    }

    token = lastToken;

    while (*lastToken != '\0') {
        if (strchr(delim, *lastToken) != NULL) {
            *lastToken = '\0';
            lastToken++;
            return token;
        }
        lastToken++;
    }

    strPointer = token;

    while (*strPointer != '\0') {
        if (strchr(delim, *strPointer) != NULL) {
            *strPointer = '\0';
            lastToken = strPointer + 1;
            return token;
        }
        strPointer++;
    }

    return token;
}
<<<<<<< HEAD
<<<<<<< HEAD

extern char **environ; /* Declaration for environ */

/**
 * main - Entry point for the simple shell program
 *
 * Return: Always 0.
 */
int main(void) {
    char *command = NULL;
    size_t n_char = 0;
    int status, i;
    bool oneline = isatty(STDIN_FILENO);
    pid_t child;

    while (1) {
        if (oneline) {
            printf("#shell27$ ");
        }

        ssize_t read_result = getline(&command, NULL, stdin);

        if (read_result == -1) {
            if (oneline) {
                printf("\n");
            }
            free(command); /* Free the allocated memory for the line */
            break;
        }

        /* Parse the command and arguments */
        char **argv;
        int argc;

        // Split the command into arguments
        argv = splitString(command, " \n", &argc);

        if (argv == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            free(command);
            break;
        }

        /* Print the parsed arguments */
        for (int i = 0; i < argc; i++) {
            printf("Argument %d: %s\n", i + 1, argv[i]);
        }

        /* Implement the exit built-in command */
        if (strcmp(argv[0], "exit") == 0) {
            if (argc == 2) {
                status = atoi(argv[1]);
                // Free the allocated memory before exiting
                for (int i = 0; i < argc; i++) {
                    free(argv[i]);
                }
                free(argv);
                free(command);
                exit(status);
            } else if (argc > 2) {
                fprintf(stderr, "Usage: exit [status]\n");
            } else {
                // Free the allocated memory for arguments
                for (int i = 0; i < argc; i++) {
                    free(argv[i]);
                }
                free(argv);
            }
            continue; // Skip the fork and exec steps for the exit command
        }

        /* Implement the env built-in command */
        if (strcmp(argv[0], "env") == 0) {
            char **env = environ;
            while (*env) {
                printf("%s\n", *env);
                env++;
            }
        }

	/* Implement the setenv built-in command */
	if (strcmp(argv[0]0 "setenv") == 0) {
		if (argc == 3) {
			if (set_environment_variable(argv[1], argv[2]) == -1) {
				fprintf(stderr, "ERROR: Unable to set environment variable\n");
			}
		} else {
			fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		}

		/* Implement the unsetenv built-in command */
		if (strcmp(argv[0], "unsetenv") == 0) {
			if (argc == 2) {
				if (unset_environment_variable(argv[1]) == -1) {
					fprintf(stderr, "Error: Unable to unset environment variable\n"); }
			} else {
				fprintf(stderr, "Usage: unsetenv VARIABLE\n");
			}
		}

        /* Iterate through directories in PATH */
        char *path = getenv("PATH");
        char *path_copy = strdup(path);
        char *dir = strtok_custom(path_copy, ":");

        while (dir != NULL) {
            char full_path[1024]; /* Adjust the size as needed */
            snprintf(full_path, sizeof(full_path), "%s/%s", dir, argv[0]);

            /* Check if the command exists in the directory */
            if (access(full_path, X_OK) == 0) {
                child = fork();
                if (child < 0) {
                    fprintf(stderr, "Error: fork failed\n");
                } else if (child == 0) {
                    if (execvp(full_path, argv) == -1) {
                        fprintf(stderr, "%s: Command execution error\n", argv[0]);
                        exit(1);
                    }
                } else {
                    wait(&status);
                }
                break;
            }

            dir = strtok_custom(NULL, ":");
        }

        /* Free the allocated memory for arguments */
        for (int i = 0; i < argc; i++) {
            free(argv[i]);
        }
        free(argv);

        free(path_copy);
    }

    free(command);
    return 0;
}
