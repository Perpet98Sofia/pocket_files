#include "main.h"

/**
 * built_in_exit - exit built-in
 * @args: param
 *
 * Return: void
 */
void built_in_exit(char *args[])
{
	if (strcmp(args[0], "exit") == 0)
		exit(0);

}
