#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>

extern char **environ;

#define BUFFER_SIZE 1024

char *_getline(void);

char **splitString(const char *input, const char *delimiter, int *count);

char *strtok_custom(char *str, const char *delim);

int set_env_variable(const char *variable, const char *value);

int unset_env_variable(const char *variable);

void execute_command(char *command);

void _buildInCmd(char **arg);

int change_directory(const char *directory);

typedef struct AliasNode {
    char *name;
    char *value;
    struct AliasNode *next;
} AliasNode;

AliasNode *alias_list;

<<<<<<< HEAD
void add_alias(char *name, char *value);

void print_aliases(void);
=======

>>>>>>> 88f69054d20ebcdcb4fc0dcc9b2732e23621ea81

int handle_separator(char *argv[], int argc);

#endif /* MAIN_H */
