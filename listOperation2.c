#include "shell.h"

/**
 * rvarNode - adds a variable at the end
 * of a r_var list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @value: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
singlelist *rvarNode(singlelist **head, int lvar, char *value, int lval)
{
	singlelist *new, *temp;

	new = malloc(sizeof(singlelist));
	if (new == NULL)
		return (NULL);

	(*new).varLen = lvar;
	(*new).value = value;
	(*new).lenVal = lval;

	(*new).next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while ((*temp).next != NULL)
			temp = (*temp).next;
		(*temp).next = new;
	}

	return (*head);
}

/**
 * rvarList - frees an rvar list
 * @head: head of the linked list.
 * Return: no return.
 */
void rvarList(singlelist **head)
{
	singlelist *temp;
	singlelist *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = (*curr).next;
			free(temp);
		}
		*head = NULL;
	}
}

