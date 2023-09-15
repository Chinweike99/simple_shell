#include "main.h"

/**
 * strmsg - function that concatenates the message for cd error
 *
 * @datash: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *strmsg(dataShell *data, char *mes, char *error, char *verstr)
{
	char *wflag;

	_strcpy(error, (*data).av[0]);
	_strcat(error, ": ");
	_strcat(error, verstr);
	_strcat(error, ": ");
	_strcat(error, (*data).args[0]);
	_strcat(error, mes);
	if ((*data).args[1][0] == '-')
	{
		wflag = malloc(3);
		wflag[0] = '-';
		wflag[1] = (*data).args[1][1];
		wflag[2] = '\0';
		_strcat(error, wflag);
		free(wflag);
	}
	else
	{
		_strcat(error, (*datash).[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * errorMsg - error message for cd command in get_cd
 * @datash: data relevant (directory)
 * Return: Error message
 */
char *errorMsg(dataShell *data)
{
	int len, idLen;
	char *error, *verstr, *mes;

	verstr = _itoa((*data).count);
	if ((*data).args[1][0] == '-')
	{
		mes = ": Wrong opt ";
		idLen = 2;
	}
	else
	{
		mes = ": Not possible ";
		idLen = _strlen((*data).args[1]);
	}

	len = _strlen((*data).av[0]) + _strlen((*data).args[0]);
	len += _strlen(verstr) + _strlen(mes) + idLen + 5;
	error = malloc(sizeof(char) * (len + 1));

	if (error == 0)
	{
		free(verstr);
		return (NULL);
	}

	error = strmsg(data, mes, error, verstr);

	free(verstr);

	return (error);
}

/**
 * error_not_found - generic error message for command not found
 * @datash: data relevant (counter, arguments)
 * Return: Error message
 */
char *unFound(dataShell *data)
{
	int len;
	char *error;
	char *verstr;

	verstr = _itoa((*data).count);
	len = _strlen((*data).av[0]) + _strlen(verstr);
	len += _strlen((*data).args[0]) + 16;
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
	_strcat(error, ": Unfound\n");
	_strcat(error, "\0");
	free(verstr);
	return (error);
}

/**
 * errorShell - generic error message for exit in get_exit
 * @data: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *errorShell(dataShell *data)
{
	int len;
	char *error;
	char *verstr;

	verstr = _itoa((*data).count);
	len = _strlen((*data).av[0]) + _strlen(verstr);
	len += _strlen((*data).args[0]) + _strlen((*data).args[1]) + 23;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(verstr);
		return (NULL);
	}
	_strcpy(error, (*data).av[0]);
	_strcat(error, ": ");
	_strcat(error, verstr);
	_strcat(error, ": ");
	_strcat(error, (*data).args[0]);
	_strcat(error, ": wrong: ");
	_strcat(error, (*data).args[1]);
	_strcat(error, "\n\0");
	free(verstr);

	return (error);
}
