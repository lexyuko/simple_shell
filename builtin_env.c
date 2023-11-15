#include "shell.h"

/**
 * handleEqualSign - handle equal sign if present in evnvironment
 * @index: Index of the '=' character.
 * @cpname: Placeholder for the function's description.
 * @data: Structure for the program's data.
 */
void handleEqualSign(size_t index, char *cpname, data_of_program *data)
{
    char *var_copy = str_duplicate(env_get_key(cpname, data));

    if (var_copy != NULL)
    {
        env_set_key(cpname, data->tokens[1] + index + 1, data);
    }

    print_environ(data);

    if (env_get_key(cpname, data) == NULL)
    {
        _print(data->tokens[1]);
        _print("\n");
    }
    else
    {
        env_set_key(cpname, var_copy, data);
        free(var_copy);
    }
}

/**
 * handleNoEqualSign -handle equal sign if not present
 * @data: Structure for the program's data.
 */
void handleNoEqualSign(data_of_program *data)
{
    errno = 2;
    perror(data->command_name);
    errno = 127;
}

/**
 * builtin_env - Displays the environment where the shell is running.
 * @data: Structure for the program's data.
 * Return: Zero on success, or another number if specified in the arguments.
 */
int builtin_env(data_of_program *data)
{
    int i;
    char cpname[50] = {'\0'};

    /* if not arguments */
    if (!data->tokens[1])
    {
        print_environ(data);
    }
    else
    {
        for (size_t i = 0; data->tokens[1][i]; i++)
        {
            if (data->tokens[1][i] == '=')
            {
                // Found '=' character
                handleEqualSign(i, cpname, data);
                return 0;
            }
            cpname[i] = data->tokens[1][i];
        }

        // If '=' is not found
        handleNoEqualSign(data);
        return 0;
    }

    print_environ(data);
    return (0);
}
/**
 * builtin_set_env - Placeholder for the function's description.
 *                   Please provide a detailed explanation.
 * @data: Structure for the program's data.
 * Return: Zero on success, or another number if specified in the arguments.
 */
int builtin_set_env(data_of_program *data)
{
    /* validate args */
    if (!data->tokens[1] || !data->tokens[2])
        return (0);
    if (data->tokens[3])
    {
        errno = IST0BIG;
        perror(data->command_name);
        return (5);
    }

    env_set_key(data->tokens[1], data->tokens[2], data);

    return (0);
}

/**
 * builtin_unset_env - Placeholder for the function's description.
 *                     Please provide a detailed explanation.
 * @data: Structure for the program's data.
 * Return: ...
 */
int builtin_unset_env(data_of_program *data)
{
    /* validate args */
    if (!data->tokens[1])
        return (0);
    if (data->tokens[2])
    {
        errno = IST0BIG;
        perror(data->command_name);
        return (5);
    }
    env_removeKey(data->tokens[1], data);

    return (0);
}