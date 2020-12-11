#include<queue.h>

queue* build_queue(node* A, int size){
    queue* q;
    q->Q = &A;
    q->size = size;
    return q;
}

void swap(queue* Q, int first, int second){
    node* temp = Q->Q[first];
    Q->Q[first] = Q->Q[second];
    Q->Q[second] = temp;
}

int find_min(queue* Q){
    int idx_min = 0;
    for(size_t i = 1; i < Q->size; i++){
        if(Q->Q[idx_min]->value > Q->Q[i]->value){
            idx_min = i;
        }
    }
    return idx_min;
}

node* dequeue(queue* Q, int index){
    swap(Q, index, Q->size-1);
    Q->size--;
    return Q->Q[Q->size];
}

int is_empty(queue* Q){
    if(Q->size == 0){
        return 1;
    }else{
        return 0;
    }
}

node* extract_min(queue* Q){ 
    if(is_empty(Q)){
        return NULL;
    }
    return dequeue(Q,find_min(Q));
}