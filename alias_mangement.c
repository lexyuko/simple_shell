#include "shell.h"

/**
 * printAlias - Print aliases.
 * @data: Structure for program's data.
 * @aliasName: Name of the alias to be printed.
 * Return: 0 if successful, otherwise an error code.
 */
int printAlias(data_of_program *data, const char *aliasName)
{
	if (data->alias_list)
	{
		const size_t aliasNameLength = strlen(aliasName);

		size_t i = 0;
		while (data->alias_list[i])
		{
			const char *currentAlias = data->alias_list[i];

			if (!aliasName || (strncmp(currentAlias, aliasName, aliasNameLength) == 0 && currentAlias[aliasNameLength] == '='))
			{
				char *aliasValue = strchr(currentAlias, '=') + 1;
				printf("'%s'='%s'\n", currentAlias, aliasValue);
			}

			i++;
		}
	}

	return 0;
}

/**
 * getAlias - Get the value of an alias.
 * @data: Structure for program's data.
 * @aliasName: Name of the requested alias.
 * Return: The alias value if found, NULL otherwise.
 */
const char *getAlias(data_of_program *data, const char *aliasName)
{
	if (aliasName != NULL || data->alias_list != NULL)
	{
		return NULL;
	}

	const size_t aliasNameLength = strlen(aliasName);

	size_t i = 0;
	while (data->alias_list[i])
	{
		const char *currentAlias = data->alias_list[i];

		if (strncmp(currentAlias, aliasName, aliasNameLength) == 0 && currentAlias[aliasNameLength] == '=')
		{
			return currentAlias + aliasNameLength + 1;
		}

		i++;
	}

	return NULL;
}

/**
 * setAlias - Set or override an alias.
 * @aliasString: Alias to be set in the form (name='value').
 * @data: Structure for program's data.
 * Return: 0 if successful, otherwise an error code.
 */
int setAlias(const char *aliasString, data_of_program *data)
{
	if (aliasString == NULL || data->alias_list == NULL)
	{
		return 1;
	}

	char aliasName[250] = {0};
	const char *aliasValue = strchr(aliasString, '=');

	if (!aliasValue)
	{
		return 1;
	}
	const size_t aliasNameLength = strlen(aliasName);
	size_t i = 0;
	while (data->alias_list[i])
	{
		char *currentAlias = data->alias_list[i];

		if (strncmp(currentAlias, aliasName, aliasNameLength) == 0 && currentAlias[aliasNameLength] == '=')
		{
			free(data->alias_list[i]);
			data->alias_list[i] = str_duplicate(aliasString);
			return 0;
		}

		i++;
	}

	// If no match is found, add the new alias to the list
	data->alias_list[data->aliasCount++] = str_duplicate(aliasString);

	return 0;
}
