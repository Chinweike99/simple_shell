#include "shell.h"

/**
 * _strdup - a function that duplicates a string.
 * @str: string to be duplicated
 * Return: duplicated string
 */
char *_strdup(const char *d)
{
	char *newStr;
	size_t len;

	len = _strlen(d);
	newStr = malloc(sizeof(char) * (len + 1));
	if (newStr == NULL)
		return (NULL);
	_memcpy(newStr, d, len + 1);
	return (newStr);
}

/**
 * _strlen - Returns the lenght of a string.
 * @str: Type char pointer
 * Return: Always 0.
 */
int _strlen(const char *d)
{
	int len = 0;

	for (; d[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * cmpChars - compare chars of strings
 * @str: the input string input string.
 * @delim: the delimiter.
 *
 * Return: 1 if same, 0 if not.
 */
int cmpChars(char str[], const char *delim)
{
	unsigned int a, b = 0, c;

	for (a = 0, c = 0; str[a]; a++)
	{
		for (; delim[b]; b++)
		{
			if (str[a] == delim[b])
			{
				c++;
				break;
			}
		}
	}
	if (a == c)
		return (1);
	return (0);
}

