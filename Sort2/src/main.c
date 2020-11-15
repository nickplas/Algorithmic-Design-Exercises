#include <stdio.h>

#include <insertion_sort.h>
#include <quick_sort.h>
#include <select.h>
#include <bubble_sort.h>
#include <selection_sort.h>
#include <heap_sort.h>
#include <utilities.h>
#include <binheap.h>

#define MAX_SIZE_ALL (1<<10) //13 is the result we want, 10 for debugging
#define MAX_SIZE_NLOGN (1<<15) //20 is the result we want, 15 for debugging
#define ARRAY_SIZE (1<<23)

#define NUM_OF_REPETITIONS 15

void test_and_print(void (*sort)(void *A, const unsigned int n, 
                         const size_t elem_size, 
                         total_order_type leq), 
                    const void *A, const unsigned int n, 
                    const size_t elem_size, total_order_type leq, 
                    const unsigned int rep, FILE* f)
{
    int sorted;
    double time = test(sort,A,n,elem_size,leq,rep,&sorted);
    printf("\t%lf", time);
    fprintf(f, "\t%lf", time);
    if (!sorted) {
        printf(" (KO)");
    }
    fflush(stdout);
}


int main(int argc, char *argv[])
{
    int *A=get_random_int_array(ARRAY_SIZE);
    int *A_sorted=malloc(sizeof(int)*ARRAY_SIZE);
    int *A_rev_sorted=malloc(sizeof(int)*ARRAY_SIZE);

    for (unsigned int i=0; i<ARRAY_SIZE; i++) {
        A_sorted[i]=i;
        A_rev_sorted[i]=ARRAY_SIZE-i;
    }

    FILE* f;
    f = fopen("results.txt", "w");

    unsigned int i;

    fprintf(f, "Size\tInsertion Sort\t          \t        \n");
    fprintf(f, "    \t(Random Case)\t(Best Case)\t(Worst Case)");
    printf("Size\tInsertion Sort\t          \t        \n");
    printf("    \t(Random Case)\t(Best Case)\t(Worst Case)");
    for (i=2; (1<<i)<=MAX_SIZE_ALL; i++) {
        const unsigned int A_size=1<<i;
        fprintf(f, "\n2^%d",i);
        printf("\n2^%d",i);
        test_and_print(insertion_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f);
        test_and_print(insertion_sort, A_sorted,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f);
        test_and_print(insertion_sort, A_rev_sorted,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f);
    }
    fprintf(f, "\n\n\n");
    printf("\n\n\n");

    
    
    fprintf(f, "Size \tQuickSort            \tQuick Sort + Select\n");
    fprintf(f, "    \t(Random Case)\t(Worst Case)\t(Random Case)\t(Worst Case)");
    printf("Size\tQuick Sort\t            \tQuick Sort + Select\n ");
    printf("    \t(Random Case)\t(Worst Case)\t(Random Case)\t(Worst Case)");
    for (i=2; (1<<i)<=MAX_SIZE_ALL; i++) {
        const unsigned int A_size=1<<i;
        fprintf(f, "\n2^%d",i);
        printf("\n2^%d",i);
        test_and_print(quick_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f);
        test_and_print(quick_sort, A_sorted,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f);
        test_and_print(quick_sort_select, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f);
        test_and_print(quick_sort_select, A_sorted,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f);
    }
    fprintf(f, "\n\n\n");
    printf("\n\n\n");
    
    fprintf(f, "Size\tInsertion Sort\tQuick Sort\tBubble Sort\tSelection Sort\tHeap Sort\n");
    fprintf(f, "    \t(Random Case)\t(Random Case)\t\t\t");
    printf("Size\tInsertion Sort\tQuick Sort\tBubble Sort\tSelection Sort\tHeap Sort\n");
    printf("    \t(Random Case)\t(Random Case)\t\t\t");
    for (i=2; (1<<i)<=MAX_SIZE_ALL; i++) {
        const unsigned int A_size=1<<i;
        fprintf(f, "\n2^%d",i);
        printf("\n2^%d",i);
        test_and_print(insertion_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f);
        test_and_print(quick_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f);
        test_and_print(bubble_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f);
        test_and_print(selection_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f);
        test_and_print(heap_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f);
    }
    fprintf(f, "\n\n\n");
    printf("\n\n\n");
    
    printf("Size\tQuick Sort\tQuick Sort +\tHeap Sort\n");
    printf("    \t          \t  Select\n");
    printf("    \t(Random Case)\t(Random Case)\t");

    fprintf(f, "Size\tQuick Sort\tQuick Sort +\tHeap Sort\n");
    fprintf(f, "    \t          \t  Select\n");
    fprintf(f, "    \t(Random Case)\t(Random Case)\t");
    printf("Size\tQuick Sort\tQuick Sort +\tHeap Sort\n");
    printf("    \t          \t  Select\n");
    printf("    \t(Random Case)\t(Random Case)\t");
    for (; (1<<i)<=MAX_SIZE_NLOGN; i++) {
        const unsigned int A_size=1<<i;
        fprintf(f, "\n2^%d",i);
        printf("\n2^%d",i);
        test_and_print(quick_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f);
        test_and_print(quick_sort_select, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f);
        test_and_print(heap_sort, A,
                       A_size, sizeof(int),
                       leq_int, NUM_OF_REPETITIONS, f);
    }

    fprintf(f, "\n");
    printf("\n");
    

    free(A);
    free(A_sorted);
    free(A_rev_sorted);

    return 0;
}
