#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "eval.h"

s_page page = {"test", ROWS, COLS, NULL};
struct op operators[] = {{"+", sum}, {"-", subtract}, {"*", multiply}, {"/", divide}, {"mod", modulus}, {NULL, NULL}};
s_cell * tab_page[ROWS][COLS] = {NULL};


void sum(my_stack_t * stack){
    double op1, op2, ris;

    op2 = (double) STACK_POP(stack, double);   
    op1 = (double) STACK_POP(stack, double);
    
    ris = op1 + op2;

    //push the result
    STACK_PUSH(stack, ris, double);
}

void subtract(my_stack_t * stack){
    double op1, op2, ris;

    op2 = (double) STACK_POP(stack, double);   
    op1 = (double) STACK_POP(stack, double);
    
    ris = op1 - op2;

    //push the result
    STACK_PUSH(stack, ris, double);
}

void multiply(my_stack_t * stack){
    double op1, op2, ris;

    op2 = (double) STACK_POP(stack, double);   
    op1 = (double) STACK_POP(stack, double);
    
    ris = op1 * op2;

    //push the result
    STACK_PUSH(stack, ris, double);
}

void divide(my_stack_t * stack){
    double op1, op2, ris;

    op2 = (double) STACK_POP(stack, double);   
    op1 = (double) STACK_POP(stack, double);

    if(op2 == 0.0)
        return; //can't divide with 0.0 !
    
    ris = op1 / op2;

    //push the result
    STACK_PUSH(stack, ris, double);
}

void modulus(my_stack_t * stack){
    double op1, op2, ris;

    op2 = (double) STACK_POP(stack, double);   
    op1 = (double) STACK_POP(stack, double);

    if(op2 == 0.0)
        return; //can't divide with 0.0 !

    ris = fmod(op1, op2); //get the remainder

    //push the result
    STACK_PUSH(stack, ris, double);
}



