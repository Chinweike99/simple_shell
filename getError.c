#include "shell.h"

/**
 * getError - Function that calls the error
 * with respect to the builtin, permission or the syntax
 * @data: data structure that contains arguments
 * @val: error value
 * Return: error
 */
int getError(dataShell *data, int val)
{
	char *error;

	switch (val)
	{
	case -1:
		error = errorEnv(data);
		break;
	case 126:
		error = pathError(data);
		break;
	case 127:
		error = unFound(data);
		break;
	case 2:
		if (_strcmp("exit", (*data).args[0]) == 0)
			error = errorEnv(data);
		else if (_strcmp("cd", (*data).args[0]) == 0)
			error = errorMsg(data);
		break;
	}
	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	(*data).stat = val;
	return (val);
}

