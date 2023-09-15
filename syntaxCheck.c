Check_syntax_error.

#include "main.h"

/**
 * charRepeated - counts the repetitions of a char
 *
 * @input: input string
 * @i: index
 * Return: repetitions
 */
int charRepeated(char *str, int x)
{
	if (*(str - 1) == *str)
		return (charRepeated(str - 1, x + 1));

	return (x);
}

/**
 * findError - finds syntax errors
 *
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int findError(char *str, int x, char last)
{
	int v;

	v = 0;
	if (*str == '\0')
		return (0);

	if (*str == ' ' || *str == '\t')
		return (findError(str + 1, x + 1, last));

	if (*str == ';')
		if (last == '|' || last == '&' || last == ';')
			return (x);

	if (*str == '|')
	{
		if (last == ';' || last == '&')
			return (x);

		if (last == '|')
		{
			v = charRepeated(str, 0);
			if (v == 0 || v > 1)
				return (x);
		}
	}

	if (*str == '&')
	{
		if (last == ';' || last == '|')
			return (x);

		if (last == '&')
		{
			v = charRepeated(str, 0);
			if (v == 0 || v > 1)
				return (x);
		}
	}

	return (findError(insert + 1, x + 1, *str));
}

/**
 * findChar - finds index of the first char
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int findChar(char *str, int *x)
{

	for (*x = 0; str[*x]; *x += 1)
	{
		if (str[*x] == ' ' || str[*x] == '\t')
			continue;

		if (str[*x] == ';' || str[*x] == '|' || str[*x] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * printError - prints when a syntax error is found
 *
 * @datash: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void printError(dataShell *data, char *str, int x, int bol)
{
	char *fmg, *smg, *tmg, *error, *count;
	int len;

	if (str[x] == ';')
	{
		if (bol == 0)
		fmg = (str[x + 1] == ';' ? ";;" : ";");
		else
			fmg = (str[x - 1] == ';' ? ";;" : ";");
	}

	if (str[x] == '|')
		fmg = (str[x + 1] == '|' ? "||" : "|");

	if (str[x] == '&')
		fmg = (str[x + 1] == '&' ? "&&" : "&");

	smg = ": error: \"";
	tmg = "\" unexpected\n";
	count = _itoa((*data).count);
	len = _strlen((*data).av[0]) + _strlen(count);
	len += _strlen(fmg) + _strlen(smg) + _strlen(tmg) + 2;

	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(count);
		return;
	}
	_strcpy(error, (*data).av[0]);
	_strcat(error, ": ");
	_strcat(error, count);
            _strcat(error, fmg);
	_strcat(error, tmg);
	_strcat(error, smg);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, len);
	free(error);
	free(count);
}

/**
 * checkSyntax - intermediate function to
 * find and print a syntax error
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int checkSyntax(dataShell *data, char *str)
{
	int start = 0;
	int char1 = 0;
	int x = 0;

	char1 = findChar(str, &start);
	if (char1 == -1)
	{
		printError(data, str, start, 0);
		return (1);
	}

	i = findError(str + start, 0, *(str + start));
	if (x != 0)
	{
		printError(data, str, start + x, 1);
		return (1);
	}

	return (0);
}

