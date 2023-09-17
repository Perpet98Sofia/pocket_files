#include "main.h"

/**
 * strcat_cd - function that concatenates the message for cd error
 * @args: list of arguments
 * @cmd: name or command
 * @msg: message to print
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *strcat_cd(char **args, char *cmd, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	_strcpy(error, cmd);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, msg);
	
	if (args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(error, args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - error message for cd command in get_cd
 * @counter: count of commands or operations
 * @args: list of arguments
 * @cmd: name or command associated with the error
 * Return: Error message
 */

char *error_get_cd(char **args, char *cmd, int counter)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = aux_itoa(counter);

	if (args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(args[1]);
	}

	length = _strlen(cmd) + _strlen(args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == NULL) /* Change error check from '0' to 'NULL' for clarity. */
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cd(args, cmd, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * error_not_found - generic error message for command not found
 * @counter: count of commands or operations
 * @args: list of arguments
 * @cmd: shell name
 * Return: Error message
 */
char *error_not_found(char **args, char *cmd, int counter)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(counter);
	length = _strlen(cmd) + _strlen(ver_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));

	if (error == NULL) /* Use NULL for clarity instead of '0' */
	{
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, "./hsh");
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");

	free(ver_str);

	return (error);
}

/**
 * error_exit_shell - generic error message for exit in get_exit
 * @counter:  a command or operation counter
 * @args:  list of arguments. Specifically, args[0] and args[1] are being used
 * @cmd: shell name
 * Return: Error message
 */
char *error_exit_shell(char **args, char *cmd, int counter)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(counter);
	length = _strlen(cmd) + _strlen(ver_str) + _strlen(args[0]) + _strlen(args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));

	if (error == NULL) /* Using NULL for clarity instead of '0'*/
	{
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, cmd);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, args[1]);
	_strcat(error, "\n\0");

	free(ver_str);

	return (error);
}

/**
 * error_env - error message for env in get_env
 * @counter: command or operation counter
 * @args: list of arguments, specifically args[0]
 * @cmd: shell name
 * Return: error message.
 */
char *error_env(char **args, char *cmd, int counter)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = aux_itoa(counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(cmd) + _strlen(ver_str) + _strlen(args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));

	if (error == NULL)  /* Using NULL for clarity instead of '0'. */
	{
		/* If error is NULL (malloc failed), there's no need to free it. */
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, cmd);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");

	free(ver_str);

	return (error);
}

/**
 * error_path_126 - error message for path and failure denied permission
 * @counter: command or operation counte
 * @args: list of arguments, specifically args[0]
 * @cmd: shell name
 *
 * Return: The error string.
 */

char *error_path_126(char **args, char *cmd, int counter)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = aux_itoa(counter);
	length = _strlen(cmd) + _strlen(ver_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));

	if (error == NULL) /* Using NULL for clarity instead of '0'. */
	{
		/* If error is NULL (malloc failed), there's no need to free it. */
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, cmd);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");

	free(ver_str);

	return (error);
}

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @args: arguements
 * @status: integer status
 * @eval: error value
 *
 * Return: error
 */
int get_error(char **args, int eval, int counter)
{
	char *error = NULL;

	switch (eval)
	{
		case -1:
			error = error_env(args, args[0], counter);
			break;
		case 126:
			error = error_path_126(args, args[0], counter);
			break;
		case 127:
			error = error_not_found(args, args[0], counter);
			break;
		case 2:
			if (_strcmp("exit", args[0]) == 0)
				error = error_exit_shell(args, args[0], counter);
			else if (_strcmp("cd", args[0]) == 0)
				error = error_get_cd(args, args[0], counter);
			break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	return (eval);
}
