#include "matrix.h"

void sub_matrix_blocks(float **C, float **A, float **B,
               	       const size_t C_f_row, const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t n){
	for (size_t y = 0; y<n; y++){
		for(size_t x=0; x<n; x++){
			C[y+C_f_row][x+C_f_col]= A[y+A_f_row][x+A_f_col] - B[y+B_f_row][x+B_f_col];
		}
	}	
}

void sum_matrix_blocks(float **C, float **A, float **B,
			const size_t C_f_row, const size_t C_f_col,
			const size_t A_f_row, const size_t A_f_col,
			const size_t B_f_row, const size_t B_f_col,
			const size_t n){
	for(size_t y=0; y<n; y++){
		for(size_t x=0; x<n; x++){
			C[y+C_f_row][x+C_f_col]= A[y+A_f_row][x+A_f_col] + B[y+B_f_row][x+B_f_col];
		}
	}

}

void naive_aux(float **C, float **A, float **B, 
               const size_t C_f_row, const size_t C_f_col,
               const size_t A_f_row, const size_t A_f_col,
               const size_t B_f_row, const size_t B_f_col,
               const size_t n){
	for (size_t y = 0; y < n; y++){
		for (size_t x = 0; x < n; x++){
        	float value = 0.0; 
        		for (size_t z = 0; z < n; z++){
            			value += A[y+A_f_row][z+A_f_col]*B[z+B_f_row][x+B_f_col];
          		}
        		C[y+C_f_row][x+C_f_col] = value;
                }
	}


}


void strassen_aux(float **C, float **A, float **B, 
		  const size_t C_f_row, const size_t C_f_col,
		  const size_t A_f_row, const size_t A_f_col,
		  const size_t B_f_row, const size_t B_f_col,
		  const size_t n){
	if(n<=128){
		naive_aux(C, A, B, 
			  C_f_row, C_f_col,
			  A_f_row, A_f_col,
			  B_f_row, B_f_col,
			  n);
		return;
	}

	size_t n2= n/2; //size of the blocks
	float ***S = (float ***)malloc(sizeof(float **)*10);// array/pointer of matrices
	for(size_t i = 0; i<10; i++){
		S[i] = allocate_matrix(n2, n2);
	}
	float ***P = (float ***)malloc(sizeof(float **)*7);
	for(size_t i =0; i<7; i++){
		P[i]=allocate_matrix(n2,n2);
	}

	//S1
	sub_matrix_blocks(S[0], B, B,
			  0, 0,
			  B_f_row,B_f_col+n2, 
			  B_f_row+n2, B_f_col+n2,
			  n2);
	//P1
	strassen_aux(P[0], A, S[0], 
		     0,0,
		     A_f_row, A_f_col,
		     0,0,
		     n2);
	//S2
	sum_matrix_blocks(S[1], A, A,
                          0, 0, 
                          A_f_row,A_f_col,
                          A_f_row, A_f_col+n2, 
                          n2);
	//P2
	strassen_aux(P[1], S[1], B,
                    0,0,
                    0,0,
                    B_f_row+n2,B_f_col +n2,
                    n2);
	//S3
	sum_matrix_blocks(S[2], A, A,
                          0, 0,
                          A_f_row+n2, A_f_col,
                          A_f_row+n2, A_f_col+n2,
                          n2);
	//P3
	strassen_aux(P[2], S[2], B,
                    0,0,
                    0,0,
                    B_f_row, B_f_col,
                    n2);
	//S4
	sub_matrix_blocks(S[3], B, B,
                          0, 0,
                          B_f_row+n2, B_f_col,
                          B_f_row, B_f_col,
                          n2);
	//P4
	strassen_aux(P[3], A, S[3], 
                    0,0,
		    A_f_row+n2, A_f_col+n2,
                    0,0,
                    n2);
	//S5
	sum_matrix_blocks(S[4], A, A,
                          0, 0,
                          A_f_row, A_f_col,
                          A_f_row+n2, A_f_col+n2,
                          n2);
	//S6
	sum_matrix_blocks(S[5], B, B,
                          0, 0,
                          B_f_row, B_f_col,
                          B_f_row + n2, B_f_col + n2,
                          n2);
	//P5
	strassen_aux(P[4], S[4], S[5],
                    0, 0,
                    0, 0,
                    0, 0,
                    n2);
	//S7
	sub_matrix_blocks(S[6], A, A,
                          0, 0,
                          A_f_row, A_f_col + n2,
                          A_f_row + n2, A_f_col + n2,
                          n2);
	//S8
	sum_matrix_blocks(S[7], B, B,
                          0, 0,
                          B_f_row + n2, B_f_col,
                          B_f_row + n2, B_f_col + n2,
                          n2);
	//P6
	strassen_aux(P[5], S[6], S[7],
                    0,0,
                    0,0,
                    0,0,
                    n2);

	//S9
	sub_matrix_blocks(S[8], A, A,
                          0, 0,
                          A_f_row, A_f_col,
                          A_f_row + n2, A_f_col,
                          n2);
	//S10
	sum_matrix_blocks(S[9], B, B,
                          0, 0,
                          B_f_row, B_f_col,
                          B_f_row, B_f_col + n2,
                          n2);
	//P7
	strassen_aux(P[6], S[8], S[9],
                    0,0,
                    0,0,
                    0,0,
                    n2);
	//C11
	sum_matrix_blocks(C, P[4], P[3],
			  C_f_row, C_f_col,
			  0, 0,
			  0, 0,
			  n2);

	sub_matrix_blocks(C, C, P[1],
                          C_f_row, C_f_col,
                          C_f_row, C_f_col,
                          0, 0,
                          n2);

	sum_matrix_blocks(C, C, P[5],
                          C_f_row, C_f_col,
                          C_f_row, C_f_col,
                          0, 0,
                          n2);
	//C12
	sum_matrix_blocks(C, P[0], P[1],
                          C_f_row, C_f_col+n2,
                          0, 0,
                          0, 0,
                          n2);
	//C21
	sum_matrix_blocks(C, P[2], P[3],
                          C_f_row+n2, C_f_col,
                          0, 0,
                          0, 0,
                          n2);
	//C22
	sum_matrix_blocks(C, P[4], P[0],
                          C_f_row+n2, C_f_col+n2,
                          0, 0,
                          0, 0,
                          n2);

        sub_matrix_blocks(C, C, P[2],
                          C_f_row+n2, C_f_col+n2,
                          C_f_row+n2, C_f_col+n2,
                          0, 0,
                          n2);

        sub_matrix_blocks(C, C, P[6],
                          C_f_row+n2, C_f_col+n2,
                          C_f_row+n2, C_f_col+n2,
                          0, 0,
                          n2);

	for(size_t i = 0; i<10; i++){
                deallocate_matrix(S[i], n2);
        }
	free(S);
        
        for(size_t i =0; i<7; i++){
                deallocate_matrix(P[i],n2);
        }
	free(P);


}

