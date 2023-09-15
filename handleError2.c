#include "main.h"

/**
 * errorEnv - error message for env in get_env.
 * @datash: data relevant (counter, arguments)
 * Return: error message.
 */
char *errorEnv(dataShell *data)
{
	int len;
	char *error;
	char *verstr;
	char *mes;

	verstr = _itoa((*data).count);
	mes = ": Not possible to add/remove from environment\n";
	len = _strlen((*data).av[0]) + _strlen(verstr);
	length += _strlen((*data).args[0]) + _strlen(mes) + 4;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(error);
		free(verstr);
		return (NULL);
	}

	_strcpy(error, (*data).av[0]);
	_strcat(error, ": ");
	_strcat(error, verstr);
	_strcat(error, ": ");
	_strcat(error, (*data).args[0]);
	_strcat(error, mes);
	_strcat(error, "\0");
	free(verstr);

	return (error);
}
/**
 * pathError - error message for path and failure denied permission.
 * @datash: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *pathError(data_shell *datash)
{
	int len;
	char *verstr;
	char *error;

	verstr = _itoa((*data).count);
	len = _strlen((*data).av[0]) + _strlen(verstr);
	len += _strlen((*data).args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(error);
		free(verstr);
		return (NULL);
	}
	_strcpy(error, (*data).av[0]);
	_strcat(error, ": ");
	_strcat(error, verstr);
	_strcat(error, ": ");
	_strcat(error, (*data).args[0]);
	_strcat(error, ": Unaccessible\n");
	_strcat(error, "\0");
	free(verstr);
	return (error);
}



File: Exec_lin

