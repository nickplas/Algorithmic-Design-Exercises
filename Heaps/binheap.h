#ifndef __BIN_HEAP__
#define __BIN_HEAP__

#include <stdlib.h>
#include "total_orders.h"

typedef struct {

	void *A; //array used to store heap nodes
	unsigned int num_of_elem; //number nodes in the heap
	unsigned int max_size; //max number of nodes
	size_t key_size; //size of the key type
	total_order_type leq; //total order of the heap
	void *max_order_value; //max value stored in the heap

} binheap_type;

int is_heap_empty(const binheap_type *H);

const void *heap_min(const binheap_type *H);

void heapify(binheap_type *H, unsigned int node);

const void *remove_min(binheap_type *H);

binheap_type *build_heap(void *A, 
                         const unsigned int num_of_elem, 
                         const unsigned int max_size, 
                         const size_t key_size, 
                         total_order_type leq);

void delete_heap(binheap_type *H);

const void *decrease_key(binheap_type *H, void *node, const void *value);

const void *insert_value(binheap_type *H, const void *value);

void print_heap(const binheap_type *H, 
                void (*key_printer)(const void *value));

#endif
