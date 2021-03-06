#ifndef __GRAPH__
#define __GRAPH__

#define INFTY 9999

#include<queue.h>

typedef struct graph{
    node* V; // set of nodes
    int** E; // adjacency matrix
    unsigned int size; // number of nodes
} graph;

graph* build_graph(node* A, int** E, unsigned int n);

int weight(graph* G, node* u, node* v);

int* find_nodes(graph* G, node* n);

void init_sssp(graph* G, unsigned int max);

void relax(node* u, node* v, int w);

void dijkstra_queue(graph* G, node* source); 

void dijkstra_heap(graph* G, node* source);

#endif