//analise the string of the given s_cell
void check_string (s_cell * cellule){
    char * string = strdup(cellule->string);
    char *ptr;
    int i,j, n = 0;
    char c;
    double num = 0.0;

    //dealloc the old list of token
    free(cellule->head_token);
    cellule->head_token = list_create();

    if(strcmp(string, "") == 0){
        cellule->value = 0.0;
        return;
    }
    
    // Returns first token 
    char* token = strtok(string, " ");

    if(strcmp(token,"=") == 0){//this is a formule

        while (token != NULL) {  

            if(sscanf(token, "%lf", &num) == 1 && num > 0.0){//this is a number
                //convert the value into double
                double value = strtod(token, &ptr);
                
                //create the token
                s_token * s_tok = (s_token *) malloc(sizeof(s_token));
                
                if(s_tok == NULL)
                    return;

                s_tok->type = VALUE;
                s_tok->value.cst = value;
                
                //append the value to the token list
                cellule->head_token = list_append(cellule->head_token, s_tok);
                
            }
            else if(strlen(token) == 1 && (strcmp(token,"+") == 0 || strcmp(token,"-") == 0 || strcmp(token,"*") == 0 || 
                    strcmp(token,"/") == 0)){//it's an operator
                //create the token
                s_token * s_tok = (s_token *) malloc(sizeof(s_token));

                if(s_tok == NULL)
                    return;

                s_tok->type = OPERATOR;
                for(i = 0; i < 5; i++){
                    if(strcmp(operators[i].name, token) == 0){
                        s_tok->value.operator = operators[i].op;
                        break;
                    }
                }            
                
                //append the value to the token list
                cellule->head_token = list_append(cellule->head_token, s_tok);
            }
            else if(sscanf(token, "%[A-Z]%d", &c, &n) == 2 && isdigit(token[1]) != 0 && n > 0 && n <= 50){
                //it's a reference
                //create the token
                s_token * s_tok = (s_token *) malloc(sizeof(s_token));

                if(s_tok == NULL)
                    return;
                
                s_tok->type = REF;
                
                int row, col;
                row = n - 1;
                col = c - 65;
                
                if(tab_page[row][col] != NULL){//the cell already exists
                    s_tok->value.ref = tab_page[row][col];
                    
                    bool itsIn = false;
                    node_t * tmp_head_s_cell = tab_page[row][col]->head_s_cell;

                    while(tmp_head_s_cell != NULL){
                        if(tmp_head_s_cell->data == cellule){
                            itsIn = true;
                            break;
                        }
                        tmp_head_s_cell = list_next(tmp_head_s_cell);
                    }
                    
                    if(!itsIn){
                        tab_page[row][col]->head_s_cell = list_append(tab_page[row][col]->head_s_cell, cellule); 
                    }
                }
                else{//the cell doesn't exit yet
                    //create it and set its values
                    s_cell * new = (s_cell *) malloc(sizeof(s_cell));

                    if(new == NULL)//problem with malloc
                        return;
                    
                    new->string = "";
                    new->value = 0.0;
                    new->head_token = NULL;
                    new->head_s_cell = list_append(new->head_s_cell, cellule);

                    //add the cell to the page table
                    tab_page[row][col] = new;

                    //add the value to the list of existing cells
                    page.list_s_cell = list_append(page.list_s_cell, new);

                    //set the reference
                    s_tok->value.ref = new;
                }

                //append the token to the token list
                cellule->head_token = list_append(cellule->head_token, s_tok);              
            }
            else if(strlen(token) == 3 && strcmp(token,"mod") == 0){//it's the modulus operator
                //create the token
                s_token * s_tok = (s_token *) malloc(sizeof(s_token));
            
                if(s_tok == NULL)
                    return;

                //set the values
                s_tok->type = OPERATOR;
                for(i = 0; i < 5; i++){
                    if(strcmp(operators[i].name, token) == 0){
                        s_tok->value.operator = operators[i].op;
                        break;
                    }
                }

                //append the token to the list
                cellule->head_token = list_append(cellule->head_token, s_tok);
            }
            //printf("#%s#\n", token);
            token = strtok(NULL, " ");
        }
    }
    else{ //this is a string or a simple number
        if(sscanf(cellule->string, "%lf%c", &num, &c) == 1){//it's a normal number
            cellule->value = num;
            cellule->head_token = NULL;
        } 
        else{//it's a string
            cellule->value = 0.0;
            cellule->head_token = NULL;
        } 
        //printf("#%s#\n", cellule->string);
    }
    free(string); //free the strdup 
}

//set the value cell value
void set_cell(s_cell * cellule){
    int i;

    //create the stack
    my_stack_t *stack = STACK_CREATE(SIZE, double);

    if(stack == NULL)
        return;

    if(cellule->head_token != NULL){//it's a formule and i have tokens
        node_t *head = cellule->head_token;

        while(head != NULL){
            s_token * token = (s_token *) head->data;

            switch (token->type){
                case VALUE:
                    //push the value 
                    if(STACK_PUSH(stack, token->value.cst, double) == 0)
                        return; //the stack is full!
                break;
                case REF:
                    //get the value of the reference and push it
                    //i suppose that the referenced cell already has a value
                    if(STACK_PUSH(stack, token->value.ref->value, double) == 0)
                        return; //the stack is full!
                break;
                case OPERATOR:
                    //call the operator's function
                    token->value.operator(stack);
                break;
            }
            //next token
            head = head->next;
        }

        //get the result 
        cellule->value = (double) STACK_POP(stack, double);
    }

    stack_remove(stack);
}

//get indexes of a cell for the tab_page
void getIndexes(int* row, int* col, char * name){
   char c;
   
   if(sscanf(name, "%c%d", &c, row) == 2){
      *row -= 1;
      *col = c - 65;
   }

   printf("Indexes of %s are row: %d  col: %d\n", name, *row, *col);
}