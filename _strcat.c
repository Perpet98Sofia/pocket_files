#include "main.h"

/**
 * _strcat - concatenates two strings
 * @dest: Destination
 * @src: Source
 * Return: Pointer to the resulting string dest
 */
char *_strcat(char *dest, char *src)
{
	char *ptr = dest;
	int count = 0, k;

	while (dest[count] != '\0')
	{
		count++;
	}

	k = 0;

	while (src[k] != '\0')
	{
		dest[count] = src[k];
		count++;
		k++;
	}

	dest[count] = '\0';

	return (ptr);
}
