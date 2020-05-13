#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"
#include "strassen.h"

void random_matrix(float **A, const size_t rows, const size_t cols){
   for (size_t i=0; i< rows; i++) {
     for (size_t j=0; j< cols; j++) {
   	   A[i][j] = rand()%10;          //just to get smaller numbers
     }
   }
} 

double measure_time(const struct timespec end, const struct timespec start){
	return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1E9;
}

int main() { 
	size_t n = (1<<9);
	float **A = allocate_matrix(n, n);
	float **B = allocate_matrix(n, n);
	float **C = allocate_matrix(n, n);
	float **D = allocate_matrix(n ,n);	
	srand(11);
	random_matrix(A, n, n);
	random_matrix(B, n, n);

	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME, &start); 
	strassen_matrix_multiplication(C, A, B, n);
	clock_gettime(CLOCK_REALTIME, &end);
	printf("The time required to perform the first implementation of strassen algorithm is: %lf \n", measure_time(end, start));
	
	clock_gettime(CLOCK_REALTIME, &start);
	test(D, A, B, n);
	clock_gettime(CLOCK_REALTIME, &end);
	printf("The time required to perform the my implementation of strassen algorithm is: %lf \n", measure_time(end, start));
	
	printf("Is the same?: %d\n",same_matrix(D, C, n, n));	

	deallocate_matrix(C,n);
	deallocate_matrix(D,n);
	deallocate_matrix(A,n);
	deallocate_matrix(B,n);	
	

	return 0;
}
	
