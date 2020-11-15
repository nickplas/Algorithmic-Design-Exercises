#include <heap_sort.h>
#include <binheap.h>
#define MAX_SIZE 1000

void heap_sort(void *A, const unsigned int n, 
               const size_t elem_size, 
               total_order_type leq)
{
	binheap_type *H = build_heap(A, n, n, elem_size, geq_int);
	for(size_t i = n-1; i>0; i--){
		extract_min(H);
	}

	delete_heap(H);
}
