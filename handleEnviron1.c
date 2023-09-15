#include "main.h"

/**
 * cmpName - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmpName(const char *env1, const char *ename)
{
	int x;

	for (x = 0; env1[x] != '='; x++)
	{
		if (env[x] != ename[i])
		{
			return (0);
		}
	}

	return (x + 1);
}

/**
 * _getEnv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *getEnv(const char *ename, char **_environ)
{
	char *ptrenv;
	int x, chn;

	/* Initialize ptr_env value */
	ptrenv = NULL;
	chn = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (x = 0; _environ[x]; x++)
	{
		/* If name and env are equal */
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
 * envVar - prints the evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
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

