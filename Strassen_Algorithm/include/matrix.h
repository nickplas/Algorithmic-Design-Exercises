#ifndef __MATRIX__
#include <stdlib.h>

void naive_matrix_multiplication(float **C, float **A,
                                float **B,
                                const size_t n);

int same_matrix(float **A, float **B,
                const size_t rows, const size_t cols);

float **allocate_matrix(const size_t rows, const size_t cols);
void deallocate_matrix(float **A, const size_t rows);


float **allocate_random_matrix(const size_t rows, const size_t cols);
#endif
