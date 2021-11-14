#ifndef _LIST_H_
#define _LIST_H_

typedef struct node{
    void * data;
    struct node * next;
}node_t;

// creation d’une nouvelle liste vide
node_t * list_create(void);
//get the data of a node
void * list_get_data (const node_t * node);
//set the data of a node
void list_set_data(node_t * node, void * data);
//get the next node
node_t * list_next(node_t * node);
/* create and insert a new node in the top of list
   return head*/
node_t * list_insert(node_t * head, void * data);
/* create and insert a new node in the tail of list
   return head*/
node_t * list_append(node_t * head, void * data);
/*remove the first node containing void * data
  return head*/
node_t * list_remove(node_t * head, void * data);
/*remove the first node 
  return the new head*/
node_t * list_head_Remove(node_t * head);
//destroy the given list
void list_destroy(node_t * head);

#endif