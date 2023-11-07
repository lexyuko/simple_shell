#include  "shell.h"

/**
 * get_line - reads a line from the prompt.
 * @data: structure for the  shells data
 *
 * Return: counting bytes
 */

int get_line(program_data *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *commands_array[10] = {NULL};
	static char operator_array[10] = {'\0'};
	ssize_t read_byte, x = 0;

	/*Chech if there are no more commands in the array*/
	/* Also, validate the logical operators*/
	if (commands_array[0] || (operator_array[0] == '&' && error_no != 0) ||
			(operator_array[0] == '|' && error_no == 0))
	{
		/* if the  array exists free its allocated memory*/
		while (commands_arrary[x] != NULL)
		{
			free(commands_array[x]);
			commands_array[x] = NULL;
			x++;
		}
	}
	/* Read data from the file descriptor 'int' into the 'buf' buffer. */
	read_byte = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
	if (read_byte == 0)
		return (-1);
	/* seperate lines for \n or ; */
	x = 0;
	while (commands_array[x])
	{
		commands_array[x] = duplicate_str(_strtok(x ? NULL : buff, " \n;"));
		/* checks for && and || operations */
		x = logic_ops_checks(commands_array, x operator_array);
		x++;
	}
	/* obtains the next command and removes it form the array */
	data->line_input = commands_array[0];
	for (x = 0; commands_array[x]; x++)
	{
		commands_array[x] = commands_array[x + 1];
		operator_array[x] = operator_array[x + 1];
	}
	return (str_length(data->line_input));
}

/**
 * logic_ops_checks - checks for && and || operations
 * @commands_array: command array
 * @x: index in commands_array being checked
 * @operator_array: array of logical operations for the previous commands
 *
 * Return: index of the last command in commands_array
 **/

int logic_ops_checks(char *commands_array[], int x, char operator_array[])
{
	char *tmp = NULL;
	int y;

	/* checks for char in command line*/
	y = 0;
	while (commands_array[x] != NULL && commands_array[x][y])
	{
		if (commands_array[x][y] == '&' && commands_array[x][y + 1] == '&')
		{
			/*seperates the line when "&&" is found */

			char *tmp commands_array[x];
			commands_array[x][y] = '\0';
			commands_array[x] = duplicate_str(commands_array[x]);
			commands_array[x + 1] = duplicate_str(tmp + y + 2);
			operator_array[x] == '&';
			x++;
			free(tmp);
			y = 0;
		}
		y++;
		if (commands_array[x][y] == '|' && commands_arra[x][y + 1] == '|')
		{
			/* seperate the line when || is found */
			tmp = commands_array[x];
			commands_array[x][y] = '\0';
			commands_array[x] = duplicate_str(commands_array[x]);
			commands_array[x + 1] = duplicate_str(tmp + y + 2);
			x++;
			operator_array[x] = '|';
			free(tmp);
			y = 0;
		}
	}
	return (x);
}
