#ifndef __QUEUE__
#define __QUEUE__

#include<stdlib.h>

typedef struct node{
    int index;
    int value;
    struct node* pred;
} node;

typedef struct priority_queue{
    node** Q;
    int size; //probably front and rear are not needed
    //int* priority;
} queue;

queue* build_queue(node* A, int size);

void swap(queue* Q, int first, int second);

int find_min(queue* Q);

node* dequeue(queue* Q, int value);

int is_empty(queue* Q);

node* extract_min(queue* Q); 


#endif