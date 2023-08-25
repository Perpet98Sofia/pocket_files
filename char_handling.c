#include "main.h"

/**
 * _strncmp - compares two strings on n characters
 * @s1: char*
 * @s2: char*
 * @n: number
 * Return: 0 (s1 == s2 || c == n) -1 otherwise
 */
int _strncmp(char *s1, char *s2, int n)
{
	int c = 0;

	while (((s1[c] != '\0') && (s2[c] != '\0')) && s1[c] == s2[c])
		c++;

	if (c == n)
		return (0);
	else if (s1[c] == s2[c])
		return (0);
	else
		return (-1);
}

/**
 * _strdup - return a copy of the string given as a parameter
 * @str: the string given
 *
 * Return: a pointer
 */
char *_strdup(char *str)
{
	int n = 0, i;
	char *buffer;

	if (str == NULL)
		return (NULL);
	while (str[n] != '\0')
		n++;

	buffer = (char *)malloc((n * sizeof(char)) + 1);
	if (buffer == NULL)
		return (NULL);

	for (i = 0; i < n; i++)
		buffer[i] = str[i];
	buffer[n] = '\0';

	return (buffer);
}

/**
 * _strcmp - compares two strings
 * @s1: char*
 * @s2: char*
 *
 * Return: 0 (s1 == s2 || c == n) -1 otherwise
 */
int _strcmp(char *s1, char *s2)
{
	int c = 0;

	while (((s1[c] != '\0') && (s2[c] != '\0')) && s1[c] == s2[c])
		c++;

	if (s1[c] == s2[c])
		return (0);
	else
		return (-1);
}
