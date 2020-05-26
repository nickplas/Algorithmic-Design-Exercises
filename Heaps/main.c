#include <stdio.h>
#include <stdlib.h>
#include "binheap.h"
#include <time.h>

#define MAX_VALUE 100000

double measure_time(const struct timespec end, const struct timespec start){
        return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1E9;
}

int main(){
	
	struct timespec end, start;

	const unsigned int n = 10000;
	int *random_array= (int*)malloc(sizeof(int)*n);	
	for(size_t i = 0; i<n; i++){
		random_array[i] =(rand()%10); 
	}
	//time to build a heap with a given array
	clock_gettime(CLOCK_REALTIME, &start);
	binheap_type *H = build_heap(random_array, n, MAX_VALUE, sizeof(int), leq_int);
	clock_gettime(CLOCK_REALTIME, &end);
	printf("The execution time required to build a heap is: %lf\n", measure_time(end, start));
	//time to insert those values
	int *empty_array= (int*)malloc(sizeof(int)*n);
	clock_gettime(CLOCK_REALTIME, &start);
	binheap_type *H1 = build_heap(empty_array, 0, MAX_VALUE, sizeof(int), leq_int);
	for(size_t i = 0; i<n; i++){
		insert_value(H1, &random_array[i]);
	}
	clock_gettime(CLOCK_REALTIME, &end);
        printf("The execution time required to build the heap through the insertion of %d values is: %lf\n", n, measure_time(end, start));	
	delete_heap(H);
	delete_heap(H1);
	free(random_array);
	free(empty_array);
	return 0;	
}
