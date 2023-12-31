#include "main.h"

/**
 * built_in_exit - exit built-in
 * @args: param
 *
 * Return: 0 Success, -1 otherwise
 */
int built_in_exit(data_shell command)
{
	int status;

	if (command.args[1])
	{
		status = atoi(command.args[1]);
		if (status != 0)
			exit(status);
		else
		{
			command.status = 2;
			get_error(command.args, command.status, command.counter);
			return (-1);
		}
	}
	else
		exit(0);
	return (0);
}
