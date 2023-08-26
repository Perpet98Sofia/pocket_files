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
	char *args[MAX_ARGS], *command = NULL;
	int is_interact = (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));

	UNUSED(ac);
	UNUSED(av);
	while (1)
	{
		if (is_interact)
			printf("$ "); /* Display the prompt */
		fflush(stdout);
		if (getline(&command, &buf_size, stdin) == -1)
		{
			if (feof(stdin))
				free(command);
			break; /* Handle Ctrl+D (End of file) */
		}
		if (_strlen(command) == 1)
			continue;
		command[_strlen(command) - 1] = '\0';
		execute(command, args, env);
	}

	return (0);
}

/**
 * execute - executes command
 * @command: command to execute
 * @args: command arguments
 * @envp: environment
 *
 * Return: void
 */
void execute(char *command, char **args, char *envp[])
{
	pid_t pid;
	int status, found = 0;
	char *exec, *abs_cmd;

	_split_line(command, args);
	if (access(args[0], X_OK) == 0)
		found = 1;
	else
	{
		exec = find_executable(args[0], envp);
		if (exec)
		{
			found = 1;
			abs_cmd = make_cmd(command, exec);
			args[0] = _strdup(abs_cmd);
		}
	}
	if (found == 1)
	{
		pid = fork();  /* Fork a new process */
		if (pid == 0)
		{
			execve(args[0], args, NULL);
			perror("./shell: 2");
			free(command);
			exit(1);
		}
		else if (pid > 0) /* Wait for the child process to complete */
			waitpid(pid, &status, 0);
		else
			perror("./shell: 0");
	}
	else
		perror("./shell: 1");
}
