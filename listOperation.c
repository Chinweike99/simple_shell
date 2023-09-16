#include "shell.h"

/**
 * sepEnd - Function that adds an isolator found at the end
 * of _linkedlist
 * @head: The head of the linked list.
 * @item: isolatator found
 * Return: head address
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
 * freeList - Function that frees _linkedlist
 * @head: The head of the linked list
 * Return: nothing.
 */
void freeList(_linkedlist **head)
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
 * addcmd - Function that adds a command line at end
 * of _linkedlist
 * @head: linked list head.
 * @track: The command line.
 * Return: head address
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
 * freeLi - Function that frees a line node
 * @head: linked list head
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

/**
 * nodeEnd - Function that adds a command line to the end
 * of a line_list.
 * @head: linked list head pointer
 * @track: The command line.
 * Return: address of the head.
 */
_tracklist *nodeEnd(_tracklist **head, char *track)
{
	_tracklist *new, *tmp;

	new = malloc(sizeof(_tracklist));
	if (new == NULL)
		return (NULL);

	(*new).track = track;
	(*new).next = NULL;
	tmp = *head;

	if (tmp == NULL)
		*head = new;
	else
	{
		while ((*tmp).next != NULL)
			tmp = (tmp).next;
		(*tmp).next = new;
	}

	return (*head);
}
