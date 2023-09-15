#include "shell.h"

/**
 * cmpName - Function that compares variable
 * names and names passed.
 * @env1: variable environment name
 * @ename: name passed
 * Return: 0 if not equal. different value if they are.
 */
int cmpName(const char *env1, const char *ename)
{
	int x;

	x = 0;
	while (env1[x] != '=')
	{
		if (env1[x] != ename[x])
			return (0);
		x++;
	}
	return (x + 1);
}

/**
 * getEnv - Function to get environment variable
 * @ename: the environment variabl ename
 * @_environ: environment variable
 * Return: variable value of envionment if found. else, returns NULL.
 */
char *getEnv(const char *ename, char **_environ)
{
	char *ptrenv;
	int x, chn;

	ptrenv = NULL;
	chn = 0;
	for (x = 0; _environ[x]; x++)
	{
		chn = cmpName(_environ[x], ename);
		if (chn)
		{
			ptrenv = _environ[x];
			break;
		}
	}

	return (ptrenv + chn);
}

/**
 * envVar - Function that prints the evironment variables
 * @data: data relevant.
 * Return: Return 1 on success.
 */
int envVar(dataShell *data)
{
	int x, y;

	for (x = 0; (*data)._environ[x]; i++)
	{

		for (y = 0; data->_environ[x][y]; y++)
			;

		write(STDOUT_FILENO, (*data)._environ[x], y);
		write(STDOUT_FILENO, "\n", 1);
	}
	(*data).status = 0;

	return (1);
}

