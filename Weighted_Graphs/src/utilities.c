#include<utilities.h>
#include<stdio.h>
#include<queue.h>
#include<graph.h>

int* get_random_int_array(const unsigned int n) //fix random values
{
  
  int* A=(int *)malloc(sizeof(int)*n);
  
  srand(10);
  for (unsigned int i = 0; i < n; i++) {
    A[i] = rand() % 20;
  }

  return A;
}

int** get_random_int_matrix(const unsigned n, const unsigned int max)
{
  int **mat = (int **)malloc(n * sizeof(int*));
  for(int i = 0; i < n; i++){ 
    mat[i] = (int *)malloc(n * sizeof(int));
  }

  srand(10);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      mat[i][j] = (rand() % 20) +1;
      if (mat[i][j] > 16){
        mat[i][j] = max;
      }
    }
  }
  return mat;
}

void print_nodes(graph* G, int size){
  for (size_t i = 0; i < size; i++){
    if (G->V[i].pred == NULL){
      printf("index: %d, value: %d, index of preced: no preced\n", G->V[i].index, G->V[i].value);
    }else{
      printf("index: %d, value: %d, index of preced: %d\n", G->V[i].index, G->V[i].value, G->V[i].pred->index);
    }
  }
}

void print_matrix(int** A, int size){
  for(size_t i = 0; i < size; i++){
    for(size_t j = 0; j < size; j++){
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

double measure_time(const struct timespec end, const struct timespec start){
	return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1E9;
}