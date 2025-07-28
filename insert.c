#include "main.h"

int insert_at_last(Dlist **head, Dlist **tail, int data)
{
	Dlist *new = malloc(sizeof(Dlist));

	if(new == NULL)
		return FAILURE;

	new->data = data;
	new->nxt = NULL;
	new->prev = NULL;

	if (*head == NULL)
	{
		*head = new;
		*tail = new;
		return SUCCESS;
	}

	(*tail)->nxt = new;
	new -> prev = *tail;
	*tail = new;

	return SUCCESS;
}

int insert_at_first(Dlist **head, Dlist **tail, int data)
{
	Dlist *new = malloc(sizeof(Dlist));
	if(new == NULL)
		return FAILURE;

	new->data = data;
	new->nxt = NULL;
	new->prev = NULL;

	if(*head == NULL)
	{
		*head = new;
		*tail = new;
		return SUCCESS;
	}

	new->nxt = *head;
	(*head)->prev = new;
	*head = new;

	return SUCCESS;
}


int string_to_int(Dlist **head, Dlist **tail, char *data)
{
	int flag = 1;

	while(data[0] == '-' || data[0] == '+')
	{
		if(data[0] == '-')
			flag = -flag;

		data++;
	}

	for(int i=0; data[i] != '\0'; i++)
	{
		if(data[i] >= '0' && data[i] <= '9')
		{
			if(*head == NULL)
				insert_at_last(head, tail, flag *(data[i]- '0'));
			else 
				insert_at_last(head, tail, data[i] - '0');

		}
		else
			return FAILURE;
	}
	return flag;
}



