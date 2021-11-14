#include <stdio.h>
#include "list.h"

void print_integer_list(node_t *head);

int main(){
    node_t * head;
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;;
    int *p;

    head = list_create();

    if(head != NULL)
        printf("head point to %p instead NULL\n", head);
    
    head = list_insert(head, &i2);
    if(head == NULL)
        printf("Error with list_insert\n");
    else
    {
        p = head->data;
        printf("the data of the new first node is %d \n", *p);
    }

    head = list_insert(head, &i1);
    if(head == NULL)
        printf("Error with list_insert()\n");
    else
    {
        p = head->data;
        printf("the data of the new first node is %d \n", *p);
    }

    print_integer_list(head);

    list_set_data(head->next, &i4);

    p = list_get_data(head->next);

    printf("The new value of head->next is %d\n", *p);

    if(head->next != list_next(head)){
        printf("Error with list_next()\n");
    }

    head = list_append(head, &i3);

    print_integer_list(head);

    head = list_remove(head, &i3);
    head = list_head_Remove(head);

    print_integer_list(head);

    printf("\nEnd of tests\n");

    return 0;
}

void print_integer_list(node_t *head){
    int c = 1;
    int * p;
    
    while (head != NULL)
    {
        p = head->data;
        printf("node %d: %d\t", c, *p);
        head = head->next;
        c++;
    }
    printf("\n");
}