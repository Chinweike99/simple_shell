#include "shell.h"

/**
 * infoCopy - Function that copies info to create new env
 * @ename: name of env or alias
 * @value: The value of the env or alias
 *
 * Return: Return new env or alias.
 */
char *infoCopy(char *ename, char *value)
{
	char *new;
	int lenName, lenValue, len1;

	lenName = _strlen(ename);
	lenValue = _strlen(value);
	len1 = lenName + lenValue + 2;
	new = malloc(sizeof(char) * (len1));
	_strcpy(new, ename);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * setEnv - Function that sets environment variable
 * @ename: The name of the environment variable
 * @value: value of the variable for environment
 * @data: data structure (environ)
 * Return: return nothing
 */
void setEnv(char *ename, char *value, dataShell *data)
{
	int x;
	char *envVar, *envName;

	for (x = 0; (*data)._environ[x]; x++)
	{
		envVar = _strdup((*data)._environ[x]);
		envName = _strtok(envVar, "=");
		if (_strcmp(envName, ename) == 0)
		{
			free((*data)._environ[x]);
			(*data)._environ[x] = infoCopy(envName, value);
			free(envVar);
			return;
		}
		free(envVar);
	}

	(*data)._environ = _realloc2((*data)._environ, x, sizeof(char *) * (x + 2));
	(*data)._environ[x] = infoCopy(ename, value);
	(*data)._environ[x + 1] = NULL;
}

/**
 * envSet - Function that compares env variables names
 * @data: data relevant (env name and env value)
 * Return: Return 1 on success.
 */
int envSet(dataShell *data)
{

	if ((*data).args[1] == NULL || (*data).args[2] == NULL)
	{
		getError(data, -1);
		return (1);
	}

	setEnv((*data).args[1], (*data).args[2], data);

	return (1);
}

/**
 * delEnv - Function that deletes an environment variable
 * @data: data
 * Return: Return 1 on success.
 */
int delEnv(dataShell *data)
{
	char **environRealloc;
	char *envVar, *envName;
	int x, y, z;

	if ((*data).args[1] == NULL)
	{
		getError(data, -1);
		return (1);
	}
	z = -1;
	for (x = 0; (*data)._environ[x]; x++)
	{
		envVar = _strdup((*data)._environ[x]);
	            envName = _strtok(envVar, "=");
		if (_strcmp(envName, (*data).args[1]) == 0)
		{
			z = x;
		}
		free(envVar);
	}
	if (z == -1)
	{
		getError(data, -1);
		return (1);
	}
	environRealloc = malloc(sizeof(char *) * (x));
	for (x = y = 0; (*data)._environ[x]; x++)
	{
		if (x != Z)
		{
			environRealloc [y] = (*data)._environ[x];
			y++;
		}
	}
	environRealloc [y] = NULL;
	free((*data)._environ[z]);
	free((*data)._environ);
	(*data)._environ = environRealloc;
	return (1);
}
