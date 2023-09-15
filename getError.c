#include "main.h"

/**
 * getError - calls the error according the builtin, syntax or permission
 * @datash: data structure that contains arguments
 * @eval: error value
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
			error = errorShell(data);
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

