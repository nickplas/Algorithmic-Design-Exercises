#include <selection_sort.h>
#include <swap.h>

void selection_sort(void *A, const unsigned int n, 
                    const size_t elem_size, 
                    total_order_type leq)
{
	size_t max_j = 0;
	for(size_t i = n-1; i>0; i--){
		max_j = 0;
		for(size_t j = 1; j<=i; j++){
			if(!leq(A+j*elem_size, A+max_j*elem_size)){
				max_j = j;
			}
		}
		swap(A+i*elem_size, A+max_j*elem_size, elem_size);
	}   
}
