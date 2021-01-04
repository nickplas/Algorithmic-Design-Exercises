#ifndef __STRASSEN__

void sub_matrix_blocks(float **C, float **A, float **B,
               	       const size_t C_f_row, const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t n);

void sum_matrix_blocks(float **C, float **A, float **B,
			const size_t C_f_row, const size_t C_f_col,
			const size_t A_f_row, const size_t A_f_col,
			const size_t B_f_row, const size_t B_f_col,
			const size_t n);

void naive_aux(float **C, float **A, float **B, 
               const size_t C_f_row, const size_t C_f_col,
               const size_t A_f_row, const size_t A_f_col,
               const size_t B_f_row, const size_t B_f_col,
               const size_t n);

void strassen_matrix_multiplication(float **C, float **A,
                                    float **B, size_t n);

void improved_strassen(float **C, float **A, float **B,
                       const size_t C_f_row, const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t n);

void improved_strassen_matrix_multiplication(float **C, float **A, float **B, size_t n);

#endif //__STRASSEN__

