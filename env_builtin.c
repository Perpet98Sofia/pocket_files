#include "main.h"

/**
 * built_in_setenv - Function to set an environment variable
 */
int built_in_setenv(char **args, char *env[])
{
	char **end_env = find_end_env(env), *varname = NULL, *value = NULL;
	char **var = env, *new_env;

	divide_string(args[1], &varname, &value);

	for (; var < end_env; var++)
	{
		if (strcmp(*var, varname) == 0)
		{
			*var = realloc(*var, strlen(varname) + strlen(value) + 2);
			strcpy(*var, varname);
			strcat(*var, "=");
			strcat(*var, value);
			return (0);
		}
	}

	/* If the variable name does not exist, create a new entry */
	new_env = malloc(strlen(varname) + strlen(value) + 2);
	if (new_env == NULL)
		return (-1);
	strcpy(new_env, varname);
	strcat(new_env, "=");
	strcat(new_env, value);

	/* Append the new entry to the environment variables */
	end_env = realloc(end_env, sizeof(char *) * (size_t)(sizeof(end_env) + 1));
	end_env[sizeof(end_env) - 1] = new_env;
	return (0);
}

/**
 * _getenv - Function to get the value of an environment variable
 */
char *_getenv(char **args, char *env[])
{
	char **var = env;

	/* Iterate over the environment variables until the end */
	for (; var < find_end_env(env); var++)
	{
		if (strcmp(*env, args[1]) == 0)
			return (*env + strlen(args[1]) + 1);
	}

	return (NULL);
}

/**
 * find_end_env - Recursive function to find the end of the environment variables
*/
char **find_end_env(char *environ[])
{
	char **env_line = environ;

	while (*env_line)
		env_line++;

	return (env_line);
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

/**
 * built_in_unsetenv - Function to unset an environment variable
*/
int built_in_unsetenv(char **args, char *env[])
{
	char **envp = env;
	char **prev = NULL;
	int found = 0;

	while (*envp)
	{
		if (strcmp(*envp, args[1]) == 0)
		{
			if (prev)
				*prev = *envp;
			free(*envp);
			*envp = NULL;
			found = 1;
			break;
		}
		prev = envp;
		envp++;
	}

	return found;
}
