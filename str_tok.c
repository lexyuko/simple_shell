#include "shell.h"

/**
 * _strtok - Tokenizes a string using specified delimiters
 * @line: Pointer to the input string, typically obtained from getline
 * @delim: Characters that define the delimiters for string segmentation
 * Return: A pointer to the created token
 */

char *_strtok(char *line, const char *delim)
{
	int c;
	static char *n_str;
	char *token;

	if (line != NULL)
		n_str = line;
	for (; *n_str != '\0'; n_str++)
	{
		for (c = 0; delim[c] != '\0'; c++)
		{
			if (*n_str == delim[c])
				break;
		}
		if (delim[c] == '\0')
			break;
	}
	token = n_str;
	if (*token == '\0')
		return (NULL);
	for (; *n_str != '\0'; n_str++)
	{
		for (c = 0; delim[c] != '\0'; c++)
		{
			if (*n_str == delim[c])
			{
				*n_str = '\0';
				n_str++;
				return (token);
			}
		}
	}
	return (token);
}
