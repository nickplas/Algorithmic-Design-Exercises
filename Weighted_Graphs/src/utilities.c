#include<utilities.h>

int *get_random_int_array(const unsigned int n) //fix random values
{
  
  int *A=(int *)malloc(sizeof(int)*n);
  
  srand(10);
  for (unsigned int i = 0; i < n; i++) {
    A[i] = (rand() - RAND_MAX / 2) % n*n;
  }

  return A;
}

int **get_random_int_matrix(const unsigned n) //fix random values
{
  int **mat = (int **)malloc(n * sizeof(int*));
  for(int i = 0; i < n; i++){ 
    mat[i] = (int *)malloc(n * sizeof(int));
  }

  srand(10);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      mat[i][j] = (rand() - RAND_MAX / 2);
    }
  }
  return mat;
}