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

/**
 * get_builtin - builtins that pass the command in the arg
 * @cmd: command
 * Return: function of the builtin command
 */
int get_builtin(char *cmd, char **args, char *env[])
{
	builtin_t builtins[] = {
		{ "env", builtin_env },
		{ "exit", built_in_exit },
		{ "setenv", built_in_setenv },
		{ "unsetenv", built_in_unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtins[i].name; i++)
	{
		if (_strcmp(builtins[i].name, args[0]) == 0)
			return (builtins[i].f(args, env));
	}

	return (execute(cmd, args, env));
}

/**
 * builtin_env - env built-in
 * @env: Environment
 *
 * Return: Always 0
 */
int builtin_env(char **args, char *env[])
{
	int i;

	UNUSED(args);

	for (i = 0; env[i]; i++)
		printf("%s\n", env[i]);

	return (0);
}

int built_in_setenv(char **args, char *env[])
{
	UNUSED(args);
	UNUSED(env);
	return (0);
}

int built_in_unsetenv(char **args, char *env[])
{
	UNUSED(args);
	UNUSED(env);
	return (0);
}

int cd_shell(char **args, char *env[])
{
	UNUSED(args);
	UNUSED(env);
	return (0);
}

int get_help(char **args, char *env[])
{
	UNUSED(args);
	UNUSED(env);
	return (0);
}

/**
 * is_digit - checks if a character is a digit
 * @c: the character to check
 *
 * Return: 1 if the character is a digit
*/
int is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/**
 * is_digit - checks if a string is a number
 * @c: string to check
 *
 * Return: 0 if the string is a number
*/
int is_number(char *c)
{
	int what = 0;

	while (*c)
	{
		what += is_digit(*c);
		c++;
	}

	return (what);
}
