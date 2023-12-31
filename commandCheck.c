#include "shell.h"

/**
 * colCheck - Function to check if colon ":"
 * if is in the current directory.
 * @myPath: pointer to char type.
 * @x: pointer of index.
 * Return: 1 on success and 0 otherwise.
 */
int colCheck(char *myPath, int *x)
{
	if (myPath[*x] == ':')
		return (1);

	while (myPath[*x] != ':' && myPath[*x])
	{
		*x += 1;
	}

	if (myPath[*x])
		*x += 1;

	return (0);
}

/**
 * locate - Function to locates a command
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *locate(char *cmd, char **_environ)
{
	char *path1, *ptrPath, *tokenPath, *direct;
	int ldirect, lcmd, x;
	struct stat st;

	path1 = getEnv("PATH", _environ);
	if (path1)
	{
		ptrPath = _strdup(path1);
		lcmd = _strlen(cmd);
		tokenPath = _strtok(ptrPath, ":");
		x = 0;

		while (tokenPath != NULL)
		{
			if (colCheck(path1, &x))
				if (stat(cmd, &st) == 0)
					return (cmd);
			ldirect = _strlen(tokenPath);
			direct = malloc(ldirect + lcmd + 2);
			_strcpy(direct, tokenPath);
			_strcat(direct, "/");
			_strcat(direct, cmd);
			_strcat(direct, "\0");
			if (stat(direct, &st) == 0)
			{
				free(ptrPath);
				return (direct);
			}
			free(direct);
			tokenPath = _strtok(NULL, ":");
		}
		free(ptrPath);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * ifexecutable - Function that determines if command
 * is an executable
 * @data: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int ifexecutable(dataShell *data)
{
	struct stat st;
	int x;
	char *str;

	str = (*data).args[0];
	for (x = 0; str[x]; x++)
	{
		if (str[x] == '.')
		{
			if (str[x + 1] == '.')
				return (0);
			if (str[x + 1] == '/')
				continue;
			else
				break;
		}
		else if (str[x] == '/' && x != 0)
		{
			if (str[x + 1] == '.')
				continue;
			x++;
			break;
		}
		else
			break;
	}
	if (x == 0)
		return (0);

	if (stat(str + x, &st) == 0)
	{
		return (x);
	}
	getError(data, 127);
	return (-1);
}

/**
 * verifyPermit - Function to verify if user have permit
 * @direct: directory destination
 * @data: data structure
 * Return: 1 on success, 0 if not
 */
int verifyPermit(char *direct, dataShell *data)
{
	if (direct == NULL)
	{
		getError(data, 127);
		return (1);
	}

	if (_strcmp((*data).args[0], direct) != 0)
	{
		if (access(direct, X_OK) == -1)
		{
			getError(data, 126);
			free(direct);
			return (1);
		}
		free(direct);
	}
	else
	{
		if (access((*data).args[0], X_OK) == -1)
		{
			getError(data, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * execCmd - Functio to execute the command lines
 *
 * @data: takes data (args and input)
 * Return: Return 1 on success.
 */
int execCmd(dataShell *data)
{
	pid_t pid;
	pid_t cpd;
	int sta;
	int exec;
	char *direct;
	(void) cpd;

	exec = ifexecutable(data);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		direct = locate((*data).args[0], (*data)._environ);
		if (verifyPermit(direct, data) == 1)
			return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (exec == 0)
			direct = locate((*data).args[0], (*data)._environ);
		else
			direct = (*data).args[0];
		execve(direct + exec, (*data).args, (*data)._environ);
	}
	else if (pid < 0)
	{
		perror((*data).av[0]);
		return (1);
	}
	else
	{
		do {
			cpd = waitpid(pid, &sta, WUNTRACED);
		} while (!WIFEXITED(sta) && !WIFSIGNALED(sta));
	}

	(*data).stat = sta / 256;
	return (1);

}
