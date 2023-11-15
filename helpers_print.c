#include "shell.h"

/**
 * _print - Writes an array of characters to the standard output.
 * @string: Pointer to the array of characters.
 * Return: The number of bytes written.
 * On error, -1 is returned, and errno is set accordingly.
 */

int _print(char *string)
{
    ssize_t result = write(STDOUT_FILENO, string, str_length(string));
    return result;
}
/**
 * _printe - Writes an array of characters to the standard error.
 * @string: Pointer to the array of characters.
 * Return: The number of bytes written.
 * On error, -1 is returned, and errno is set accordingly.
 */
int _printe(char *string)
{
    ssize_t result = write(STDERR_FILENO, string, str_length(string));
    return result;
}

/**
 * _print_error - Writes an array of characters to the standard error.
 * @data: A pointer to the program's data.
 * @errorcode: Error code to print.
 * Return: The number of bytes written.
 * On error, -1 is returned, and errno is set accordingly.
 */
int _print_error(int errorcode, data_of_program *data)
{
    char n_as_string[10] = {'\0'};

    long_to_string((long)data->exec_counter, n_as_string, 10);

    switch (errorcode)
    {
    case 2:
    case 3:
        _printe(data->program_name);
        _printe(": ");
        _printe(n_as_string);
        _printe(": ");
        _printe(data->tokens[0]);
        if (errorcode == 2)
            _printe(": Illegal number: ");
        else
            _printe(": can't cd to ");
        _printe(data->tokens[1]);
        _printe("\n");
        break;

    case 127:
        _printe(data->program_name);
        _printe(": ");
        _printe(n_as_string);
        _printe(": ");
        _printe(data->command_name);
        _printe(": not found\n");
        break;

    case 126:
        _printe(data->program_name);
        _printe(": ");
        _printe(n_as_string);
        _printe(": ");
        _printe(data->command_name);
        _printe(": Permission denied\n");
        break;

        // Add more cases if needed

    default:
        // Handle other error codes
        break;
    }

    return (0);
}