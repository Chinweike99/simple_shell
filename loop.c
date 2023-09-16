#include "shell.h"

/**
 * noComment - a function that removes comments from the input
 *
 * @inStr: input string
 * Return: input without comments
 */
char *noComment(char *inStr)
{
	int a = 0, upto;

	upto = 0;
	for (; inStr[a]; a++)
	{
		if (inStr[a] == '#')
		{
			if (a == 0)
			{
				free(inStr);
				return (NULL);
			}

			if (inStr[a - 1] == ' ' || inStr[a - 1] == '\t' || inStr[a - 1] == ';')
				upto = a;
		}
	}

	if (upto != 0)
	{
		inStr = _realloc(inStr, a, upto + 1);
		inStr[upto] = '\0';
	}

	return (inStr);
}

/**
 * shellLoop - Loop of shell
 * @data: element of the struct
 *
 * Return: no return.
 */
void shellLoop(dataShell *data)
{
	int iterate, eof;
	char *str;

	iterate = 1;
	while (iterate == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		str = readLine(&eof);
		if (eof != -1)
		{
			str = noComment(str);
			if (str == NULL)
				continue;

			if (checkSyntax(data, str) == 1)
			{
				(*data).stat = 2;
				free(str);
				continue;
			}
			str = repVar(str, data);
			iterate = splitCmd(data, str);
			(*data).count += 1;
			free(str);
		}
		else
		{
			iterate = 0;
			free(str);
		}
	}
}

