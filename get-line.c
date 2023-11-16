#include "shell.h"

/**
 * get_line - read one line from the prompt.
 * @data: struct for the program's data
 *
 * Return: reading counting bytes.
 */
int get_line(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *command_array[10] = {NULL};
	static char array_of_operators[10] = {'\0'};
	ssize_t bytes_to_read, x = 0;

	/* check if doesnot exist more commands in the array */
	/* and checks the logical operators */
	if (!command_array[0] || (array_of_operators[0] == '&' && errno != 0) ||
			(array_of_operators[0] == '|' && errno == 0))
	{
		/*free the memory allocated in the array if it exists */
		for (x = 0; command_array[x]; x++)
		{
			free(command_array[x]);
			command_array[x] = NULL;
		}

		/* read from the file descriptor int to buff */
		bytes_to_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_to_read == 0)
			return (-1);

		/* split lines for \n or ; */
		x = 0;
		do	{
			command_array[x] = str_duplicate(_strtok(x ? NULL : buff, "\n;"));
			/*checks and splxt for && and || operators*/
			x = _checks_all_logic_ops(command_array, x, array_of_operators);
		} while (command_array[x++]);
	}

	/*obtains the next command (command 0) and remove it for the array*/
	data->input_line = command_array[0];
	for (x = 0; command_array[x]; x++)
	{
		command_array[x] = command_array[x + 1];
		array_of_operators[x] = array_of_operators[x + 1];
	}

	return (str_length(data->input_line));
}

/**
 * _check_logic_ops - checks and split for && and || operators
 * @command_array: array of the commands.
 * @x: index in the command_array to be checked
 * @array_of_operators: array of the logical
 * operators for each previous command
 * Return: index of the last command in array.
 */
int _checks_all_logic_ops(char *command_array[], int x, char array_of_operators[])
{
	char *temp = NULL;
	int y;

	/* checks for the & char in the command lxne*/
	for (y = 0; command_array[x] != NULL && command_array[x][y]; y++)
	{
		if (command_array[x][y] == '&' && command_array[x][y + 1] == '&')
		{
			/* split the line when chars && was found */
			temp = command_array[x];
			command_array[x][y] = '\0';
			command_array[x] = str_duplicate(command_array[x]);
			command_array[x + 1] = str_duplicate(temp + y + 2);
			x++;
			array_of_operators[x] = '&';
			free(temp);
			y = 0;
		}
		if (command_array[x][y] == '|' && command_array[x][y + 1] == '|')
		{
			/* split the line when chars || was found */
			temp = command_array[x];
			command_array[x][y] = '\0';
			command_array[x] = str_duplicate(command_array[x]);
			command_array[x + 1] = str_duplicate(temp + y + 2);
			x++;
			array_of_operators[x] = '|';
			free(temp);
			y = 0;
		}
	}
	return (x);
}
