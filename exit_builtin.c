#include "main.h"

/**
 * built_in_exit - exit built-in
 * @args: param
 *
 * Return: 0 Success, -1 otherwise
 */
int built_in_exit(char **args, char *env[])
{
	int status;

	UNUSED(env);

	if (args[1])
	{
		status = atoi(args[1]);
		if (status != 0)
			exit(status);
		else
		{
			perror("exit");
			return (-1);
		}
	}
	else
		exit(0);
	return (0);
}
