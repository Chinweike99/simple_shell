#include "shell.h"

/**
 * getLen - a function that gets the length of a number.
 * @m: the integer number.
 * Return: Length of a number.
 */
int getLen(int m)
{
	unsigned int n1;
	int len = 1;

	if (m < 0)
	{
		len++;
		n1 = m * -1;
	}
	else
	{
		n1 = m;
	}
	while (n1 > 9)
	{
		len++;
		n1 = n1 / 10;
	}

	return (len);
}
/**
 * _itoa - function converts int to string.
 * @m: type int number
 * Return: String.
 */
char *_itoa(int m)
{
	unsigned int n1;
	int len = getLen(m);
	char *buff;

	buff = malloc(sizeof(char) * (len + 1));
	if (buff == 0)
		return (NULL);

	*(buff + len) = '\0';

	if (m < 0)
	{
		n1 = m * -1;
		buff[0] = '-';
	}
	else
	{
		n1 = m;
	}

	len--;
	do {
		*(buff + len) = (n1 % 10) + '0';
		n1 = n1 / 10;
		len--;
	}
	while (n1 > 0)
		;
	return (buff);
}

/**
 * _atoi - a function that converts a string to an integer.
 * @str: the string.
 * Return: integer.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, rc = 0, lp = 1, m = 1, a;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			lp *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (a = count - size; a < count; a++)
	{
		rc = rc + ((*(s + a) - 48) * m);
		m /= 10;
	}
	return (rc * lp);
}

