#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <matrix.h>
#include <strassen.h>
#include <generalization_strassen.h>

double measure_time(const struct timespec end, const struct timespec start){
	return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1E9;
}


int main() { 
	srand(11);
	//FILE *f = fopen("results", "w");
	//fprintf(f, "n\t strassen \t improvement \t same\n"); 
	//for(size_t i = 8; i < 13; i++){
	size_t n = (1<<9);
	float **A = allocate_random_matrix(n, n);
	float **B = allocate_random_matrix(n, n);
	float **C = allocate_matrix(n, n);
	float **D = allocate_matrix(n, n);	

	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME, &start); 
	naive_matrix_multiplication(C, A, B, n);
	clock_gettime(CLOCK_REALTIME, &end);
	double t = measure_time(end, start);
	printf("The time required to perform the first implementation of strassen algorithm is: %lf \n", t);
	
	clock_gettime(CLOCK_REALTIME, &start);
	improved_strassen_matrix_multiplication(D, A, B, n);
	clock_gettime(CLOCK_REALTIME, &end);
	double t1 = measure_time(end, start);
	printf("The time required to perform the my implementation of strassen algorithm is: %lf \n", t1);
	
	printf("Is the same?: %d\n",same_matrix(D, C, n, n));	
	//fprintf(f, "2^%zu \t%lf \t%lf \t%d\n", i, t, t1, same_matrix(D,C,n,n));
	deallocate_matrix(C,n);
	deallocate_matrix(D,n);
	deallocate_matrix(A,n);
	deallocate_matrix(B,n);	
	
	//}
	//fclose(f);
	
	//Example with square matrix

	size_t nn = 509;
	float **A1 = allocate_random_matrix(nn, nn);
	float **B1 = allocate_random_matrix(nn, nn);
	float **C1 = allocate_matrix(nn, nn);
	float **D1 = allocate_matrix(nn, nn);

	naive_matrix_multiplication(C1, A1, B1, nn);

	square_strassen_matrix_multiplication(D1, A1, B1, nn);

	printf("Is the same?: %d\n",same_matrix(D1, C1, nn, nn));

	deallocate_matrix(C1,nn);
	deallocate_matrix(D1,nn);
	deallocate_matrix(A1,nn);
	deallocate_matrix(B1,nn);	


	//Example with rectangula matrices
	size_t n1 = 500;
	size_t n2 = 530;
	size_t n3 = 320;

	float** A2 = allocate_random_matrix(n1, n2);
	float** B2 = allocate_random_matrix(n2, n3);
	float** C2 = allocate_matrix(n1, n3);
	float** D2 = allocate_matrix(n1, n3);

	naive_rectangular_matrix_multiplication(C2, A2, B2, n1, n3, n2);

	rectangular_strassen_matrix_multiplication(D2, A2, B2, n1, n2, n3);

	printf("Is the same?: %d\n",same_matrix(D2, C2, n1, n3));
	return 0;
}
	
