#include "graphe.h"

//calculate the degrees and return list conteining all successors (direct and undirect)
node_t * get_degree(node_t * head_graphe){
    if(head_graphe == NULL){
        return list_create();//the graphe is empty
    }
    else{
        //initialize the checked value
        node_t * head_tmp = head_graphe;

        while(head_tmp != NULL){
            s_cell * t = (s_cell *) head_tmp->data;
           
            t->checked = false;
            
            //next cell
            head_tmp = list_next(head_tmp);
        }   

        return visit_cell(head_graphe);
    }
}

//recursive visite to calculate all degrees
node_t * visit_cell(node_t *list_succ){
    if (list_succ == NULL){
        return NULL;
    }
    node_t *list_graph = list_succ;

    while (list_succ != NULL){
        //direct successeur
        s_cell *tmp = (s_cell *)list_succ->data;

        //if not checked get the degree
        if (!tmp->checked){
            tmp->degre_negatif = 0;

            check_string(tmp);

            if (tmp->head_token != NULL){
                node_t *curr_head_token = tmp->head_token;

                //scan the list of tokens
                while (curr_head_token != NULL){
                    s_token *curr_token = (s_token *)curr_head_token->data;

                    if(curr_token->type == REF){
                        tmp->degre_negatif += 1;
                    }

                    //next token
                    curr_head_token = list_next(curr_head_token);
                }
            }
            tmp->checked = true;

            //indirect successeur
            node_t *indirect_succ = visit_cell(tmp->head_s_cell);

            if (indirect_succ != NULL){
                //concat the list
                list_graph = list_concat(list_graph, indirect_succ);
            }
        }
        //next cell
        list_succ = list_next(list_succ); 
    }
    return list_graph;
}

//concatenate 2 lists
node_t * list_concat(node_t * head, node_t * tail){
    node_t * tmp = head;

    //go to the end of the first list
    while(tmp->next != NULL)
        tmp = list_next(tmp);

    tmp->next = tail;

    return head;
}

/*return the first cell with degree = 0
*
*param: **list -> the pointer to list of successors
*
*/
s_cell * get_cell(node_t ** list){
    node_t * curr = *list;

    while(curr != NULL){
        s_cell * t = (s_cell *) curr->data;
        
        if(t->degre_negatif == 0){
            *list = list_remove(*list, t);

            return t;
        }
        curr = list_next(curr);
    }
    return NULL;
}

/*evaluation of the graph in degree order
*
*param: *list -> the list of successors 
*       *init -> the "root" of the sub-graph
*
*/
void set_graph(node_t * list, s_cell * init){
    init->degre_negatif = 0;
    list = list_insert(list, init);

    if(list == NULL)
        return; //the graph is empty

    node_t * tmp_list = list;
    //reset the checked field
    while(tmp_list != NULL){
        ((s_cell *)tmp_list->data)->checked = false;
        tmp_list = list_next(tmp_list);
    }
    
    //get a 0 degree cell
    s_cell * s;
    while (list != NULL){
        do{
            //check if the cell was alread checked!
            s = get_cell(&list);
            if(s == NULL)
                return;
        }while(s->checked);
        
        //set the cell's value
        set_cell(s);
        
        //mark it
        s->checked = true;

        //compute the degrees again
        node_t * tmp = s->head_s_cell;
        while(tmp != NULL){
            s_cell * sj = (s_cell *)tmp->data;
            if(sj->degre_negatif != 0){
                sj->degre_negatif -= 1;
            }

            tmp = list_next(tmp);
        }
    }
}