#include "main.h"

/**
 * find_cmd - Finds the main command in a string
 * @buffer: String to search in
 *
 * Return: The command found
 */
char *find_cmd(const char *buffer)
{
	int len = strlen(buffer), i = 0;
	char *cmd;

	cmd = malloc(len + 1);
	if (cmd == NULL)
		return (NULL);
	while (*buffer && *buffer != ' ')
	{
		cmd[i] = *buffer;
		buffer++;
		i++;
	}
	cmd[i] = '\0';

	return (cmd);
}

/**
 * find_executable - Finds the executable
 * @command: Parameter
 * @envp: Environment
 *
 * Return: The executable if found, NULL otherwise
 */
char *find_executable(const char *command, char **envp)
{
	char *path_env = NULL, *token, *full_path = NULL;
	size_t token_len = 0, command_len = 0;
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break;
		}
	}

	if (path_env)
	{
		token = strtok(strdup(path_env), ":");
		while (token)
		{
			token_len = strlen(token);
			command_len = strlen(command);
			full_path = malloc(token_len + command_len + 2);
			if (full_path)
			{
				strcpy(full_path, token);
				full_path[token_len] = '/';
				strcpy(full_path + token_len + 1, command);
				full_path[token_len + command_len + 1] = '\0';
				if (access(full_path, X_OK) == 0)
					return (full_path);
				free(full_path);
			}
			token = strtok(NULL, ":");
		}
		free(token);
	}

	return (NULL);
}

/**
 * make_cmd - Rebuilds the command w/ the executable and all argumets enterred
 * @entry: The input
 * @exec: The executable
 *
 * Return: The command built n char*
 */
char *make_cmd(char *entry, char *exec)
{
	int i = 0, j = 0;
	char *arg, *res;

	res = malloc(sizeof(char) * MAX_COMMAND_LENGTH);
	if (res == NULL)
		return (NULL);
	arg = strrchr(entry, ' ');
	while (exec[i])
	{
		res[i] = exec[i];
		i++;
	}
	if (arg)
	{
		while (arg[j])
		{
			res[i + j] = arg[j];
			j++;
		}
	}
	res[i + j] = '\0';

	return (res);
}
