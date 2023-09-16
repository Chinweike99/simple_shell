#include "shell.h"

/**
 * _strcat - concatenate two strings
 * @dest: string one
 * @src: string two
 * Return: the dest
 */
char *_strcat(char *dest, const char *src)
{
	int a = 0;
	int b = 0;

	for (; dest[a] != '\0'; a++)
		;

	for (; src[b] != '\0'; b++)
	{
		dest[a] = src[b];
		a++;
	}

	dest[a] = '\0';
	return (dest);
}
/**
 * *_strcpy - Copies a string.
 * @dest: the new string
 * @src: string to be copied
 * Return: the dest.
 */
char *_strcpy(char *dest, char *src)
{

	size_t i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return (dest);
}
/**
 * _strcmp - Function that compares two strings.
 * @str1: first string to b  compared
 * @str2: second string to be compared
 * Return: Always 0.
 */
int _strcmp(char *str1, char *str2)
{
	int a;

	for (a = 0; str1[a] == str2[a] && str1[a]; a++)
		;

	if (str1[a] > str2[a])
		return (1);
	if (str1[a] < str2[a])
		return (-1);
	return (0);
}
/**
 * _strchr - locates a character in a string,
 * @str: the string.
 * @c: character.
 * Return: the new character followed by a new line
 */
char *_strchr(char *str, char c)
{
	unsigned int a = 0;

	for (; *(str + a) != '\0'; a++)
		if (*(str + a) == c)
			return (str + a);
	if (*(str + a) == c)
		return (str + a);
	return ('\0');
}
/**
 * _strspn - a function that gets the length of a string.
 * @str: initial segment.
 * @accbytes: accepted bytes.
 * Return: the length
 */
int _strspn(char *str, char *accbytes)
{
	int a, b, bool;

	for (a = 0; *(str + a) != '\0'; a++)
	{
		bool = 1;
		for (b = 0; *(accbytes + b) != '\0'; b++)
		{
			if (*(str + a) == *(accbytes + b))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (a);
}

