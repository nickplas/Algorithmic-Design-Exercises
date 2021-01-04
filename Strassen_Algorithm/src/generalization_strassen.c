#include <generalization_strassen.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <matrix.h>
#include <strassen.h>
#include <stdio.h>

//debugging
void print_matrix(float** A, size_t size){
  for(size_t i = 0; i < size; i++){
    for(size_t j = 0; j < size; j++){
      printf("%f ", A[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

size_t max_dim(size_t a, size_t b, size_t c){
    size_t max = a;
    if(max < b){
        max = b;
    }

    if(max < c){
        max = c;
    }
    return max;
}

bool is_power_2(size_t x){
    if (x == 0) return false;
    return (ceil(log2(x)) == floor(log2(x)));
}

void naive_rectangular_matrix_multiplication(float** C, float** A, float** B, size_t n1, size_t n2, size_t n3){
    for(size_t i = 0; i < n1; i++){
        for(size_t j = 0; j < n2; j++){
            float value = 0.0;
            for(size_t k = 0; k < n3; k++){
                value += A[i][k]*B[k][j]; 
            }
            C[i][j] = value;
        }
    }
}

float** padding(float** A, size_t rows, size_t cols, size_t A_r, size_t A_c, size_t max){
    float** B;
    if(rows == cols){ //is a square
        B = allocate_matrix(rows+1, cols+1);
    }else{ //is a rectangle
         B = allocate_matrix(max, max);
    }
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++){
            B[i][j] = A[A_r + i][A_c + j];
        }
    }
    return B;

}

float** remove_padding(float**C, float** C_pad, size_t n, size_t n1){
    cpy_submatrix(C, C_pad, n, n1);
    return C;

}

void square_strassen(float** C, float** A, float**B,
                    const size_t C_f_row, const size_t C_f_col,
                    const size_t A_f_row, const size_t A_f_col,
                    const size_t B_f_row, const size_t B_f_col, 
                    size_t n){
    
    if(n<=128){
        naive_aux(C, A, B,
                  C_f_row, C_f_col,
                  A_f_row, A_f_col,
                  B_f_row, B_f_col,
                  n);
                return;
    }
    if(is_power_2(n)){
        improved_strassen(C, A, B,
                          C_f_row, C_f_col,
                          A_f_row, A_f_col,
                          B_f_row, B_f_col,
                          n);
        return;
    }

    if(n % 2 != 0){
        size_t old_n = n;        
        float** A_pad = allocate_matrix(n+1, n+1);
        float** B_pad = allocate_matrix(n+1, n+1);
        float** C_pad = allocate_matrix(n+1, n+1);

        A_pad = padding(A, n, n, A_f_row, A_f_col, 0);
        B_pad = padding(B, n, n, B_f_row, B_f_col, 0);
        n +=1;
                
        if (is_power_2(n)){
            improved_strassen(C_pad, A_pad, B_pad, 0,0,0,0,0,0,n);
            C = remove_padding(C, C_pad, old_n, old_n);
            deallocate_matrix(A_pad, n);
            deallocate_matrix(B_pad, n);
            deallocate_matrix(C_pad, n);
            return;
        }else{
            square_strassen(C_pad, A_pad, B_pad, 0, 0, 0, 0, 0, 0, n);
            C = remove_padding(C, C_pad, old_n, old_n);
            deallocate_matrix(A_pad, n);
            deallocate_matrix(B_pad, n);
            deallocate_matrix(C_pad, n);
            return;
        }
    }

    //printf("Start computation cuz %zu\n", n);
    size_t n2= n/2;
    float*** S = (float ***)malloc(sizeof(float **)*2);
    for(size_t i = 0; i < 2; i++){
        S[i] = allocate_matrix(n2, n2); 
    }
        
    float*** P = (float ***)malloc(sizeof(float **)*4);
    for(size_t i =0; i<4; i++){
        P[i]=allocate_matrix(n2,n2); 
    }

    //C11 = P5 + P4 - P2 + P6
	
    //S5
    sum_matrix_blocks(S[0], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row+n2, A_f_col+n2,
                      n2);

	//S6
    sum_matrix_blocks(S[1], B, B,
                      0, 0,
                      B_f_row, B_f_col,
                      B_f_row+n2, B_f_col+n2,
                      n2);
	    
	//P5 = S5* S6
    square_strassen(P[0], S[0], S[1],
                    0,0,
                    0,0,
                    0,0,
                    n2);

	//S4 = B21 - B11
    sub_matrix_blocks(S[0], B, B,
                      0, 0,
                      B_f_row+n2, B_f_col,
                      B_f_row, B_f_col,
                      n2);

	//P4 = A22 * S4
    square_strassen(P[1], A, S[0],
                    0,0,
               	    A_f_row+n2, A_f_col+n2,
            	    0,0,
                    n2);

	//S2 = A11 + A12
    sum_matrix_blocks(S[1], A, A,
                      0, 0,
                      A_f_row,A_f_col,
                      A_f_row, A_f_col+n2,
                      n2);

	//P2 = S2 * B22
    square_strassen(P[2], S[1], B,
                    0,0,
                	0,0,
                	B_f_row+n2,B_f_col +n2,
                    n2);
	
	//S7 = A12 - A22
	sub_matrix_blocks(S[0], A, A,
                      0, 0,
                      A_f_row, A_f_col + n2,
                      A_f_row + n2, A_f_col + n2,
                      n2);
	
    //S8 = B21 + B22
	sum_matrix_blocks(S[1], B, B,
                      0, 0,
                      B_f_row + n2, B_f_col,
                      B_f_row + n2, B_f_col + n2,
                      n2);

    //P6 = S7 * S8	   
    square_strassen(P[3], S[0], S[1],
                    0,0,
                    0,0,
                    0,0,
                    n2);

	//C11
    sum_matrix_blocks(C, P[0], P[1],
                      C_f_row, C_f_col,
                      0, 0,
                      0, 0,
                      n2);
    sub_matrix_blocks(C, C, P[2],
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      n2);

    sum_matrix_blocks(C, C, P[3],
                      C_f_row, C_f_col,
                      C_f_row, C_f_col,
                      0, 0,
                      n2);
                

	//C12 = P1 + P2
    //P2 is already in P[2]
	//S1 = B12 - B22
    sub_matrix_blocks(S[0], B, B,
                      0, 0,
                      B_f_row,B_f_col+n2,
                      B_f_row+n2, B_f_col+n2,
                      n2);
	//P1 = A11 * S1
    square_strassen(P[3], A, S[0],
                    0,0,
                 	A_f_row, A_f_col,
                    0,0,
                    n2);

	//C12
    sum_matrix_blocks(C, P[3], P[2],
                      C_f_row, C_f_col+n2,
                      0, 0,
                      0, 0,
                      n2);

	//C21 = P3 + P4
    //P4 is already in P[1]
	//S3 = A21 + A22
    sum_matrix_blocks(S[1], A, A,
                      0, 0,
                      A_f_row+n2, A_f_col,
                      A_f_row+n2, A_f_col+n2,
                      n2);
			
	//P3 = S3 * B11
    square_strassen(P[2], S[1], B,
                    0,0,
                    0,0,
                    B_f_row, B_f_col,
                    n2);

	//C21	
    sum_matrix_blocks(C, P[2], P[1],
                      C_f_row+n2, C_f_col,
                      0, 0,
                      0, 0,
                      n2);

	//C22 = P5 + P1 - P3 + P7
    //P1 is in P[3]
	//P5 is in P[0]
    //P3 is in P[2]
	//S9 = A11 - A21 
    sub_matrix_blocks(S[0], A, A,
                      0, 0,
                      A_f_row, A_f_col,
                      A_f_row + n2, A_f_col,
                      n2);
	//S10 = B11 + B12
    sum_matrix_blocks(S[1], B, B,
                      0, 0,
                      B_f_row, B_f_col,
                      B_f_row, B_f_col + n2,
                      n2);
	
	//P7 = S9 * S10 
    square_strassen(P[1], S[0], S[1],
                    0,0,
                    0,0,
                    0,0,
                    n2);

	//C22
    sum_matrix_blocks(C, P[0], P[3],
                      C_f_row+n2, C_f_col+n2,
                      0, 0,
                      0, 0,
                      n2);

    sub_matrix_blocks(C, C, P[2],
                      C_f_row+n2, C_f_col+n2,
                      C_f_row+n2, C_f_col+n2,
                      0, 0,
                      n2);

    sub_matrix_blocks(C, C, P[1],
                      C_f_row+n2, C_f_col+n2,
                      C_f_row+n2, C_f_col+n2,
                      0, 0,
                      n2);


	for(size_t i = 0; i<2; i++){
        deallocate_matrix(S[i], n2);
    }
    free(S);

    for(size_t i =0; i<4; i++){
        deallocate_matrix(P[i],n2);
    }
    free(P);
    return;    
}

void square_strassen_matrix_multiplication(float **C, float **A, float **B, size_t n){
        square_strassen(C, A, B, 0, 0, 0, 0, 0, 0, n);
}

void rectangular_strassen(float **C, float **A, float **B,
                          const size_t C_f_row, const size_t C_f_col,
                          const size_t A_f_row, const size_t A_f_col,
                          const size_t B_f_row, const size_t B_f_col,
                          const size_t n1, const size_t n2, const size_t n3){

    if(n1 == n2 && n2 == n3){
        square_strassen(C, A, B, C_f_row, C_f_col, A_f_row, A_f_col, B_f_row, B_f_col, n1);
    }

    //find the right dimension
    size_t max = max_dim(n1, n2, n3);


    float** A_pad = allocate_matrix(max, max);
    float** B_pad = allocate_matrix(max, max);
    float** C_pad = allocate_matrix(max, max);

    A_pad = padding(A, n1, n2, A_f_row, A_f_col, max);
    B_pad = padding(B, n2, n3, B_f_row, B_f_col, max);

    square_strassen_matrix_multiplication(C_pad, A_pad, B_pad, max);

    C = remove_padding(C, C_pad, n1, n3);
    
    deallocate_matrix(A_pad, max);
    deallocate_matrix(B_pad, max);
    deallocate_matrix(C_pad, max);
    return;
}

void rectangular_strassen_matrix_multiplication(float** C, float** A, float** B, size_t n1, size_t n2, size_t n3){
    rectangular_strassen(C, A, B, 0, 0, 0, 0, 0, 0, n1, n2, n3);
}