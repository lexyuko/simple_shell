#include "shell.h"

/**
 * env_get_key - gets the value of an environment variable
 * @key: the environment variable of interest
 * @data: struct of the program's data
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char *env_get_key(char *key, data_of_program *data)
{
	int i, key_length = 0;
	/* Validate arguments*/
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* Obtain the length of the variable requested*/
	key_length = str_length(key);

	/* Iterate through the environment to check for the key*/
	while (data->env[i])
	{
		/* Check for coincidence of the key*/
		if (str_compare(key, data->env[i],
					key_length) && data->env[i][key_length] == '=')
		{
			/* Return the value of the key NAME= when found*/
			return (data->env[i] + key_length + 1);
		}

		i++;
	}

	/* Return NULL if the key is not found*/
	return (NULL);
}

/**
 * env_set_key - sets or updates an environment
 * variable with the specified key and value
 * or create it if does not exist.
 * @key: the key of the variable to set
 * @value: The value to set for the environment variable
 * @data: The structure of the program's data containing the env
 * Return: 1 if the parameters are NULL, 2 if there is an error, 0 if sucess.
 */

int env_set_key(char *key, char *value, data_of_program *data)
{
	int i, key_length = 0;
	int is_new_key = 1;

	/* Validate arguments*/
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* Obtain the length of the variable requested*/
	key_length = str_length(key);

	/* Iterate through the environment to check for the key*/
	while (data->env[i])
	{
		/* Check for coincidence of the key*/
		if (str_compare(key, data->env[i],
					key_length) && data->env[i][key_length] == '=')
		{
			/* Ifi key already exists, free the entire variable*/
			   is_new_key = 0;
			   free(data->env[i]);
			   break;
			   }

			   i++;
			   }

		/* Create a string of the form key=value*/
	data->env[i] = str_concat(str_duplicate(key), "=");
	data->env[i] =str_concat(data->env[i], value);

	if (is_new_key)
	{
		/* create at end of the list */
		/* and put the NULL value in the next position */
		data->env[i + 1] = NULL;
	}
		return (0);
}

/**
 * env_remove_key - remove a key from the environment variable
 * @key: the key to remove
 * @data: the structure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int env_remove_key(char *key, data_of_program *data)
{
	int i, key_length = 0;
	/* Validate arguments*/
	if (key == NULL || data->env == NULL)
		return (0);

	/* Obtain the length of the variable requested*/
	key_length = str_length(key);

	while (data->env[i])
	{
		/* Check for coincidences*/
		if (str_compare(key, data->env[i],
					key_length) && data->env[i][key_length] == '=')
		{
			/* Free the memory occupied by the key*/
			free(data->env[i]);

			/* Shift the remaining keys down*/

			while (data->env[i + 1])
			{
				data->env[i] = data->env[i + 1];
				i++;
			}

			/* Set the last element to NULL*/
			data->env[i] = NULL;

			return (1);
		}

		i++;
	}

	return (0);
}

/**
 * print_environ - prints the current environ
 * @data: struct for the program's data
 * Return: nothing
 */

void print_environ(data_of_program * data)
{
	int t;

	for (t = 0; data->env[t]; t++)
	{
		_print(data->env[t]);
		_print("\n");
	}
}
