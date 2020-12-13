#include <graph.h>
#include <stdlib.h>
#include<queue.h>
#include<binheap.h>
#include<total_orders.h>

graph* build_graph(node* A, int** M, unsigned int n){
    graph* g = (graph*)malloc(sizeof(graph));
    g->V = A; 
    g->E = M;
    g->size = n;
    return g;
}

int weight(graph* G, node* u, node* v){
    return G->E[u->index][v->index];
}

void init_sssp(graph* G, unsigned int max){
    for (size_t i = 0; i<G->size; i++){
        G->V[i].index = i;
        G->V[i].value = max;
        G->V[i].pred = NULL;
    }
}

void relax(node* u, node* v, int w){
    if(u->value+ w < v->value){
        u->value = u->value+w;
        v->pred=u;
    }
}

node* find_nearest_node(graph* G, node* n){ 
    
    int idx_min = 0;
    for(size_t i = 0; i < G->size; i++){       
        if((n->index != G->V[i].index && (weight(G, n, &G->V[i]) < weight(G, n, &G->V[idx_min])) )){
            idx_min = i;
        }
    }
    return &G->V[idx_min]; 
}

void dijkstra_queue(graph* G, node* source){
    init_sssp(G, INFTY);
    source->value = 0;
    queue* q = build_queue(G->V, G->size);
    while(!is_empty(q)){ 
        node* u = extract_min_queue(q); 
        node* v = find_nearest_node(G, u);
        relax(u, v, weight(G, u, v)); 
    }
}

void dijkstra_heap(graph* G, node* source){
    init_sssp(G, INFTY);
    source->value = 0;
    binheap_type* H = build_heap(G->V, G->size, G->size, sizeof(node), leq_int_node);
    while(!is_heap_empty(H)){ 
        node* u = (node*)extract_min_heap(H); 
        node* v = find_nearest_node(G, u);
        printf("%d\n", u->index);
        relax(u, v, weight(G, u, v)); // causes segfault in heap only
        heapify(H, 0); 
    }
    delete_heap(H);
}
