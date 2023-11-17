#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * splitString - Split a string into an array of tokens based on a delimiter.
 * @input: The input string to be split.
 * @delimiter: The delimiter used for splitting.
 * @count: Pointer to store the number of tokens.
 *
 * Return: An array of strings (tokens).
 */

char **splitString(const char *input, const char *delimiter, int *count)
{
	int tokenCount = 0;
	char **tokens = NULL;
	int maxTokens = 10; /* Initial array size, can be adjusted based on your needs */
	char *token;
	char *str;
	*count = 0;

	tokens = (char **)malloc(maxTokens * sizeof(char *));
	if (tokens == NULL)
	{
		return (NULL); /* Memory allocation error */
	}

	str = strdup(input);
	if (str == NULL)
	{
		free(tokens);
		return (NULL); /* Memory allocation error */
	}

	token = strtok_custom(str, delimiter);
	while (token != NULL)
	{
		tokens[tokenCount] = strdup(token);
		tokenCount++;

		if (tokenCount >= maxTokens)
		{
			maxTokens *= 2;
			tokens = (char **)realloc(tokens, maxTokens * sizeof(char *));
			if (tokens == NULL)
			{
				free(str);
				return (NULL); /* Memory allocation error */
			}
		}

		token = strtok_custom(NULL, delimiter);
	}

	free(str);
	tokens[tokenCount] = NULL; /* Null-terminate the array */
	*count = tokenCount;

	return (tokens);
}

/**
 * strtok_custom - Custom implementation of strtok function.
 * @str: The string to tokenize.
 * @delim: The delimiter character.
 *
 * Return: A pointer to the next token, or NULL if there are no more tokens.
 */

char *strtok_custom(char *str, const char *delim)
{
	static char *lastToken; /* Stores the last token between calls */
	char *token;
	char *strPointer;

	if (str != NULL)
	{
		lastToken = str;
	} else if (lastToken == NULL)
	{
		return (NULL);
	}

	token = lastToken;

	while (*lastToken != '\0')
	{
		if (strchr(delim, *lastToken) != NULL)
		{
			*lastToken = '\0';
			lastToken++;
			return (token);
		}
		lastToken++;
	}

	strPointer = token;

	while (*strPointer != '\0')
	{
		if (strchr(delim, *strPointer) != NULL)
		{
			*strPointer = '\0';
			lastToken = strPointer + 1;
			return (token);
		}
		strPointer++;
	}

	return (token);
}
