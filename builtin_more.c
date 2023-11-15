#include "shell.h"

/**
 * builtin_exit - exit of the program with the status
 * @data: structure for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_exit(data_of_program *data)
{
	int t;

	if (data->tokens[1] != NULL)
	{/*if exists arg for exit, check if is a number*/
		for (t = 0; data->tokens[1][t]; t++)
			if ((data->tokens[1][t] < '0' || data->tokens[1][t] > '9')
				&& data->tokens[1][t] != '+')
			{/*if is not a number*/
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - change the current directory
 * @data: structure for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_cd(data_of_program *data)
{
	char *dir_home = env_get_key("HOME", data), *dir_old = NULL;
	char prev_dir[128] = {0};
	int err_code = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = env_get_key("OLDPWD", data);
			if (dir_old)
				error_code = set_work_directory(data, dir_old);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (err_code);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(prev_dir, 128);

		return (set_work_directory(data, dir_home));
	}
	return (0);
}

/**
 * set_work_directory - set the path as the new work directory
 * @data: structure for the program's data
 * @curr_dir: path to be set as the working directory
 * Return:  if sucess return 0, or other number declared in the function
 */
int set_work_directory(data_of_program *data, char *curr_dir)
{
	char prev_dir[128] = {0};
	int err_code = 0;

	getcwd(prev_dir, 128);

	if (!str_compare(prev_dir, curr_dir, 0))
	{
		err_code = chdir(curr_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", curr_dir, data);
	}
	env_set_key("OLDPWD", prev_dir, data);
	return (0);
}

/**
 * builtin_help - shows the environment where the shell help runs
 * @data: structure for the program's data
 * Return: if sucess return o, or other number declared in the function
 */
int builtin_help(data_of_program *data)
{
	int j, length = 0;
	char *Info[6] = {NULL};

	Info[0] = HELP_MSG;

	/* validate args */
	if (data->tokens[1] == NULL)
	{
		_print(Info[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = 2LARGE;
		perror(data->command_name);
		return (5);
	}
	Info[1] = HELP_EXIT_MSG;
	Info[2] = HELP_ENV_MSG;
	Info[3] = HELP_SETENV_MSG;
	Info[4] = HELP_UNSETENV_MSG;
	Info[5] = HELP_CD_MSG;

	for (j = 0; Info[i]; j++)
	{
		/*print the length of string */
		length = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], Info[j], length))
		{
			_print(Info[j] + length + 1);
			return (1);
		}
	}
	/*if there is no match, print error and return -1 */
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * builtin_alias - set, remove or printaliases
 * @data: structure for the program's data
 * Return: if sucess return 0, or other number declared in the function
 */
int builtin_alias(data_of_program *data)
{
	int x = 0;

	/* if there are no arguments, print all environment */
	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++x])
	{/* if there are arguments, set or print each env variable*/
		if (count_characters(data->tokens[x], "="))
			set_alias(data->tokens[x], data);
		else
			print_alias(data, data->tokens[x]);
	}

	return (0);
}