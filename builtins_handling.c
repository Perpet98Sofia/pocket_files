#include "main.h"

/**
 * get_builtin - builtins that pass the command in the arg
 * @cmd: command
 * Return: function of the builtin command
 */
int get_builtin(char *cmd, char **args, char *env[])
{
	builtin_t builtins[] = {
		{ "env", builtin_env },  { "help", get_help },
		{ "exit", built_in_exit }, { "cd", cd_shell },
		{ "setenv", built_in_setenv },
		{ "unsetenv", built_in_unsetenv },
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
