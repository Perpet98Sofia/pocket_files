#include "main.h"

/**
 * _split_line - split a line into strings separated
 *
 * @line: the line to split
 * @argv: the variable where the strings will be stored
 *
 * Return: void
 */
void _split_line(char *line, char *argv[])
{
	int i = 0;

	argv[i] = strtok(line, " \n");
	while (argv[i] != NULL)
	{
		i++;
		argv[i] = strtok(NULL, "\n");
	}
	argv[i] = NULL;
}
