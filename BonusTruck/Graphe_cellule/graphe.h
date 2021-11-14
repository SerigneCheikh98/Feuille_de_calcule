#include <stdio.h>
#include <stdlib.h>

#include "../List/list.h"
#include "../Stack/stack.h"
#include "../Eval Cellule/eval.h"

/*calculate the degrees and return list conteining all successors (direct and undirect)
*
* param: direct successors of a cell
*
*/
node_t * get_degree(node_t * head_graphe);

/*recursive visite to calculate all degrees
*
* param: direct successors of a cell
*
*/
node_t * visit_cell(node_t * list_succ);

//concatenate 2 lists
node_t * list_concat(node_t * head, node_t * tail);

/*return the first cell with 0 degree
*
* param: pointer of the sub-graph list returned by get_degree()
*
*/
s_cell * get_cell(node_t ** list);

/*evaluation of the graph in degree order
*
* param: sub-graph list returned by get_degree()
*
*/
void set_graph(node_t * list, s_cell * init);