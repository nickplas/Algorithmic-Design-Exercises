#include <graph.h>
#include <stdlib.h>
#include <queue.h>
#include <binheap.h>
#include <total_orders.h>
#include <utilities.h>

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
        v->value = u->value+w;
        v->pred = u;
    }
}

//Must find all neighbours of node n, list of indices
int* find_nodes(graph* G, node* n){ 
    
    int* nodes = (int*)malloc(sizeof(int)*G->size);
    int j = 0;
    for(size_t i = 0; i < G->size; i++){       
        if(n->index != G->V[i].index && (weight(G, n, &G->V[i]) < INFTY) ){
            nodes[j] = G->V[i].index;
            j++;
        }
    }
    nodes[j]= -1;
    return nodes; 
}

void dijkstra_queue(graph* G, node* source){
    init_sssp(G, INFTY);
    source->value = 0;
    queue* q = build_queue(G->V, G->size);
    while(!is_empty(q)){ 
        node* u = extract_min_queue(q); 
        int* v = find_nodes(G, u);
        int j = 0;      
        while(v[j] != -1){
            relax(u, &G->V[v[j]], weight(G, u, &G->V[v[j]]));
            j++;
        }
        //printf("after relax, index: %d\n", u->index);
        //print_nodes(G, G->size);
        free(v);
    }
}

void dijkstra_heap(graph* G, node* source){
    init_sssp(G, INFTY);
    source->value = 0;
    binheap_type* H = build_heap(G->V, G->size, G->size, sizeof(node), leq_int_node);
    while(!is_heap_empty(H)){ 
        node* u = (node*)malloc(sizeof(node*));
        u = &((node*)H->A)[0];
        int* v = find_nodes(G, u);
        int j = 0;
        while(v[j] != -1){
            relax(u, &G->V[v[j]], weight(G, u, &G->V[v[j]]));
            j++;           
        }        
        extract_min(H);
        heapify(H, 0);  
        free(v);
    }
    delete_heap(H);
}