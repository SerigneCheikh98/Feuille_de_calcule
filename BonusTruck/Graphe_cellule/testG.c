/*For compilation:
 *gcc graphe.c testG.c ../List/list.c ../Stack/stack.c ../Eval\ Cellule/eval.c -lm*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "graphe.h"
#include "../Eval Cellule/eval.h"
#include "../Stack/stack.h"

int main(){

    s_cell *D3 = (s_cell *)malloc(sizeof(s_cell));

    if (D3 == NULL)
    {
        printf("Error with malloc\n");
        exit(1);
    }

    D3->string = "= 4 3 *";

    s_cell *A4 = (s_cell *)malloc(sizeof(s_cell));

    if (A4 == NULL)
    {
        printf("Error with malloc\n");
        exit(1);
    }

    A4->string = "= D3";

    s_cell *A5 = (s_cell *)malloc(sizeof(s_cell));

    if (A5 == NULL)
    {
        printf("Error with malloc\n");
        exit(1);
    }
    
    A5->string = "= A4 D3 +";

    s_cell *D2 = (s_cell *)malloc(sizeof(s_cell));

    if (D2 == NULL)
    {
        printf("Error with malloc\n");
        exit(1);
    }

    D2->string = "= 1000 5 /";

    s_cell *C5 = (s_cell *)malloc(sizeof(s_cell));

    if (C5 == NULL)
    {
        printf("Error with malloc\n");
        exit(1);
    }

    C5->string = "= D2 A5 -";

    //add the cells to the matrix
    int row, col;

    getIndexes(&row, &col, "D3");
    tab_page[row][col] = D3;
    page.list_s_cell = list_append(page.list_s_cell, D3);


    getIndexes(&row, &col, "A4");
    tab_page[row][col] = A4;
    page.list_s_cell = list_append(page.list_s_cell, A4);

    getIndexes(&row, &col, "A5");
    tab_page[row][col] = A5;
    page.list_s_cell = list_append(page.list_s_cell, A5);

    getIndexes(&row, &col, "D2");
    tab_page[row][col] = D2;
    page.list_s_cell = list_append(page.list_s_cell, D2);

    getIndexes(&row, &col, "C5");
    tab_page[row][col] = C5;
    page.list_s_cell = list_append(page.list_s_cell, C5);

    check_string(D3);
    set_cell(D3);

    printf("D3: %f\n\n", D3->value);

    check_string(A4);
    set_cell(A4);

    printf("A4: %f\n\n", A4->value);

    check_string(A5);
    set_cell(A5);

    printf("A5: %f\n\n", A5->value);

    check_string(D2);
    set_cell(D2);

    printf("D2: %f\n\n", D2->value);

    check_string(C5);
    set_cell(C5);

    printf("C5: %f\n\n", C5->value);

    printf("D3 change de: \"%s\" à ", D3->string);
    D3->string = "= 30 3 +";
    check_string(D3);
    
    printf("\"%s\"\n", D3->string);
    //set_cell(D3);

    node_t * list = get_degree(D3->head_s_cell);
    
    set_graph(list, D3);

    printf("\tafter set graph:\n\n");
    printf("D3: %f\n", D3->value);
    printf("A4: %f\n", A4->value);
    printf("A5: %f\n", A5->value);
    printf("D2: %f\n", D2->value);
    printf("C5: %f\n\n", C5->value);


    free(D3);
    free(A4);
    free(A5);
    free(D2);
    free(C5);
    return 0;
}