#include <graph.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>
#include<queue.h>

graph* build_graph(void* A, int** M, unsigned int n){
    graph* g;
    g->V = A; //pass an array of values
    g->E = M;
    g->size = n;
    return g;
}

int weight(graph* G, node* u, node* v){
    return G->E[u->index][v->index];
}

void init_sssp(graph* G, unsigned int max){
    for (size_t i = 0; i<G->size; i++){
        G->V[i].value = max;
        G->V[i].pred = NULL;
    }
}

void relax(queue* Q, node* u, node* v, int w){
    if(u->value+ w < v->value){
        u->value = u->value+w;
        v->pred=u;
    }
}

node* find_nearest_node(graph* G, node* n){ //given a node find the nearest one in the col of E matrix
    
    int idx_min = 0;
    for(size_t i = 0; i < G->size; i++){       
        if((n->index != G->V[i].index && (weight(G, n, &G->V[i]) < weight(G, n, &G->V[idx_min])) )){
            idx_min = i;
        }
    }
    return &G->V[idx_min]; 
}

void dijkstra(graph* G, node* source){
    init_sssp(G, INFTY);
    source->value = 0;
    queue* q = build_queue(G->V, G->size);
    while(!is_empty(q)){ //implement is_empty queue
        node* u = extract_min_queue(q); //implement
        node* v = find_nearest_node(G, u);
        relax(q, u, v, weight(G, u, v)); 
    }
}

