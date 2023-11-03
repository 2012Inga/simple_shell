/**
 * tokenizer.c
 * A simple program to tokenize a command line input into indivividual tokens.
 *
 * This program reads a command line input from the user and then tokenizes it,
 * breaking it into separate words or tokens based on spaces, tabs, and newline characters.
 * The resulting tokens are then printed to the console.
 *
 * Usage: Compile the program and run it. Provide a command line input, and it will tokenize and display the individual tokens.
 *
 * Author : Inganathi Ndinga & Cizario Gum
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 64
#define MAX_TOKEN_LENGTH 128

/**
 * tokenize - Tokenize a command line input into individual tokens.
 *
 * @param input: The input command line string to be tokenized.
 * @param tokens: An array of strings to store the tokens.
 *
 * Return: The number of tokens found.
 */

int tokenize(char *input, char *tokens[])
{
	char *token;
	int token_count = 0;

	/* Use strtok, split the input into tokens based on spaces, tabs and newline.
	 *
	 */


	token = strtok(input, " \t\n");
	while (token != NULL && token_count < MAX_TOKENS)
	{
		tokens[token_count] = strdup(token);
		token_count++;
		token = strtok(NULL, " \t\n");
	}

	return (token_count);
}

int main(void)
{
	char input[MAX_TOKEN_LENGTH];
	char *tokens[MAX_TOKENS];
	int token_count, i;

	printf("#shell22$ "); /* Display a prompt */

	/* Read the entire input line */
	if (fgets(input, sizeof(input), stdin) == NULL)
	{
		perror("fgets");
		exit(EXIT_FAILURE);
	}

	/* Tokenize the input */
	token_count = tokenize(input, tokens);

	/* Print the tokens */
	for (i = 0; i < token_count; i++)
	{
		printf("Token %d: %s\n", i, tokens[i]);
		free(tokens[i]); /* Free allocated memory for each token */
	}

	return (0);
}
