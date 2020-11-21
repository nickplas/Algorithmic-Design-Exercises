#include <select.h>
#include <swap.h>
#include <quick_sort.h>
#include <insertion_sort.h>

unsigned int select_pivot(void* A, const unsigned int n, 
                          const size_t elem_size,
                          total_order_type leq)
{
    if (n <= 10){
        insertion_sort(A, n, elem_size, leq);
        return n/2;
    }

    unsigned int chunks = n/5, begin, end;
    for(size_t c = 0; c < chunks; c++){
        begin = c*5;
        end = 5 + c*5;

        insertion_sort(A+begin*elem_size,end - begin, elem_size, leq);
        swap(A+(begin+2)*elem_size, A+c*elem_size, elem_size);
    }

    return select_index(A, chunks, chunks/2, elem_size, leq);
}

unsigned int select_index(void *A, const unsigned int n, 
                          const unsigned int i,
                          const size_t elem_size, 
                          total_order_type leq)
{
    if(n<= 10){
        insertion_sort(A, n, elem_size,leq);
        return i;
    }
    unsigned int p = select_pivot(A, n, elem_size, leq);
    int *k = new_partition(A, elem_size, 0, n, p, leq);

    if (i<k[0]){
        return select_index(A, k[0] , i, elem_size, leq);
    }
    if(i>k[1]){
	    return select_index(A+(k[1]+1)*elem_size, n-k[1], i, elem_size, leq);	
    }

    return i;
}

void quick_sort_aux_select(void *A, unsigned int i,
                           const unsigned int n,
                           const size_t elem_size,
                           total_order_type leq)
{
	while(i<n){
        int p = i + select_pivot(A+i*elem_size, n - i, elem_size, leq);//
		int *k = new_partition(A, elem_size, i, n, p, leq);
		quick_sort_aux_select(A, i, k[0], elem_size, leq);
		i = k[1]+1; //tail recursion
		//quick_sort_aux(A, p+1, n, elem_size, leq); 
	}
    //free(k);	
}

void quick_sort_select(void *A, const unsigned int n, 
                       const size_t elem_size, 
                       total_order_type leq)
{
   quick_sort_aux_select(A,0,n, elem_size, leq);
}


