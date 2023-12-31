#include "main.h"
/**
 * free_double_ptr - free malloced arrays
 * @str: array of strings
 */
void free_double_ptr(char **str)
{
	int i = 0;

	while (str[i] != NULL)
	{
		if (str[i])
			free(str[i]);
		i++;
	}
}
