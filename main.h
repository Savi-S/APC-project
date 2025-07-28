#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS -1
#define FAILURE -2

typedef struct node
{
	int data;
	struct node *prev;
	struct node *nxt;
}Dlist;

int add(Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2, int sign1, int sign2, Dlist **res_head, Dlist **res_tail);
int subtract(Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2, Dlist **res_head, Dlist **res_tail);
int multiply(Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2, int sign1, int sign2);
int divide(Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2, int sign1, int sign2);
int reverse(Dlist **head, Dlist **tail);
int compare(Dlist *tail1, Dlist *tail2);
int insert_at_last(Dlist **head, Dlist **tail, int data);
int insert_at_first(Dlist **head, Dlist **tail, int data);
int string_to_int(Dlist **head, Dlist **tail, char *data);
void display(Dlist *head);
#endif
