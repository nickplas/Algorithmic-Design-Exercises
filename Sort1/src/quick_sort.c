#include <quick_sort.h>
#include <swap.h>
#include <total_order.h>
#include <stdio.h>

unsigned int partition(void *A, const size_t elem_size, size_t i, size_t j ,size_t p, total_order_type leq)
{
	swap(A+i*elem_size, A+p*elem_size, elem_size);
	p = i;
	i++;
	while(i<=j){
		if(leq(A+p*elem_size, A+i*elem_size)){
			swap(A+i*elem_size,A+j*elem_size, elem_size);
			j--;
		}else{
			i++;
		}
	}
	swap(A+p*elem_size, A+j*elem_size, elem_size);
	return j;	
}

void quick_sort_aux(void *A, size_t i, const unsigned int n, const size_t elem_size, total_order_type leq)
{
	unsigned int p;
	while(i<n){
		p = partition(A, elem_size, i, n, i, leq);
		quick_sort_aux(A, i, p, elem_size, leq);
		i = p+1; //tail recursion
		//quick_sort_aux(A, p+1, n, elem_size, leq); 
	}		
}

void quick_sort(void *A, const unsigned int n, 
                const size_t elem_size, 
                total_order_type leq)
{
	quick_sort_aux(A, 0, n, elem_size, leq);   
}
