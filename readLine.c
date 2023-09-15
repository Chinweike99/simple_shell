#include "shell.h"

/**
 * readLine - reads the input string.
 *
 * @eof: return value of getline function
 * Return: input string
 */
char *readLine(int *eof)
{
	char *str = NULL;
	size_t bufsize = 0;

	*eof = getLine(&str, &bufsize, stdin);

	return (str);
}

