#include "shell.h"

/**
 * printAlias - Print aliases.
 * @data: Structure for program's data.
 * @aliasName: Name of the alias to be printed.
 * Return: 0 if successful, otherwise an error code.
 */
int printAlias(ProgramData *data, const char *aliasName) {
    if (data->aliasList) {
        const size_t aliasNameLength = strlen(aliasName);

        for (size_t i = 0; data->aliasList[i]; i++) {
            const char *currentAlias = data->aliasList[i];

            if (!aliasName || (strncmp(currentAlias, aliasName, aliasNameLength) == 0 && currentAlias[aliasNameLength] == '=')) {
                char *aliasValue = strchr(currentAlias, '=') + 1;
                printf("'%s'='%s'\n", currentAlias, aliasValue);
            }
        }
    }

    return 0;
}

/**
 * getAlias - Get the value of an alias.
 * @data: Structure for program's data.
 * @aliasName: Name of the requested alias.
 * Return: The alias value if found, NULL otherwise.
 */
const char *getAlias(ProgramData *data, const char *aliasName) {
    if (aliasName == NULL || data->aliasList == NULL) {
        return NULL;
    }

    const size_t aliasNameLength = strlen(aliasName);

    for (size_t i = 0; data->aliasList[i]; i++) {
        const char *currentAlias = data->aliasList[i];

        if (strncmp(currentAlias, aliasName, aliasNameLength) == 0 && currentAlias[aliasNameLength] == '=') {
            return currentAlias + aliasNameLength + 1;
        }
    }

    return NULL;
}

/**
 * setAlias - Set or override an alias.
 * @aliasString: Alias to be set in the form (name='value').
 * @data: Structure for program's data.
 * Return: 0 if successful, otherwise an error code.
 */
int setAlias(const char *aliasString, ProgramData *data) {
    if (aliasString == NULL || data->aliasList == NULL) {
        return 1;
    }

    char aliasName[250] = {0};
    const char *aliasValue = strchr(aliasString, '=');

    if (aliasValue == NULL) {
        return 1;
    }

    const ptrdiff_t aliasNameLength = aliasValue - aliasString;
    strncpy(aliasName, aliasString, aliasNameLength);

    for (size_t i = 0; data->aliasList[i]; i++) {
        char *currentAlias = data->aliasList[i];

        if (strncmp(currentAlias, aliasName, aliasNameLength) == 0 && currentAlias[aliasNameLength] == '=') {
            free(data->aliasList[i]);
            data->aliasList[i] = strDuplicate(aliasString);
            return 0;
        }
    }

    data->aliasList[data->aliasCount++] = strDuplicate(aliasString);

    return 0;
}
