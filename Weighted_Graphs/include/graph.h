
typedef struct node{
    int index;
    int value;
    struct node* pred;
} node;

typedef struct graph{
    node* V; // set of nodes
    int** E; // adjacency matrix
    unsigned int size; // number of nodes
} graph;

typedef struct queue{
    
} queue;

graph* build_graph(void* A, int** E, unsigned int n);

void init_sssp(graph* G, unsigned int max);

void relax ();

void dijkstra (graph* G);

queue* build_queue();
