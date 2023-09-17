#include "main.h"

/**
 * main - Entry point
 * @ac: Arguments count
 * @av: Arguments
 * @env: Environment
 *
 * Return: Always 0
 */
int main(int ac, char **av, char *env[])
{
	size_t buf_size = 0;
	char *command;
	data_shell data;
	int is_interact = (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO)), i = 0;

	UNUSED(ac);
	UNUSED(av);
	data.counter = 0;
	while (1)
	{
		fflush(stdout);
		if (is_interact)
			printf("$ "); /* Display the prompt */
		if (getline(&command, &buf_size, stdin) == -1)
		{
			if (feof(stdin))
				free(command);
			break; /* Handle Ctrl+D (End of file) */
		}
		if (_strlen(command) == 1)
			continue;
		data.input = _strdup(command);
		data.counter++;
		while (env[i] != NULL)
		{
			data._environ[i] = _strdup(env[i]);
			i++;
		}
		data._environ[i] = NULL;
		split_commands(&data, data.input);
		free(data.input);
	}

	return (0);
}

/**
 * execute - executes command
 * @command: command to execute
 * @args: command arguments
 * @envp: environment
 *
 * Return: 0 for success, -1 for failure
 */
int execute(data_shell command)
{
	pid_t pid;
	int status, found = 0;
	char *exec, *abs_cmd;

	if (access(command.args[0], X_OK) == 0)
		found = 1;
	else
	{
		exec = find_executable(command.args[0], command._environ);
		if (exec)
		{
			found = 1;
			abs_cmd = make_cmd(command.input, exec);
			command.args[0] = _strdup(abs_cmd);
		}
	}
	if (found == 1)
	{
		pid = fork(); /* Fork a new process */
		if (pid == 0)
			return (execve(command.args[0], command.args, command._environ));
		else if (pid > 0) /* Wait for the child process to complete */
			waitpid(pid, &status, 0);
		else
			perror("./hsh: 0");
	}
	else
	{
		command.status = 127;
		get_error(command.args, command.status, command.counter);
	}
	return (0);
}
