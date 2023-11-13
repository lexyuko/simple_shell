#include "shell.h"

/**
 * main - Initialize program variables and start the shell.
 * @argc: Number of command line arguments.
 * @argv: Command line arguments.
 * @env: Environment variables.
 * Return: 0 on success.
 */
int main(int argc, char *argv[], char *env[]) {
    ProgramData dataStruct = {NULL}, *data = &dataStruct;
    char *prompt = "";

    initializeData(data, argc, argv, env);

    signal(SIGINT, handleCtrlC);

    if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1) {
        /* We are in the terminal, interactive mode */
        errno = 2; /* ???? */
        prompt = PROMPT_MSG;
    }

    errno = 0;
    sisifo(prompt, data);

    return 0;
}

/**
 * handleCtrlC - Handle SIGINT (Ctrl+C) signal.
 * @signal: Signal value (UNUSED).
 */
void handleCtrlC(int signal UNUSED) {
    _print("\n");
    _print(PROMPT_MSG);
}

/**
 * initializeData - Initialize the structure with program information.
 * @data: Pointer to the program's data structure.
 * @argc: Number of command line arguments.
 * @argv: Array of arguments passed to the program.
 * @env: Environment passed to the program.
 */
void initializeData(ProgramData *data, int argc, char *argv[], char **env) {
    int i = 0;

    data->programName = argv[0];
    data->inputLine = NULL;
    data->commandName = NULL;
    data->execCounter = 0;

    /* Define the file descriptor to be read */
    if (argc == 1) {
        data->fileDescriptor = STDIN_FILENO;
    } else {
        data->fileDescriptor = open(argv[1], O_RDONLY);
        if (data->fileDescriptor == -1) {
            _printe(data->programName);
            _printe(": 0: Can't open ");
            _printe(argv[1]);
            _printe("\n");
            exit(127);
        }
    }

    data->tokens = NULL;

    data->env = malloc(sizeof(char *) * 50);
    if (env) {
        for (; env[i]; i++) {
            data->env[i] = strDuplicate(env[i]);
        }
    }
    data->env[i] = NULL;
    env = data->env;

    data->aliasList = malloc(sizeof(char *) * 20);
    for (i = 0; i < 20; i++) {
        data->aliasList[i] = NULL;
    }
}

/**
 * sisifo - Infinite loop that shows the prompt and handles user input.
 * @prompt: Prompt to be printed.
 * @data: Program data structure.
 */
void sisifo(char *prompt, ProgramData *data) {
    int errorCode = 0, stringLen = 0;

    while (++(data->execCounter)) {
        _print(prompt);
        errorCode = stringLen = _getline(data);

        if (errorCode == EOF) {
            freeAllData(data);
            exit(errno); /* If EOF is the first character of the string, exit */
        }

        if (stringLen >= 1) {
            expandAlias(data);
            expandVariables(data);
            tokenize(data);

            if (data->tokens[0]) {
                /* If text is given to the prompt, execute */
                errorCode = execute(data);
                if (errorCode != 0) {
                    _printError(errorCode, data);
                }
            }

            freeRecurrentData(data);
        }
    }
}
