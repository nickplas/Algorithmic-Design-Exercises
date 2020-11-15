#include <select.h>
#include <swap.h>
#include <quick_sort.h>

unsigned int select_pivot(void* A, const unsigned int n, 
                          const size_t elem_size,
                          total_order_type leq)
{
    if (n <= 10){
        quick_sort(A, n, elem_size, leq);
        return n/2;
    }

    unsigned int chunks = n/5, c_l, c_r;
    for(size_t c = 0; c < chunks; c++){
        c_l = 1+ c*5;
        c_r = 5 + c*5;

        quick_sort(A+c_l*elem_size,c_r - c_l, elem_size, leq);
        swap(A+(c_l+2)*elem_size, A+c*elem_size, elem_size);
    }

    return select_index(A, chunks -1, chunks/2, elem_size, leq);
}

unsigned int select_index(void *A, const unsigned int n, 
                          const unsigned int i,
                          const size_t elem_size, 
                          total_order_type leq)
{
    int *k = malloc(sizeof(int)*2);
    if(n<= 10){
        quick_sort(A, n, elem_size,leq);
        return i;
    }
    unsigned int p = select_pivot(A, n, elem_size, leq);
    unsigned int j = select_pivot(A, n, elem_size, leq);
    k = new_partition(A, elem_size, 0, n, p, leq);

    if (i<k[0]){
        return select_index(A, k[0], 0, elem_size, leq);// if i<k_1
    }
    if(i>k[1]){
	    return select_index(A, n, k[1]+1, elem_size, leq);// if i>k_2	
    }

    return i;
}

void quick_sort_aux_select(void *A, unsigned int i,
                           const unsigned int n,
                           const size_t elem_size,
                           total_order_type leq)
{
    int p = select_pivot(A, n, elem_size, leq);
    int *k;
	while(i<n){
		k = new_partition(A, elem_size, i, n, p, leq);
		quick_sort_aux_select(A, i, k[0], elem_size, leq);
		i = k[1]+1; //tail recursion
		//quick_sort_aux(A, p+1, n, elem_size, leq); 
	}	
}

void quick_sort_select(void *A, const unsigned int n, 
                       const size_t elem_size, 
                       total_order_type leq)
{
   quick_sort_aux_select(A,0,n, elem_size, leq);
}


