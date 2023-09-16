#include "shell.h"

/**
 * errorEnv - Function for error message.
 * @data: data relevant counter or arguments
 * Return: error
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
	len += _strlen((*data).args[0]) + _strlen(mes) + 4;
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
 * pathError - Function for error message for path.
 * @data: data relevant counter, arguments.
 * Return: Return the error string.
 */
char *pathError(dataShell *data)
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

