#include "shell.h"

/**
 * builtins_list - Search for a match and
 * execute the associated builtin command.
 * @data: structure for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int builtins_list(data_of_program *data)
{
	int iterator;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", _builtin_env},
		{"setenv", _builtin_set_env},
		{"unsetenv", _builtin_unset_env},
		{NULL, NULL}};

	/*walk through the structure*/
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
		/*if there is a match between the given command and a builtin,*/
		if (str_compare(options[iterator].builtin, data->command_name, 0))
		{
			/*execute the function, and return the return value of the function*/
			return (options[iterator].function(data));
		}
		/*if there is no match return -1 */
	}

	return (-1);
}
