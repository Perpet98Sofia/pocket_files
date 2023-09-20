#include "main.h"

/**
 * free_data - frees data structure
 *
 * @datash: data structure
 * Return: no return
 */
void free_data(data_shell *datash)
{
    unsigned int i;

    for (i = 0; datash->_environ[i]; i++)
    {
        free(datash->_environ[i]);
    }
}

/**
 * set_data - Initialize data structure
 *
 * @datash: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(data_shell *datash, char **av, char **environ)
{
    unsigned int i = 0;

    while (i < MAX_ARGS)
    {
        if (av[i])
            datash->av[i] = av[i];
        i++;
    }
    i = 0;
    while (i < MAX_ARGS)
    {
        datash->args[i] = NULL;
        i++;
    }
    datash->input = NULL;
    datash->status = 0;
    datash->counter = 1;

    for (i = 0; environ[i]; i++)
        ;

    *datash->_environ = malloc(sizeof(char *) * (i + 1));

    for (i = 0; environ[i]; i++)
        datash->_environ[i] = _strdup(environ[i]);

    datash->_environ[i] = NULL;
    datash->pid = getpid();
}
