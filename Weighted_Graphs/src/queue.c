#include<queue.h>
#include<total_orders.h>
#include<stdio.h>

queue* build_queue(node* A, int size){
    queue* q = (queue*)malloc(sizeof(queue));
    q->size = size;
    q->Q = (node**)malloc(sizeof(node)*size);
    for(size_t i = 0; i < size; i++){
        q->Q[i] = &A[i]; 
    }
    return q;
}

void swap(queue* Q, int first, int second){
    node* temp = Q->Q[first];
    Q->Q[first] = Q->Q[second];
    Q->Q[second] = temp;
}

int find_min(queue* Q){
    unsigned int min = 0;
    for(unsigned int i = 1; i < Q->size; i++){
        if(leq_int_node(Q->Q[i], Q->Q[min])){
            min = i;
        }
    }
    return min;
}

node* dequeue(queue* Q, int index){
    node* n = Q->Q[index]; //added
    swap(Q, index, Q->size-1);
    Q->size--;
    return n; //Q->Q[Q->size];
}

int is_empty(queue* Q){
    if(Q->size == 0){
        return 1;
    }else{
        return 0;
    }
}

node* extract_min_queue(queue* Q){ 
    if(is_empty(Q)){
        return NULL;
    }
    int n = find_min(Q); //added
    return dequeue(Q,n);// find_min(Q);
}