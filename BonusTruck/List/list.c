#include <stdlib.h>

#include "list.h"


node_t * list_create(void){
    return NULL;
}

void * list_get_data (const node_t * node){
    return node->data;
}

void list_set_data(node_t * node , void * data){
    node->data = data;
}

node_t * list_next(node_t * node){
    //if the next is null will return null
    return node->next;
}

node_t * list_insert(node_t * head, void * data){
    node_t * node;

    if ((node = (node_t *) malloc(sizeof(node_t))) == NULL){
        return head;
    }

    node->data = data;
    
    if(head == NULL){
        node->next = NULL;
        head = node;
    }
    else{
        node->next = head;
        head = node;
    }

    return head;
}

node_t * list_append(node_t * head, void * data){
    node_t * node;

    if ((node = (node_t *) malloc(sizeof(node_t))) == NULL){
        return head;
    }

    node->data = data;

    if(head == NULL){
        node->next = NULL;
        head = node;
    }
    else{
        //pointer of the current node
        node_t * curr = head;
        
        //get the last node
        while (curr->next != NULL){
            curr = curr->next;
        }

        curr->next = node;
        node->next = NULL;
    }

    return head;
}

node_t * list_remove(node_t * head, void * data){
    node_t * temp;

    if(head == NULL)
        return head;
    else if(head->data == data){
        temp = head;
        head = head->next;
        free(temp);
    }
    else{
        node_t * curr = head;

        while (curr->next != NULL){
            
            if(curr->next->data == data){
                temp = curr->next;
                curr->next = curr->next->next;
                free(temp);

                return head;
            }
            //get next node
            curr = curr->next;
        }
    }

    return head;
}

node_t * list_head_Remove(node_t * head){
    node_t * temp;
    temp = head;
    head = head->next;
    free(temp);
    return head;
}

//we need the pointer of the head pointer to let him point to NULL otherwise it will also point to the first node ! 
void list_destroy(node_t * head){
    node_t *next, *curr;
    curr = head;

    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

