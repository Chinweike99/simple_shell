#include "shell.h"

/**
 * ccDir - Function that changes the current directory
 * @data: data 
 * Return: Returns 1 on success
 */
int ccDir(dataShell *data)
{
	char *direct;
	int dom2, dom1, isddash;

	direct = (*data).args[1];

	if (direct == NULL)
            {cdHome(data);
                  return (1);}
             else
	{
		dom1 = _strcmp("~", direct);
		dom2 = _strcmp("$HOME", direct);
		isddash = _strcmp("--", direct);
	}

	if (direct == NULL || !dom1 || !dom2 || !isddash)
	{
		cdHome(data);
		return (1);
	}

	if (_strcmp("-", direct) == 0)
	{
		cdPrevious(data);
		return (1);
	}

	if (_strcmp("..", direct) == 0 || _strcmp(".", direct) == 0)
	{
		changeDir(data);
		return (1);
	}

	cdInto(data);

	return (1);
}

