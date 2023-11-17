#include "main.h"

/**
 * main.c - Implementation of the 'alias' command and related functions.
 */

/**
 * Print_aliases: Prints all defined aliases in the form name='value'.
 *
 * This function iterates through the list of aliases and prints each alias
 * alon with its corresponding calue in the specified format.
 */
void print_aliases(void) {
    AliasNode *current = alias_list;
    while (current != NULL) {
        printf("%s='%s'\n", current->name, current->value);
        current = current->next;
    }
}

/**
 * find_alias - Finds an alias with the given name.
 * @name: The name of the alias to find.
 * Return: A pointer to the AliasNode if found, otherwise NULL.
 */
AliasNode *find_alias(char *name)
{
    AliasNode *current = alias_list;
    while (current != NULL) 
    {
        if (strcmp(current->name, name) == 0) {
            return (current);
        }
        current = current->next;
    }
    return (NULL);
}

/**
 * define_alias - Defines or modifies an alias with the given name and value.
 * @name: The name of the alias.
 * @value: The value to assign to the alias.
 */
void define_alias(char *name, char *value)
{
    AliasNode *existing = find_alias(name);
    if (existing != NULL)
    {
        free(existing->value);
        existing->value = strdup(value);
    } else
    {
        AliasNode *new_alias = malloc(sizeof(AliasNode));
        new_alias->name = strdup(name);
        new_alias->value = strdup(value);
        new_alias->next = alias_list;
        alias_list = new_alias;
    }
}

/**
 * alias_command - Handles the 'alias' command, printing or defining aliases as needed.
 * @argc: The number of command-line arguments.
 * @argv: An array of command-line argument strings.
 */
void alias_command(int argc, char *argv[]) {
    	int i;
	if (argc == 1) {
        /* Print all aliases */
        print_aliases();
    } else {
        /* Check if the alias is already defined and print */
        for (int i = 1; i < argc; i++)
	{
            char *name = strtok_custom(argv[i], "=");
            AliasNode *existing = find_alias(name);
            if (existing != NULL) {
                printf("%s='%s'\n", existing->name, existing->value);
            }
        }

        /* Define new aliases */
        for (int i = 1; i < argc; i++)
	{
            char *name = strtok_custom(argv[i], "=");
            char *value = strtok_custom(NULL, "=");
            if (value != NULL)
	    {
                define_alias(name, value);
            }
        }
    }
}

/**
 * main - The main function serves as the entry point for the shell program.
 *
 * This function initializes the shell environment, handles user input, and
 * manages the execution of commands. The main loop continues until the user
 * exits the shell, ensuring proper memory management and error handling.
 *
 * Return: 0 on successful execution.
 */
int main(void) 
{
    char *commands[] = {"alias", "ls='ls -l'", "alias", "grep", "alias"};
    handle_separator(commands, 5);

    return (0);
}
