#include "shell.h"

/**
 * _strtok - Tokenizes a string using specified delimiters
 * @line: Pointer to the input string, typically obtained from getline
 * @delim: Characters that define the delimiters for string segmentation
 * Return: A pointer to the created token
 */


char *_strtok(char **line, const char *delim)
{
	if (line == NULL || *line == NULL || **line == '\0')
		return NULL;

	char *start = *line;
	char *token = NULL;


	// Find the beginning of the next token
	while (*start && strchr(delim, *start))
		start++;

	// Return NULL if no more tokens
	if (!*start)
	{
		**line = '\0';
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

	*line = start;

	return token;
}
