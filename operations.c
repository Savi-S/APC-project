#include "main.h"

int add(Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2, int sign1, int sign2, Dlist **res_head, Dlist **res_tail) 
{
    int carry = 0, sum;
    Dlist *S_head = NULL, *S_tail = NULL;
    Dlist *t1, *t2;

    int h1_neg = (*head1 && (*head1)->data < 0);
    int h2_neg = (*head2 && (*head2)->data < 0);

    if (h1_neg && h2_neg) 
    {
        (*head1)->data = -(*head1)->data;
        (*head2)->data = -(*head2)->data;
        
	add(head1, head2, tail1, tail2, 1, 1, res_head, res_tail); 
        if (*res_head) 
	{
            Dlist *actual_head = *res_head;
            
	    while(actual_head->prev != NULL)
	    {
                actual_head = actual_head->prev;
            }
            actual_head->data *= -1; 
        }
        return SUCCESS;
    }

    if (h1_neg && !h2_neg) 
    {
        (*head1)->data = -(*head1)->data;
        subtract(head2, head1, tail2, tail1, res_head, res_tail);
        return SUCCESS;
    }

    if (!h1_neg && h2_neg) 
    {
        (*head2)->data = -(*head2)->data;
        subtract(head1, head2, tail1, tail2, res_head, res_tail);
        return SUCCESS;
    }


    t1 = *tail1;
    t2 = *tail2;

    while (t1 || t2 || carry) 
    {
        sum = carry;
        if (t1) 
	{
            sum += t1->data;
            t1 = t1->prev;
        }

        if (t2) 
	{
            sum += t2->data;
            t2 = t2->prev;
        }

        carry = sum / 10;
        sum %= 10;

        insert_at_first(&S_head, &S_tail, sum);
    }

    *res_head = S_head;
    *res_tail = S_tail;

    return SUCCESS;
}


int subtract(Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2, Dlist **res_head, Dlist **res_tail)
{
        int brw=0, diff;

        Dlist *Dhead = NULL;
        Dlist *Dtail = NULL;

        Dlist *t1, *t2;

        int h1_neg = (*head1 && (*head1)->data < 0);
        int h2_neg = (*head2 && (*head2)->data < 0);

        if(h1_neg && h2_neg)
        {
                (*head1)->data = -(*head1)->data;
                (*head2)->data = -(*head2)->data;
                subtract(head2, head1, tail2, tail1,res_head, res_tail);
                return SUCCESS;
        }

        if(h1_neg && !h2_neg)
        {
                (*head1)->data = -(*head1)->data;
                add(head1, head2, tail1, tail2, 1, 1, res_head, res_tail);
                if(*res_head != NULL)
                        (*res_head)->data *= -1;

                return SUCCESS;

        }
        if(!h1_neg && h2_neg)
        {
                (*head2)->data = -(*head2)->data;
                add(head1, head2, tail1, tail2, 1, 1, res_head, res_tail);
                return SUCCESS;
        }

        if(compare(*head1, *head2) < 0)
        {
                Dlist *temp = *head1;
                *head1 = *head2;
                *head2 = temp;
                temp = *tail1;
                *tail1 = *tail2;
                *tail2 = temp;
                if(*res_head != NULL)
                        (*res_head)->data *= -1;
        }

        t1 = *tail1;
	t2 = *tail2;

        while(t1 || t2)
        {
                diff = brw;

                if(t1)
                {
                        diff += t1->data;
                        t1 = t1->prev;
                }

                if(t2)
                {
                        diff -= (t2)->data;
                        t2 = t2->prev;
                }

                if(diff < 0)
                {
                        diff += 10;
                        brw = -1;
                }
                else
                        brw = 0;

                insert_at_first(&Dhead, &Dtail, diff);
        }

        while(Dhead && Dhead->data == 0 && Dhead->nxt)
        {
                Dlist *temp = Dhead;
                Dhead = Dhead->nxt;
                Dhead->prev = NULL;
                free(temp);
        }

        if(Dhead == NULL)
        {
                insert_at_first(&Dhead, &Dtail, 0);
        }

        *res_head = Dhead;
        *res_tail = Dtail;

        return SUCCESS;
}


int multiply(Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2, int sign1, int sign2)
{
        Dlist *r_head = NULL, *r_tail = NULL;
        Dlist *temp2 = *tail2;
        int shift = 0;

        insert_at_first(&r_head, &r_tail, 0);

        if(sign1 == -1)
                (*head1)->data = -(*head1)->data;

        if(sign2 == -1)
                (*head2)->data = -(*head2)->data;

        while(temp2)
        {
                int carry = 0;
                Dlist *temp1 = *tail1;
                Dlist *t_head = NULL, *t_tail = NULL;

                for(int i=0; i<shift; i++)
                        insert_at_first(&t_head, &t_tail, 0);

                while(temp1)
                {
                        int product = temp1->data * temp2->data + carry;
                        carry = product / 10;
                        insert_at_first(&t_head, &t_tail, product%10);
                        temp1 = temp1->prev;
                }

                if(carry)
                        insert_at_first(&t_head, &t_tail, carry);

                Dlist *sum_head = NULL, *sum_tail = NULL;
                add(&r_head, &t_head, &r_tail, &t_tail, 1, 1, &sum_head, &sum_tail);
                r_head = sum_head;
                r_tail = sum_tail;
                temp2 = temp2->prev;
                shift++;
        }

        if((sign1 * sign2) == -1)
                printf("-");

        display(r_head);

        return SUCCESS;
}


int divide(Dlist **head1, Dlist **head2, Dlist **tail1, Dlist **tail2, int sign1, int sign2)
{
        if(*head2 == NULL || (*head2)->data == 0)
        {
                printf("Not defined\n");
                return FAILURE;
        }

        Dlist *q_head = NULL, *q_tail = NULL;

        if((*head1)->data < 0)
                (*head1)->data = -(*head1)->data;
        if((*head2)->data < 0)
                (*head2)->data = -(*head2)->data;

        int div = 0, dis = 0, quo = 0;

        Dlist *temp1 = *head1;
        Dlist *temp2 = *head2;

        while(temp1)
        {
                div = div*10 + temp1->data;
                temp1 = temp1->nxt;
        }

        while(temp2)
        {
                dis = dis*10 + temp2->data;
                temp2 = temp2->nxt;
        }


        if(div < dis)
        {
                printf("Result is : 0\n");
                return SUCCESS;
        }

        quo = div / dis;

        char buffer[50];
        sprintf(buffer, "%d", quo);

        for(int i=0;buffer[i] != '\0'; i++)
                insert_at_last(&q_head, &q_tail, buffer[i] - '0');

        if((sign1 * sign2) == -1)
                printf("-");

        display(q_head);

        return SUCCESS;
}
