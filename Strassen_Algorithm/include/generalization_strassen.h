#ifndef __GENERALIZATION_STRASSEN__
#include<stdlib.h>

void naive_rectangular_matrix_multiplication(float** C, float** A, float** B, size_t n1, size_t n2, size_t n3);

float** padding(float** A, size_t rows, size_t cols, size_t A_r, size_t A_c, size_t max);

float** remove_padding(float** C, float** C_pad, size_t n, size_t n1);

void square_strassen(float** C, float** A, float**B, 
                    const size_t C_f_row, const size_t C_f_col,
                    const size_t A_f_row, const size_t A_f_col,
                    const size_t B_f_row, const size_t B_f_col,
                    size_t n);

void square_strassen_matrix_multiplication(float **C, float **A, float **B, size_t n);

void rectangular_strassen(float **C, float **A, float **B,
                          const size_t C_f_row, const size_t C_f_col,
                          const size_t A_f_row, const size_t A_f_col,
                          const size_t B_f_row, const size_t B_f_col,
                          const size_t n1, const size_t n2, const size_t n3);

void rectangular_strassen_matrix_multiplication(float** C, float** A, float** B, size_t n1, size_t n2, size_t n3);

void print_matrix(float** A, size_t size);

#endif