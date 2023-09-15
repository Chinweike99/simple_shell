#include "shell.h"

/**
 * getHelp - function that retrieves help messages
 * @data: data structure for args and str
 * Return: Return 1
*/
int getHelp(dataShell *data)
{

	if ((*data).args[1] == 0)
		helpGeneral();
	else if (_strcmp((*data).args[1], "setenv") == 0)
		helpSetenv();
	else if (_strcmp((*data).args[1], "env") == 0)
		helpEnv();
	else if (_strcmp((*data).args[1], "unsetenv") == 0)
		helpUnsetenv();
	else if (_strcmp((*data).args[1], "help") == 0)
		auxhelp();
	else if (_strcmp((*data).args[1], "exit") == 0)
		helpExit();
	else if (_strcmp((*data).args[1], "cd") == 0)
		helpcd();
	else if (_strcmp((*data).args[1], "alias") == 0)
		helpalias();
	else
		write(STDERR_FILENO, (*data).args[0],
		      _strlen((*data).args[0]));

	(*data).stat = 0;
	return (1);
}

