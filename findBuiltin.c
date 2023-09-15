#include "main.h"

/**
 * findBuilt - finds builtins and commands
 *
 * @datash: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(dataShell *data)
{
	int (*builtin)(dataShell *data);

	if ((*data).args[0] == NULL)
		return (1);

	builtin = getBuiltin((*data).args[0]);

	if (builtin != NULL)
		return (builtin(data));

	return (cmdExec(data));
}
/**
 * shellExit - exits the shell
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int shellExit(dataShell *data)
{
	unsigned int ustat;
	int digitv;
	int strlenv;
	int _number;

	if ((*data).args[1] != NULL)
	{
		ustat = at_oi((*data).args[1]);
		digitv = _digitv((*data).args[1]);
		strlenv = _strlen((*data).args[1]);
		_number = ustat > (unsigned int)INT_MAX;
		if (!digitv || strlenv > 10 || _number)
		{
			getError(data, 2);
			(*data).stat = 2;
			return (1);
		}
		(*data).stat = (ustat % 256);
	}
	return (0);
}

#include "main.h"

/**
 * getBuiltin - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*getBuiltin(char *cmd))(dataShell *)
{
	builtint builtin[] = {
		{ "env", envVar },
		{ "exit", shellExit },
		{ "setenv", setEnv },
		{ "unsetenv", delEnv },
		{ "cd", ccDir },
		{ "help", getHelp },
		{ NULL, NULL }
	};
	int x;

	for (x = 0; builtin[x].ename; x++)
	{
		if (_strcmp(builtin[x].ename, cmd) == 0)
			break;
	}

	return (builtin[x].f);
}

