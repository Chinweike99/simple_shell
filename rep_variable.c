#include "main.h"

/**
 * envCheck - checks if the typed variable is an env variable
 *
 * @hd: head of linked list
 * @inp: input string
 * @data: data structure
 * Return: no return
 */
void envCheck(r_var **hd, char *inp, dataShell *data)
{
	int rw, chr, j, lval;
	char **_evr;

	_evr = (*data)._environ;
	for (rw = 0; _evr[rw]; rw++)
	{
		for (j = 1, chr = 0; _evr[rw][chr]; chr++)
		{
			if (_evr[rw][chr] == '=')
			{
				lval = _strlen(_evr[rw] + chr + 1);
				rvarNode(hd, j, _evr[rw] + chr + 1, lval);
				return;
			}

			if (inp[j] == _evr[rw][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; inp[j]; j++)
	{
		if (inp[j] == ' ' || inp[j] == '\t' || inp[j] == ';' || inp[j] == '\n')
			break;
	}

	rvarNode(hd, j, NULL, 0);
}

/**
 * varCheck - check if the typed variable is $$ or $?
 *
 * @hd: head of the linked list
 * @inp: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int varCheck(r_var **hd, char *inp, char *st, dataShell *data)
{
	int a, last, lpd;

	last = _strlen(st);
	lpd = _strlen((*data).pid);

	for (a = 0; inp[a]; a++)
	{
		if (inp[a] == '$')
		{
			if (inp[a + 1] == '?')
				rvarNode(hd, 2, st, last), a++;
			else if (inp[i + 1] == '$')
				rvarNode(hd, 2, (*data).pid, lpd), a++;
			else if (inp[a + 1] == '\n')
				rvarNode(hd, 0, NULL, 0);
			else if (inp[a + 1] == '\0')
				rvarNode(hd, 0, NULL, 0);
			else if (inp[a + 1] == ' ')
				rvarNode(hd, 0, NULL, 0);
			else if (inp[a + 1] == '\t')
				rvarNode(hd, 0, NULL, 0);
			else if (inp[a + 1] == ';')
				rvarNode(hd, 0, NULL, 0);
			else
				envCheck(hd, inp + a, data);
		}
	}

	return (a);
}

/**
 * replaced_str - replaces string into variables
 *
 * @head: head of the linked list
 * @str: input string
 * @new_str: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_str(r_var **head, char *str, char *new_str, int nlen)
{
	r_var *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (str[j] == '$')
		{
			if (!((*indx).len_var) && !((*indx).len_val))
			{
				new_str[i] = str[j];
				j++;
			}
			else if ((*indx).len_var && !((*indx).len_val))
			{
				for (k = 0; k < (*indx).len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < (*indx).len_val; k++)
				{
					new_str[i] = (*indx).val[k];
					i++;
				}
				j += ((*indx).len_var);
				i--;
			}
			indx = (*indx).next;
		}
		else
		{
			new_str[i] = str[j];
			j++;
		}
	}

	return (new_str);
}

/**
 * repVar - calls functions to replace string into vars
 *
 * @str: input string
 * @data: data structure
 * Return: replaced string
 */
char *repVar(char *str, dataShell *data)
{
	r_var *head, *indx;
	char *stat, *new_str;
	int olen, nlen;

	stat = _itoa((*data).stat);
	head = NULL;

	olen = check_vars(&head, str, stat, data);

	if (head == NULL)
	{
		free(stat);
		return (str);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += ((*indx).len_val - (*indx).len_var);
		indx = (*indx).next;
	}

	nlen += olen;

	new_str = malloc(sizeof(char) * (nlen + 1));
	new_str[nlen] = '\0';

	new_str = replaced_str(&head, str, new_str, nlen);

	free(str);
	free(stat);
	free_rvar_list(&head);

	return (new_str);
}
