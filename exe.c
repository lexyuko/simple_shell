#include "shell.h"
/**
 * execute - execute a command with its entire path variables.
 * @data: a pointer to the program's data
 * Return: If sucess return zero, otherwise, return -1.
 */
int execute(data_of_program *data)
{
	int status;

	/* Check for built-in programs*/
	if (builtins_list(data) != -1)
		return (0);

	/* Check for program in the file system*/
	if (find_program(data) != 0)
		return (0);

	/* Fork a child process*/
	pid_t child_pid = fork();
	if (child_pid == -1)
	
	{
		perror(data->command_name);
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		/* Child process: execute the program*/
		execve(data->tokens[0], data->tokens, data->env);

		/* If execve fails*/
		perror(data->command_name);
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process: wait for the child and check exit status*/
		waitpid(child_pid, &status, 0);

		if (WIFEXITED(status))
			errno = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			errno = 128 + WTERMSIG(status);
	}

	return (0);
}
