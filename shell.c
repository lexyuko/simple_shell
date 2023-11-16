#include "shell.h"

/**
 * main - Initialize program variables and start the shell.
 * @argc: Number of command line arguments.
 * @argv: Command line arguments.
 * @env: Environment variables.
 * Return: 0 on success.
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program dataStruct = {NULL}, *data = &dataStruct;
	char *prompt = "";

	initialize_Data(data, argc, argv, env);

	signal(SIGINT, handle_Ctrl_C);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		/* We are in the terminal, interactive mode */
		errno = 2; /* ???? */
		prompt = PROMPT_MSG;
	}

	errno = 0;
	sisifo(prompt, data);

	return (0);
}

/**
 * handle_Ctrl_C - Handle SIGINT (Ctrl+C) signal.
 * @UNUSED: Signal value (UNUSED).
 */
void handle_Ctrl_C(int sgnl UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * initialize_Data - Initialize the structure with program information.
 * @data: Pointer to the program's data structure.
 * @argc: Number of command line arguments.
 * @argv: Array of arguments passed to the program.
 * @env: Environment passed to the program.
 */
void initialize_Data(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;
	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	switch (argc)
	{
		case 1:
			data->file_descriptor = STDIN_FILENO;
			break;
		case 2:
			data->file_descriptor = open(argv[1], O_RDONLY);
			if (data->file_descriptor == -1)
			{
				_printe(data->program_name);
				_printe(": 0: Can't open ");
				_printe(argv[1]);
				_printe("\n");
				exit(127);
			}
			break;
		default:
			_printe("Usage: ");
			_printe(data->program_name);
			_printe(" [file]\n");
			exit(1);
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	igf (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;
	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}

/**
 * sisifo - Infinite loop that shows the prompt and handles user input.
 * @prompt: Prompt to be printed.
 * @data: Program data structure.
 */
void sisifo(char *prompt, data_of_program *data)
{
	int errorCode = 0, _stringLen = 0;

	for (data->exec_counter = 1;; ++(data->exec_counter))
	{
		_print(prompt);
		errorCode = _stringLen = get_line(data);

		if (errorCode == EOF)
		{
			free_all_data(data);
			exit(errno); /* If EOF is the first character of the string, exit */
		}

		if (_stringLen >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{ /* if a text is given to prompt, execute */
				errorCode = execute(data);
				if (errorCode != 0)
					_print_error(errorCode, data);
			}
			free_recurrent_data(data);
		}
	}
}
