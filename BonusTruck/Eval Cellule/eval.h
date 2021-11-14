#ifndef _EVAL_H_
#define _EVAL_H_

#include <stdbool.h>

#include "../List/list.h"
#include "../Stack/stack.h"

#define COLS 26
#define ROWS 50
#define SIZE 100

//cell's structure
typedef struct cell{
    char * string;
    double value;
    node_t * head_token;
    node_t * head_s_cell;
    int degre_negatif;
    bool checked;
} s_cell;

//token
typedef struct token {
    enum {VALUE, REF, OPERATOR} type;
    union {
        double cst ;
        s_cell * ref ;
        void (* operator) (my_stack_t * eval) ;
    } value;
} s_token;

//informations of the page
typedef struct Feuille{
    char * name;
    int rows;
    int cols;
    node_t * list_s_cell;
}s_page;

//operator 
struct op{
    char *name;
    void (*op)(my_stack_t *);
};


extern s_page page;
extern struct op operators[6];
extern s_cell * tab_page[ROWS][COLS];

void sum(my_stack_t * stack);

void subtract(my_stack_t * stack);

void multiply(my_stack_t * stack);

void divide(my_stack_t * stack);

void modulus(my_stack_t * stack);

void check_string (s_cell * cellule);

void set_cell(s_cell * cellule);  

void getIndexes(int* row, int* col, char * name);
#endif
