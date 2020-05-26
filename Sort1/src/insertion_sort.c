#include <insertion_sort.h>
#include <swap.h>

void insertion_sort(void *A, const unsigned int n, 
                    const size_t elem_size, 
                    total_order leq)
{
	size_t j;
	for(size_t i = 0; i<n; i++){
		j = i;
		while((j>0) && leq_int(A+j*elem_size, A+(j-1)*elem_size)){
			swap(A+j*elem_size, A+(j-1)*elem_size, elem_size);
			j--;
		}
	}
}
