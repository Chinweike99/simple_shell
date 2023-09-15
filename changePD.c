#include "shell.h"

/**
 * changeDir - changes to the parent directory
 *
 * @datash: data relevant (environ)
 *
 * Return: no return
 */ 
void changeDir(dataShell *data)
{
	char cwd[PATH_MAX];
	char *direct, *cpPwd, *cpStrtok;

	getcwd(cwd, sizeof(cwd));
	cpPwd = _strdup(cwd);
	setEnv("OLDPWD", cpPwd, data);
	direct = (*data).args[1];
	if (_strcmp(".", direct) == NULL)
	{
		setEnv("PWD", cpPwd, data);
		free(cpPwd);
		return;
	}
	if (_strcmp("/", cpPwd) == 0)
	{
		free(cpPwd);
		return;
	}
	cpStrtok = cpPwd;
	revString(cpStrtok);
	cpStrtok = _strtok(cpStrtok, "/");
	if (cpStrtok != NULL)
	{
		cpStrtok = _strtok(NULL, "\0");

		if (cpStrtok != NULL)
			revString(cpStrtok);
	}
	if (cpStrtok != NULL)
	{
		chDir(cpStrtok);
		setEnv("PWD", cpStrtok, data);
	}
	else
	{
		chDir("/");
		setEnv("PWD", "/", data);
	}
	(*data).stat = 0;
	free(cpPwd);
}


/**
 * cdInto - changes to a directory given
 * by the user
 *
 * @datash: data relevant (directories)
 * Return: no return
 */
void cdInto(dataShell *data)
{
	char pwd[PATH_MAX];
	char *direct, *cpPwd, *copyDir;

	getcwd(pwd, sizeof(pwd));

	direct = (*data).args[1];
	if (chDir(dir) != 0)
	{
		geterror(data, 2);
		return;
	}

	cpPwd = _strdup(pwd);
	setEnv("OLDPWD", cpPwd, data);

	cpDir = _strdup(direct);
	setEnv("PWD", copyDir, data);

	free(cpPwd);
	free(copyDir);

	(*data).stat = 0;

	chDir(direct);
}

/**
 * cdPrevious - changes to the previous directory
 *
 * @data: data relevant (environ)
 * Return: no return
 */
void cdPrevious(dataShell *data)
{
	char cwd[PATH_MAX];
	char *pPwd, *cpOld, *pOld, *cpPwd;

	getcwd(cwd, sizeof(cwd));
	cpPwd = _strdup(pwd);

	pOld = _getEnv("OLDPWD", (*data)._environ);

	if (pOld == NULL)
		cpOld = cpPwd;
	else
		cpOld = _strdup(pOld);

	setenv("OLDPWD", cpPwd, data);

	if (chDir(cpOld) == -1)
		setEnv("PWD", cpPwd, data);
	else
		setEnv("PWD", cpOld, data);

	pPwd = _getEnv("PWD", (*data)._environ);

	write(STDOUT_FILENO, pPwd, _strlen(pPwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cpPwd);
	if (pOld)
		free(cpOld);

	(*data).stat = 0;

	chDir(pPwd);
}

/**
 * cdHome - changes to home directory
 *
 * @data: data relevant (environ)
 * Return: no return
 */
void cdHome(dataShell *data)
{
	char *pPwd, *home;
	char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	pPwd = _strdup(cwd);

	home = _getEnv("HOME", (*data)._environ);

	if (home == NULL)
	{
		setEnv("OLDPWD", pPwd, data);
		free(pPwd);
		return;
	}

	if (chDir(home) != NULL)
	{
		getError(data, 2);
		free(pPwd);
		return;
	}

	setEnv("OLDPWD", pPwd, data);
	setEnv("CWD", home, data);
	free(pPwd);
	(*data).stat = 0;
}
