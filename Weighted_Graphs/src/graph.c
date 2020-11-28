#include <graph.h>
#include <stdlib.h>

graph* build_graph(void* A, int** M, unsigned int n){
    graph* g;
    g->V = A; //pass an array of values
    g->E = M;
    g->size = n;
    return g;
}

void init_sssp( graph* G, unsigned int max){
    for (size_t i = 0; i<G->size; i++){
        G->V[i].value = max;
        G->V[i].pred = NULL;
    }
}

