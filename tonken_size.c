#include "shell.h"

/**
 * tokenize - Tokenizes the input string, separating it into an array of tokens using a specified delim.
 *
 * @data: Pointer to the program's data.
 *
 * This function modifies the input string by replacing the newline character with a null terminator.
 * It then counts the number of tokens, allocates memory for the tokens in the token array.
 *  each token is stored in the tokens array.
 * The last element of the tokens array is set to NULL, and the command name is set to the first token.
 *
 * Note: The function uses dynamic memory allocation. Ensure to free the allocated memory when done using the tokens.
 * Return: An array containing single parts of input string
 */

void tokenize(data_of_program *data)
{
	const char *delim = " \t";
	char *token, *input_copy;
	int counter = 0;

	
	size_t length = str_length(data->input_line);
	if (length > 0 && data->input_line[length - 1] == '\n')
		data->input_line[length - 1] = '\0';


	input_copy = str_duplicate(data->input_line);
	if (input_copy == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}

	token = _strtok(input_copy, delim);
	while (token != NULL)
	{
		counter++;
		token = _strtok(NULL, delim);
	}

	free(input_copy);

	
	data->tokens = malloc((counter + 1) * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}

	
	token = _strtok(data->input_line, delim);
	counter = 0;
	while (token != NULL)
	{
		data->tokens[counter] = str_duplicate(token);
		if (data->tokens[counter] == NULL)
		{
			perror(data->program_name);
			exit(errno);
		}

		counter++;
		token = _strtok(NULL, delim);
	}


	data->tokens[counter] = NULL;

	data->command_name = (counter > 0) ? str_duplicate(data->tokens[0]) : NULL;
}

