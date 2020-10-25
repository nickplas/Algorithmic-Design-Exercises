#include <binheap.h>
#include <stdio.h>
#include <string.h>

#define PARENT(node) ((node-1)/2)
#define LEFT_CHILD(node) (2*(node)+1)
#define RIGHT_CHILD(node) (2*(node+1)) 
#define VALID_NODE(H,node) ((H)->num_of_elem>(node))
#define ADDR(H,node) ((H)->A+node*(H)->key_size)
#define INDEX_OF(H,addr) (((addr)-((H)->A))/(H)->key_size)

//new macros used to implement key_pos and rev_pos
#define POS(H, node) ((H)->key_pos[node])
#define KEY(H, pos) ((H)->rev_pos[pos])

int is_heap_empty(const binheap_type *H){
	return (H->num_of_elem == 0);
}

const void *min_value(const binheap_type *H){
	if(is_heap_empty(H)){
		return NULL;
	}
	return ADDR(H, 0);
}

//Here we will use key_pos and rev_pos to perform the swap
void swap_keys(binheap_type *H, unsigned int n_a, unsigned int n_b ){
	//printf("I am swapping node %d in pos %d with node %d in pos %d\n", n_a, POS(H, n_a), n_b, POS(H, n_b));
	unsigned int p_a = POS(H, n_a);
	unsigned int p_b = POS(H, n_b);
	//printf("p_a is %d, p_b is %d\n", p_a, p_b);
	POS(H, n_a) = p_b;
	POS(H, n_b) = p_a; 
	KEY(H, p_a) = n_b;
	KEY(H, p_b) = n_a;
	//printf("now we have that %d is in pos %d and %d is in pos %d\n", KEY(H, p_a), POS(H, n_a), KEY(H, p_b), POS(H, n_b));
}

//changing heapify function in order to use POS and KEY
void heapify(binheap_type *H, unsigned int node){
	unsigned int dst_node = node;
	unsigned int child, node_pos, child_pos;
	do{
        	node = dst_node;
		node_pos = POS(H, node);
        	child_pos = RIGHT_CHILD(node_pos);
		child = KEY(H, child_pos); 
        	if (VALID_NODE(H,child_pos) && H->leq(ADDR(H,child), ADDR(H, dst_node))){
        		dst_node = child;
        	}
        	child_pos = LEFT_CHILD(node_pos);
		child = KEY(H, child);
        	if (VALID_NODE(H,child) && H->leq(ADDR(H,child), ADDR(H, dst_node))) {
        		dst_node = child;
        	}
        	if(dst_node != node){
        		swap_keys(H, dst_node, node);
        	}
	}while(dst_node != node);
}

const void *extract_min(binheap_type *H){
	if(is_heap_empty(H)){
        	return NULL;
	}
	swap_keys(H, 0,  H->num_of_elem-1); //here I've used KEY macro
	H->num_of_elem--;
	heapify(H, 0); //KEY macro

	return ADDR(H, H->num_of_elem+1); //KEY macro
}

const void *find_the_max(void *A, const unsigned int num_of_elem,
                  const unsigned int key_size,total_order_type leq){

        if(num_of_elem==0){
        	return NULL;
        }
        const void *max_value = A;
        for(const void *addr=A+key_size;
            addr!=A+num_of_elem*key_size; addr+=key_size){
                if(!leq (addr, max_value)){
                	max_value = addr;
                }
        }

        return max_value;
}

//new buildheap
binheap_type *build_heap(void *A, 
                         const unsigned int num_of_elem,
                         const unsigned int max_size,  
                         const size_t key_size, 
                         total_order_type leq)
{
	binheap_type *H = (binheap_type *)malloc(sizeof(binheap_type)); 
	H->A = A;
	H->num_of_elem = num_of_elem;
	H->max_size = max_size;
	H->key_size = key_size;
	H->leq = leq;
	H->max_order_value = malloc(key_size);
	
	H->rev_pos = (unsigned int*)malloc(sizeof(unsigned int)*max_size);
	H->key_pos = (unsigned int*)malloc(sizeof(unsigned int)*max_size);

	if (num_of_elem == 0) {
		return H;
	}
	const void *value = find_the_max(A,num_of_elem, key_size,leq);
	                            							
	memcpy(H->max_order_value, value, key_size);

	for(size_t i = 0; i<num_of_elem; i++ ){
		H->rev_pos[i] = i;
		H->key_pos[i] = i;
	}

	//fix heap property
	for(unsigned int i=num_of_elem/2; i>0; i--){
		heapify(H, i); 
	}						 
	heapify(H,0); 
	return H;
}

void delete_heap(binheap_type *H){
	free(H->max_order_value);
	free(H->key_pos);
	free(H->rev_pos);
	free(H);
}


const void *decrease_key(binheap_type *H, void *node, const void *value){

	unsigned int node_idx = POS(H, INDEX_OF(H, node));

    	//check if the node is valid or if the new value is greater than the node's key
    	if(!(H->leq(value, node)) || !(VALID_NODE(H, node_idx))){
        
		return NULL;
    	}
    
    	memcpy(node, value, H->key_size);
	
    	//if we have only one element we cannot use PARENT macro
    	if(H->num_of_elem > 1){ //prevent segmentation fault
        
		unsigned int parent_idx = PARENT(node_idx);
		void* parent = ADDR(H, parent_idx);

		while( (node_idx!=0) && (!(H->leq(parent, node))) ){
		
			swap_keys(H, parent_idx, node_idx);
			node_idx = parent_idx;
			
			if(node_idx == 0){
				parent_idx = 0;
			}else{
				parent_idx = PARENT(node_idx);
				parent = ADDR(H, parent_idx); 
			}
		}

	}

    	return node;
}


const void *insert_value(binheap_type *H, const void *value){
    	if(H->max_size == H->num_of_elem){
        	return NULL;
    	}

    	if(H->num_of_elem == 0 || !(H->leq(value, H->max_order_value))){
        	memcpy(H->max_order_value, value, H->key_size);
    	}

    	//create new node as we did in the Heaps code using the new arrays
	KEY(H, H->num_of_elem) = H->num_of_elem;
	POS(H, H->num_of_elem) = H->num_of_elem;  
	void *new_node_addr = ADDR(H, H->num_of_elem);
    	memcpy(new_node_addr, H->max_order_value, H->key_size);
    	H->num_of_elem++;
    	return decrease_key(H, new_node_addr, value);
}

void print_heap(const binheap_type *H, 
                void (*key_printer)(const void *value)){

    	unsigned int next_level_node = 1;
    	for (unsigned int node = 0; node < H->num_of_elem; node++){
        	if(node == next_level_node){
            		printf("\n");
            		next_level_node = LEFT_CHILD(node);
       		}else{
            		printf("\t");
        	}
        	key_printer(ADDR(H, POS(H,node)));
    	}
    	printf("\n");
}
