#include "shell.h"

/**
 * printAlias - Print aliases.
 * @data: Structure for program's data.
 * @aliasName: Name of the alias to be printed.
 * Return: 0 if successful, otherwise an error code.
 */
int printAlias(data_of_program *data, const char *aliasName)
{
	if (data->aliasList)
	{
		const size_t aliasNameLength = strlen(aliasName);

		size_t i = 0;
		while (data->aliasList[i])
		{
			const char *currentAlias = data->aliasList[i];

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
	if (aliasName != NULL || data->aliasList != NULL)
	{
		return NULL;
	}

	const size_t aliasNameLength = strlen(aliasName);

	size_t i = 0;
	while (data->aliasList[i])
	{
		const char *currentAlias = data->aliasList[i];

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
	if (aliasString == NULL || data->aliasList == NULL)
	{
		return 1;
	}

	char aliasName[250] = {0};
	const char *aliasValue = strchr(aliasString, '=');

	if (!aliasValue)
	{
		return 1;
	}

	size_t i = 0;
	while (data->aliasList[i])
	{
		char *currentAlias = data->aliasList[i];

		if (strncmp(currentAlias, aliasName, aliasNameLength) == 0 && currentAlias[aliasNameLength] == '=')
		{
			free(data->aliasList[i]);
			data->aliasList[i] = strDuplicate(aliasString);
			return 0;
		}

		i++;
	}

	// If no match is found, add the new alias to the list
	data->aliasList[data->aliasCount++] = strDuplicate(aliasString);

	return 0;
}
