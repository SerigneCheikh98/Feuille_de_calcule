/*For compilation:
 *gcc eval.c testCell.c ../List/list.c ../Stack/stack.c -lm*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "eval.h"
#include "../Stack/stack.h"

int main(){

   s_cell *A1 = (s_cell *)malloc(sizeof(s_cell));

   if (A1 == NULL){
      printf("Error with malloc\n");
      exit(1);
   }

   A1->string = "= 2.8 4 +";
   
   
   s_cell *B1 = (s_cell *)malloc(sizeof(s_cell));

   if (B1 == NULL){
      printf("Error with malloc\n");
      exit(1);
   }

   B1->string = "= A1 10.8 *";

   s_cell *A5 = (s_cell *)malloc(sizeof(s_cell));

   if (A5 == NULL){
      printf("Error with malloc\n");
      exit(1);
   }

   A5->string = "toto";

   s_cell *B4 = (s_cell *)malloc(sizeof(s_cell));

   if (B4 == NULL){
      printf("Error with malloc\n");
      exit(1);
   }

   B4->string = "5";

   //add the cells to the matrix
   int row, col;

   //row = 1 - 1;
   //col = 'A' - 65;
   getIndexes(&row, &col, "A1");
   tab_page[row][col] = A1; //  [0][0]

   //row = 1 - 1;
   //col = 'B' - 65;
   getIndexes(&row, &col, "B1");
   tab_page[row][col] = B1; //  [0][1]

   //row = 5 - 1;
   //col = 'A' - 65;
   getIndexes(&row, &col, "A5");
   tab_page[row][col] = A5; //   [4][0]

   getIndexes(&row, &col, "B4");
   tab_page[row][col] = B4; //   [4][0]

   check_string(A1);
   set_cell(A1);

   printf("A1: %f\n\n", A1->value);

   check_string(B1);
   set_cell(B1);

   printf("B1: %f\n\n", B1->value);

   check_string(A5);
   set_cell(A5);

   printf("A5: %f\n\n", A5->value);

   check_string(B4);
   set_cell(B4);

   printf("B4: %f\n", B4->value);

   free(A1);
   free(B1);
   free(A5);   
   free(B4); 
   return 0;
}