#include "shell.h"

/**
 * freeData - frees data structure
 *
 * @data: data structure
 * Return: no return
 */
void freeData(dataShell *data)
{
	unsigned int a = 0;

	for (; (*data)._environ[a]; a++)
	{
		free((*data)._environ[a]);
	}

	free((*data)._environ);
	free((*data).pid);
}

/**
 * setData - Initialize data structure
 *
 * @data: data structure
 * @av: argument vector
 * Return: no return
 */
void setData(dataShell *data, char **av)
{
	unsigned int a;

	(*data).av = av;
	(*data).str = NULL;
	(*data).args = NULL;
	(*data).stat = 0;
	(*data).count = 1;

	for (a = 0; environ[a]; a++)
		;

	(*data)._environ = malloc(sizeof(char *) * (a + 1));

	for (a = 0; environ[a]; a++)
	{
		(*data)._environ[a] = _strdup(environ[a]);
	}

	(*data)._environ[a] = NULL;
	(*data).pid = _itoa(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	dataShell data;
	(void) ac;

	signal(SIGINT, _callp);
	setData(&data, av);
	shellLoop(&data);
	freeData(&data);
	if (data.stat < 0)
		return (255);
	return (data.stat);
}

