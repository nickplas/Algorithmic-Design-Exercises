#include<graph.h>
#include<stdlib.h>
#include<utilities.h>

#define MAX_SIZE 100


int main(){
    int* A = get_random_int_array(10);
    int** E = get_random_int_matrix(10);
    graph* g = build_graph(A, E, 10); 
    init_sssp(g, INFTY);
    return 0;
}