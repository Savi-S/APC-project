#include "main.h"

void display(Dlist *head)
{
	if(head == NULL)
	{
		printf("0\n");
		return;
	}

	while(head)
	{
		printf("%d", head->data);

		head = head->nxt;
	}
	printf("\n\n");

}

int compare(Dlist *head1, Dlist *head2)
{
	int size1 = 0, size2 = 0;
	Dlist *temp1 = head1;
	Dlist *temp2 = head2;
	while(temp1)
	{
		size1++;
		temp1 = temp1->nxt;
	}
	while(temp2)
	{
		size2++;
		temp2 = temp2->nxt;
	}

	if(size1 > size2)
		return 1;
	if(size1 < size2)
		return -1;

	while(head1 && head2)
	{
		if(head1 -> data > head2->data)
			return 1;

		if(head1->data < head2->data)
			return -1;

		head1 = head1->nxt;
		head2 = head2->nxt;
	}
	return 0;
}