void improved_strassen(float **C, float **A, float **B,
                       const size_t C_f_row, const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t n){
        if(n<=128){
                naive_aux(C, A, B,
                          C_f_row, C_f_col,
                          A_f_row, A_f_col,
                          B_f_row, B_f_col,
                          n);
                return;
        }
        size_t n2= n/2;
        float ***S = (float ***)malloc(sizeof(float **)*10);
	
	//Basically we improve allocation by reducing
	//its number and using the same matrix for
	//storing different values.
	
        //allocate only 2 S matrices because we need
        //only 2 of them at the same time to perform
        //the calculations
	for(size_t i = 0; i<2; i++){
                S[i] = allocate_matrix(n2, n2);
        }

	//allocate only 4 P matrices for the same
	//reason
	float ***P = (float ***)malloc(sizeof(float **)*7);
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
	improved_strassen(P[0], S[0], S[1],
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
	improved_strassen(P[1], A, S[0],
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
	improved_strassen(P[2], S[1], B,
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
	improved_strassen(P[3], S[0], S[1],
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
	improved_strassen(P[3], A, S[0],
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
	improved_strassen(P[2], S[1], B,
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
	improved_strassen(P[1], S[0], S[1],
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
	
}

void test(float **C, float **A,
          float **B, size_t n){
	improved_strassen(C, A, B,
			  0, 0,
			  0, 0,
			  0, 0,
			  n);
}

void strassen_matrix_multiplication(float **C, float **A,
                                    float **B, size_t n) 
{
	strassen_aux(C, A, B, 
		     0, 0,
		     0, 0,
		     0, 0,
		     n); 
}
