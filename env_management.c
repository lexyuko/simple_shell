#include "shell.h"

/**
 * env_get_key - gets the value of an environment variable
 * @key: the environment variable of interest
 * @data: struct of the program's data
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char *env_get_key(char *key, data_of_program *data)
{
	// Validate arguments
	if (key == NULL || data->env == NULL)
		return NULL;

	// Obtain the length of the variable requested
	size_t key_length = str_length(key);

	int i = 0;

	// Iterate through the environment to check for the key
	while (data->env[i])
	{
		// Check for coincidence of the key
		if (str_compare(key, data->env[i], key_length) && data->env[i][key_length] == '=')
		{
			// Return the value of the key NAME= when found
			return data->env[i] + key_length + 1;
		}

		i++;
	}

	// Return NULL if the key is not found
	return NULL;
}

/**
 * env_set_key - sets or updates an environment variable with the specified key and value
 * or create it if does not exist.
 * @key: the key of the variable to set
 * @value: The value to set for the environment variable
 * @data: The structure of the program's data containing the env
 * Return: 1 if the parameters are NULL, 2 if there is an error, 0 if sucess.
 */

int env_set_key(char *key, char *value, data_of_program *data)
{
	// Validate arguments
	if (key == NULL || value == NULL || data->env == NULL)
		return 1;

	// Obtain the length of the variable requested
	size_t key_length = str_length(key);

	int i = 0;
	int is_new_key = 1;

	// Iterate through the environment to check for the key
	while (data->env[i])
	{
		// Check for coincidence of the key
		if (str_compare(key, data->env[i], key_length) && data->env[i][key_length] == '=')
		{
			// If key already exists, free the entire variable
			is_new_key = 0;
			free(data->env[i]);
			break;
		}

		i++;
	}

	// Create a string of the form key=value
	char *new_variable = str_concat(str_concat(str_duplicate(key), "="), value);

	// If it's a new key, create it at the end of the list and set the next element to NULL
	if (is_new_key)
	{
		data->env[i] = new_variable;
		data->env[i + 1] = NULL;
	}
	else
	{
		// Update the existing key with the new value
		data->env[i] = new_variable;
	}

	return 0;
}

/**
 * env_remove_key - remove a key from the environment variable
 * @key: the key to remove
 * @data: the structure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int env_remove_key(char *key, data_of_program *data)
{
	// Validate arguments
	if (key == NULL || data->env == NULL)
		return 0;

	// Obtain the length of the variable requested
	size_t key_length = str_length(key);

	int i = 0;

	while (data->env[i])
	{
		// Check for coincidences
		if (str_compare(key, data->env[i], key_length) && data->env[i][key_length] == '=')
		{
			// Free the memory occupied by the key
			free(data->env[i]);

			// Shift the remaining keys down
			int t = i;
			while (data->env[t + 1])
			{
				data->env[t] = data->env[t + 1];
				t++;
			}

			// Set the last element to NULL
			data->env[i] = NULL;

			return 1;
		}

		i++;
	}

	return 0;
}

/**
 * print_environ - prints the current environ
 * @data: struct for the program's data
 * Return: nothing
 */
void print_environ(data_of_program *data)
{
	int t;

	for (t = 0; data->env[t]; t++)
	{
		_print(data->env[t]);
		_print("\n");
	}
}
