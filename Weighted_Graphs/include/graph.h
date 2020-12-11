#ifndef __GRAPH__
#define __GRAPH__

#define INFTY 9999

#include<queue.h>

typedef struct graph{
    node* V; // set of nodes
    int** E; // adjacency matrix
    unsigned int size; // number of nodes
} graph;

graph* build_graph(void* A, int** E, unsigned int n);

int weight(graph* G, node* u, node* v);

void init_sssp(graph* G, unsigned int max);

void relax(queue* Q, node* u, node* v, int w);

void dijkstra(graph* G, node* source); //here distance array aka .d will be created

#endif
