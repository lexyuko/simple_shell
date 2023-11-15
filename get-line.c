#include "shell.h"

#define MAX_COMMANDS 10
#define MAX_OPERATORS 10

/**
 * readCommandline- read one line from the prompt.
 * @data: struct for the program's data
 *
 * Return: reading counting bytes.
 */
int readCommandLine(data_of_program *data);
void freeCommandArray(char *commandArray[], int size);
int parseAndSplitCommands(char *commandArray[], char operatorArray[], const char buffer[]);
void shiftArrayElements(char *commandArray[], char operatorArray[], int size);
int findLogicalOperators(char *command);

int readCommandLine(data_of_program *data)
{
    char buffer[BUFFER_SIZE] = {'\0'};
    char *commandArray[MAX_COMMANDS] = {NULL};
    char operatorArray[MAX_OPERATORS] = {'\0'};
    ssize_t bytesRead;
    int x = 0;

    if (commandArray[0] || (operatorArray[0] == '&' && data->errorNo != 0) ||
        (operatorArray[0] == '|' && data->errorNo == 0))
    {
        freeCommandArray(commandArray, MAX_COMMANDS);
    }

    bytesRead = read(data->file_descriptor, buffer, BUFFER_SIZE - 1);
    if (bytesRead == 0)
    {
        return -1;
    }

    x = parseAndSplitCommands(commandArray, operatorArray, buffer);

    data->line_input = commandArray[0];
    shiftArrayElements(commandArray, operatorArray, MAX_COMMANDS);

    return strLength(data->line_input);
}

void freeCommandArray(char *commandArray[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (commandArray[i] != NULL)
        {
            free(commandArray[i]);
            commandArray[i] = NULL;
        }
    }
}

int parseAndSplitCommands(char *commandArray[], char operatorArray[], const char buffer[])
{
    int x = 0;
    char *token;

    // Tokenize the input buffer
    token = strtok(buffer, " \n;");
    while (token != NULL)
    {
        commandArray[x] = duplicateStr(token);
        operatorArray[x] = findLogicalOperators(commandArray[x]);
        token = strtok(NULL, " \n;");
        x++;
    }

    return x;
}

int findLogicalOperators(char *command)
{
    int i = 0;
    while (command[i] != '\0')
    {
        if (command[i] == '&' && command[i + 1] == '&')
        {
            return '&';
        }
        else if (command[i] == '|' && command[i + 1] == '|')
        {
            return '|';
        }
        i++;
    }
    return '\0';
}

void shiftArrayElements(char *commandArray[], char operatorArray[], int size)
{
    for (int i = 0; i < size; i++)
    {
        commandArray[i] = commandArray[i + 1];
        operatorArray[i] = operatorArray[i + 1];
    }
}
