#include <stdio.h>
#include <string.h>
#include "main.h"

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		printf("Invalid Input\n");
		return FAILURE;
	}

	char opr = argv[2][0];

	int sign1 = 1, sign2 = 1;

	if(argv[1][0] == '-')
		sign1 = -1;

	if(argv[3][0] == '-')
		sign2 = -1;

	Dlist *head1 = NULL;
	Dlist *tail1 = NULL;

	Dlist *head2 = NULL;
	Dlist *tail2 = NULL;

	Dlist *res_head = NULL, *res_tail = NULL;


	int value1 =  string_to_int(&head1, &tail1, argv[1]);
	int value2 =  string_to_int(&head2, &tail2, argv[3]);

	if(value1 == FAILURE || value2 == FAILURE)
	{
		printf("Invalid Input\n");
		return FAILURE;
	}
	
	printf("\n");
	display(head1);
	display(head2);

	switch(opr)
	{
		case '+':
			add(&head1, &head2, &tail1, &tail2, sign1, sign2, &res_head, &res_tail);
			display(res_head);
			break;
		case '-':
			subtract(&head1, &head2, &tail1, &tail2, &res_head, &res_tail);
			display(res_head);
			break;
		case '*':
			multiply(&head1, &head2, &tail1, &tail2, sign1, sign2);
			break;
		case '/':
			divide(&head1, &head2, &tail1, &tail2, sign1, sign2);
			break;
		default:
			printf("Invalid operator\n");
	}

	return 0;

}


