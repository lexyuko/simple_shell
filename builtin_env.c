#include "shell.h"

/**
 * _builtin_env - shows the environment where the shell runs
 * @data: structure for the program's data
 * Return: zero if success, or other number if it's declared in the arguments
 */
int _builtin_env(data_of_program *data)
{
	int x;
	char c_name[50] = {'\0'};
	char *key_copy = NULL;

	if (data->tokens[1] == NULL)
	{
		print_environ(data);
	}
	else
	{
		for (x = 0; data->tokens[1][x]; x++)
		{
			if (data->tokens[1][x] == '=')
			{
				key_copy = str_duplicate(env_get_key(c_name, data));

				if (key_copy != NULL)
				{
					env_set_key(c_name, data->tokens[1] + x + 1, data);
				}

				print_environ(data);

				if (env_get_key(c_name, data) == NULL)
				{
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{
					env_set_key(c_name, key_copy, data);
					free(key_copy);
				}

				return 0;
			}
			c_name[x] = data->tokens[1][x];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}

	return 0;
}

/**
 * _builtin_set_env - sets an environment variable
 * @data: struct for the program's data
 * Return: zero if success, or other number if it's declared in the arguments
 */
int _builtin_set_env(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL || data->tokens[3] != NULL)
	{
		errno = (data->tokens[3] != NULL) ? E2BIG : EINVAL;
		perror(data->command_name);
		return 5;
	}

	env_set_key(data->tokens[1], data->tokens[2], data);

	return 0;
}

/**
 * _builtin_unset_env - unsets an environment variable
 * @data: struct for the program's data
 * Return: zero if success, or other number if it's declared in the arguments
 */
int _builtin_unset_env(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] != NULL)
	{
		errno = (data->tokens[2] != NULL) ? E2BIG : EINVAL;
		perror(data->command_name);
		return 5;
	}

	env_remove_key(data->tokens[1], data);

	return 0;
}
