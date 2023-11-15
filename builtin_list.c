#include "shell.h"

/**
 * builtins_list - Search for a match and execute the associated builtin command.
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
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

	/*walk through the structure*/
	iterator = 0;
	while (options[iterator].builtin != NULL)
	{
		if (str_compare(options[iterator].builtin, data->command_name, 0))
		{
			switch (iterator)
			{
				case 0:
					return option_0_function(data);
					// Add more cases for each option if needed
					// case 1:
					//     return option_1_function(data);
					// ...
				default:
					return -1;
			}
		}
		iterator++;
	}

	return (-1);
}
