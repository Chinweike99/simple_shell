#include "shell.h"

/**
 * swapChar - swaps | and & for non-printed chars
 *
 * @str: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *swapChar(char *str, int bool)
{
	int a = 0;

	if (bool == 0)
	{
		for (; str[a]; a++)
		{
			if (str[a] == '|')
			{
				if (str[a + 1] != '|')
					str[a] = 16;
				else
					a++;
			}

			if (str[a] == '&')
			{
				if (str[a + 1] != '&')
					str[a] = 12;
				else
					a++;
			}
		}
	}
	else
	{
		for (; str[a]; a++)
		{
			str[a] = (str[a] == 16 ? '|' : str[a]);
			str[a] = (str[a] == 12 ? '&' : str[a]);
		}
	}
	return (str);
}

/**
 * addNodes - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @str: input string
 * Return: no return
 */
void addNodes(_linkedlist **head_s, _tracklist **head_l, char *str)
{
	int a = 0;
	char *track;

	str = swapChar(str, 0);

	for (; str[a]; a++)
	{
		if (str[a] == ';')
			sepEnd(head_s, str[a]);

		if (str[a] == '|' || str[a] == '&')
		{
			sepEnd(head_s, str[a]);
			a++;
		}
	}

	track = _strtok(str, ";|&");
	do {
		track = swapChar(track, 1);
		addcmd(head_l, track);
		track = _strtok(NULL, ";|&");
	} while (track != NULL);

}

/**
 * goNext - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @data: data structure
 * Return: no return
 */
void goNext(_linkedlist **list_s, _tracklist **list_l, dataShell *data)
{
	int iterate_sep;
	_linkedlist *ls_s;
	_tracklist *ls_l;

	iterate_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && iterate_sep)
	{
		if ((*data).stat == 0)
		{
			if ((*ls_s).isolator == '&' || (*ls_s).isolator == ';')
				iterate_sep = 0;
			if ((*ls_s).isolator == '|')
				ls_l = (*ls_l).next, ls_s = (*ls_s).next;
		}
		else
		{
			if ((*ls_s).isolator == '|' || (*ls_s).isolator == ';')
				iterate_sep = 0;
			if ((*ls_s).isolator == '&')
				ls_l = (*ls_l).next, ls_s = (*ls_s).next;
		}
		if (ls_s != NULL && !iterate_sep)
			ls_s = (*ls_s).next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * splitCmd - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @data: data structure
 * @str: input string
 * Return: 0 to exit, 1 to continue
 */
int splitCmd(dataShell *data, char *str)
{

	_linkedlist *head_s, *list_s;
	_tracklist *head_l, *list_l;
	int iterate;

	head_s = NULL;
	head_l = NULL;

	addNodes(&head_s, &head_l, str);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		(*data).str = (*list_l).track;
		(*data).args = lineSplit((*data).str);
		iterate = findBuilt(data);
		free((*data).args);

		if (iterate == 0)
			break;

		goNext(&list_s, &list_l, data);

		if (list_l != NULL)
			list_l = (*list_l).next;
	}

	freeList(&head_s);
	freeLi(&head_l);

	if (iterate == 0)
		return (0);
	return (1);
}

/**
 *lineSplit - tokenizes the input string
 *
 * @str: input string.
 * Return: string splitted.
 */
char **lineSplit(char *str)
{
	size_t size;
	size_t a;
	char **token2;
	char *token;

	size = BUFFSIZE;
	token2 = malloc(sizeof(char *) * (size));
	if (token2 == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(str, T_DELIM);
	token2[0] = token;

	for (a = 1; token != NULL; a++)
	{
		if (a == size)
		{
			size += BUFFSIZE;
			token2 = _realloc2(token2, a, sizeof(char *) * size);
			if (token2 == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, T_DELIM);
		token2[a] = token;
	}

	return (token2);
}

