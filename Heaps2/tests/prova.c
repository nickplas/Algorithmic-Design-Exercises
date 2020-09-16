#include<stdio.h>
#include<string.h>
#include<binheap.h>
//Macros
#define PARENT(pos) ((pos-1)/2) 
#define LEFT_CHILD(pos) (2*pos+1)
#define RIGHT_CHILD(pos) (2*pos+2)
#define VALID_NODE(H, node) (((H)->num_of_elem) > node) //An index for a node is valid if its smaller than the size of the heap
#define ADDR(H, node) ((H)->A+(node)*((H)->key_size)) //The position in memory where we want to go
#define INDEX_OF(H, addr) ((addr-((H)->A))/((H)->key_size))
#define POS(node) (H->key_pos[node]) //Returns the position of node i
#define NODE(pos) (H->rev_pos[pos]) //Returns the node in position i

int main(){

    int arr[5];

    for(size_t i=0; i<5; i++){
        arr[i]= i+1;
    }

    for(size_t i=0; i<5; i++){
        printf("%d\n", arr[i]);
    }

    binheap_type *heap=build_heap(arr,5,5,sizeof(int),geq_int);

    printf("The addr of arr[4] is %p\n", INDEX_OF(heap, 1));
    return 0;
}