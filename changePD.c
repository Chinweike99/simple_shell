#include "shell.h"

/**
 * changeDir - Function to change the parent directory
 *
 * @data: data relevant to the environ
 */ 
void changeDir(dataShell *data)
{
	char cwd[PATH_MAX];
	char *direct, *cpPwd, *cpStrtok;

	getcwd(cwd, sizeof(cwd));
	cpPwd = _strdup(cwd);
	setEnv("OLDPWD", cpPwd, data);
	direct = (*data).args[1];
	if (_strcmp(".", direct) == 0)
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
 * cdInto - change dirctory to user dirctory
 *
 * @data: data to the directories
 * Return: return nothing
 */
void cdInto(dataShell *data)
{
	char pwd[PATH_MAX];
	char *direct, *cpPwd, *copyDir;

	getcwd(pwd, sizeof(pwd));

	direct = (*data).args[1];
	if (chDir(direct) != 0)
	{
		getError(data, 2);
		return;
	}

	cpPwd = _strdup(pwd);
	setEnv("OLDPWD", cpPwd, data);

	copyDir = _strdup(direct);
	setEnv("PWD", copyDir, data);

	free(cpPwd);
	free(copyDir);

	(*data).stat = 0;

	chDir(direct);
}

/**
 * cdPrevious - changes directory to the previous directory
 *
 * @data: data relevant (environ)
 */
void cdPrevious(dataShell *data)
{
	char cwd[PATH_MAX];
	char *pPwd, *cpOld, *pOld, *cpPwd;

	getcwd(cwd, sizeof(cwd));
	cpPwd = _strdup(cwd);

	pOld = getEnv("OLDPWD", (*data)._environ);

	if (pOld == NULL)
		cpOld = cpPwd;
	else
		cpOld = _strdup(pOld);

	setEnv("OLDPWD", cpPwd, data);

	if (chDir(cpOld) == -1)
		setEnv("PWD", cpPwd, data);
	else
		setEnv("PWD", cpOld, data);

	pPwd = getEnv("PWD", (*data)._environ);

	write(STDOUT_FILENO, pPwd, _strlen(pPwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cpPwd);
	if (pOld)
		free(cpOld);

	(*data).stat = 0;

	chDir(pPwd);
}

/**
 * cdHome - changes the directory to home directory
 * @data: data relevant (environ)
 */
void cdHome(dataShell *data)
{
	char *pPwd, *home;
	char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	pPwd = _strdup(cwd);

	home = getEnv("HOME", (*data)._environ);

	if (home == NULL)
	{
		setEnv("OLDPWD", pPwd, data);
		free(pPwd);
		return;
	}

	if (chDir(home) != -1)
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

