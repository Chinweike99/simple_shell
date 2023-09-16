#include "shell.h"

/**
 * _strtok - tokenizes a string.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splitted.
 */
char *_strtok(char str[], const char *delim)
{
	static char *split, *strEnd;
	char *strStart;
	unsigned int a, bool;

	if (str != NULL)
	{
		if (cmpChars(str, delim))
			return (NULL);
		split = str;
		a = _strlen(str);
		strEnd = &str[a];
	}
	strStart = split;
	if (strStart == strEnd)
		return (NULL);

	for (bool = 0; *split; split++)
	{

		if (split != strStart)
			if (*split && *(split - 1) == '\0')
				break;

		for (a = 0; delim[a]; a++)
		{
			if (*split == delim[a])
			{
				*split = '\0';
				if (split == strStart)
					strStart++;
				break;
			}
		}
		if (bool == 0 && *split)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (strStart);
}

/**
 * _isdigit - defines if string passed is a number
 *
 * @str: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int _isdigit(const char *d)
{
	unsigned int a = 0;

	for (; d[a]; a++)
	{
		if (d[a] < 48 || d[a] > 57)
			return (0);
	}
	return (1);
}
/**
 * revString - reverses a string.
 * @str: input string.
 * Return: returns nothing.
 */
void revString(char *d)
{
	int count = 0, a, b;
	char *strng, temp;

	while (count >= 0)
	{
		if (d[count] == '\0')
			break;
		count++;
	}
	strng = d;

	for (a = 0; a < (count - 1); a++)
	{
		for (b = a + 1; b > 0; b--)
		{
			temp = *(strng + b);
			*(strng + b) = *(strng + (b - 1));
			*(strng + (b - 1)) = temp;
		}
	}
}

