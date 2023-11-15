#include "shell.h"

/**
 * _strtok - Tokenizes a string using specified delimiters
 * @line: Pointer to the input string, typically obtained from getline
 * @delim: Characters that define the delimiters for string segmentation
 * Return: A pointer to the created token
 */

char *_strtok(char **str, const char *delim)
{
	if (!str || !(*str))
		return NULL;

	char *start = *str;
	char *token = NULL;

	// Find the beginning of the next token
	while (*start && strchr(delim, *start))
		start++;

	// Return NULL if no more tokens
	if (!*start)
	{
		*str = NULL;
		return NULL;
	}

	token = start;

	// Find the end of the token
	while (*start && !strchr(delim, *start))
		start++;

	if (*start)
	{
		*start = '\0';
		start++;
	}

	*str = start;

	return token;
}
