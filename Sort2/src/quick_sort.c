#include <quick_sort.h>
#include <swap.h>
#include <total_order.h>
#include <stdio.h>

//To be changed to deal with equal values
int* new_partition(void *A, const size_t elem_size, size_t i, size_t j ,size_t p, total_order_type leq)
{
	swap(A+i*elem_size, A+p*elem_size, elem_size);
	int* k= malloc(sizeof(int)*2);
	//static int k[2];
	unsigned int c = 0;
	p = i;
	i++;
	j--;
	while(i<=j){
		if(leq(A+p*elem_size, A+i*elem_size) && leq(A+i*elem_size, A+p*elem_size)){
			c++;
			swap(A+(p+c)*elem_size, A+i*elem_size, elem_size);
			i++;
		}else if(leq(A+p*elem_size, A+i*elem_size)){
			swap(A+i*elem_size, A+j*elem_size, elem_size);
			j--;
		}else{
			i++;
		}
	}
	for(unsigned int count = 0; count <=c; count++){
		swap(A+(p+count)*elem_size, A+(j-count)*elem_size, elem_size);
	}
	k[0] = j-c; //initial position 
	k[1] = j; //last position (to check)
	return k;	
}

unsigned int partition(void *A, const size_t elem_size, size_t i, size_t j ,size_t p, total_order_type leq)
{
	swap(A+i*elem_size, A+p*elem_size, elem_size);
	p = i;
	i++;
	j--; //Non può avere come valore n !!!
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
	//int *k;
	unsigned int k;
	while(i<n){
		k = partition(A, elem_size, i, n, i, leq);
		quick_sort_aux(A, i, k, elem_size, leq);
		//i = k[1]+1; //tail recursion
		i = k+1;
		//quick_sort_aux(A, p+1, n, elem_size, leq); 
	}		
}

void quick_sort(void *A, const unsigned int n, 
                const size_t elem_size, 
                total_order_type leq)
{
	quick_sort_aux(A, 0, n, elem_size, leq);   
}
