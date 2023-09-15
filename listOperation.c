#include "main.h"

/**
 * sepEnd - adds a separator found at the end
 * of a sep_list.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
_linkedlist *sepEnd(_linkedlist **head, char item)
{
	_linkedlist *new, *tmp;

	new = malloc(sizeof(sepList));
	if (new == NULL)
		return (NULL);

	(*new).isolator = item;
	(*new).next = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		*head = new;
	}
	else
	{
		while ((*tmp).next != NULL)
			tmp = (*tmp).next;
		(*tmp).next = new;
	}

	return (*head);
}

/**
 * free_sep_list - frees a sep_list
 * @head: head of the linked list.
 * Return: no return.
 */
void freList(_linkedlist **head)
{
	_linkedlist *tmp;
	_linkedlist *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((tmp = curr) != NULL)
		{
			curr = (*curr).next;
			free(tmp);
		}
		*head = NULL;
	}
}

/**
 * addcmd - adds a command line at the end
 * of a line_list.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
_tracklist *addcmd(_tracklist **head, char *track)
{
	_tracklist *new, *tmp;

	new = malloc(sizeof(_tracklist));
	if (new == NULL)
		return (NULL);

	(*new).track = track; or /*new->track = strdup(track);*/
	(*new).next = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		*head = new;
	}
	else
	{
		while ((*tmp).next != NULL)
			tmp = (*tmp).next;
		(*tmp).next = new;
	}

	return (*head);
}

/**
 * freeLi - frees a line_list
 * @head: head of the linked list.
 * Return: no return.
 */
void freeLi(_tracklist **head)
{
	_tracklist *tmp;
	_tracklist *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((tmp = curr) != NULL)
		{
			curr = (*curr).next;
			free(tmp);
		}
		*head = NULL;
	}
}

