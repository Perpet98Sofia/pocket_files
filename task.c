#include "main.h"

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
	size_t buf_size = 0, command_length;
	char *args[] = { "", NULL }, *command = NULL;
	int is_interact = (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));

	while (1)
	{
		if (is_interact)
			printf("$ "); /* Display the prompt */
		fflush(stdout);
		if (getline(&command, &buf_size, stdin) == -1)
		{
			if (command != NULL)
				free(command);
			break; /* Handle Ctrl+D (End of file) */
		}
		command_length = strlen(command);
		command[command_length - 1] = '\0';
		execute(command, args);
	}

	return (0);
}

/**
 * execute - executes command
 * @command: command to execute
 * @args: command arguments
 *
 * Return: void
 */
void execute(char *command, char **args)
{
	pid_t pid;
	int status;

	if (access(command, X_OK) == 0)
	{
		pid = fork();  /* Fork a new process */
		if (pid == 0)
		{
			args[0] = command;
			execve(command, args, NULL);
			perror("./shell");
			free(command);
			exit(1);
		}
		else if (pid > 0)
			waitpid(pid, &status, 0); /* Wait for the child process to complete */
		else
			perror("Fork failed");
	}
	else
		perror("./shell");
}
