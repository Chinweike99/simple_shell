#include "main.h"

/**
 * charRepeated - Function that counts char repeated
 * @str: The input string
 * @x: index
 * Return: repetitions
 */
int charRepeated(char *str, int x)
{
	if (*(str - 1) == *str)
		return (charRepeated(str - 1, x + 1));

	return (x);
}

/**
 * findError - Function that finds errors in synrax
 * @str: input string
 * @x: The index
 * @last: The last char read
 * Return: Return 0 on success
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
 * findChar - Function that finds first char index
 * @str: the input string
 * @x: index
 * Return: 1 on no errors and 0 in other case.
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
 * printError - Function to prints when a syntax error occurs
 * @data: data struct
 * @str: input string
 * @x: index for the error
 * @bol: this controls the msg error
 * Return: nothing
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
 * checkSyntax - function check and print a syntax error
 * @data: data structure
 * @str: input string
 * Return: 1 on error. 0 on no case
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

