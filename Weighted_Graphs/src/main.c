#include<graph.h>
#include<stdlib.h>

#define MAX_SIZE 100

int *get_random_int_array(const unsigned int n) 
{
  
  int *A=(int *)malloc(sizeof(int)*n);
  
  srand(10);
  for (unsigned int i = 0; i < n; i++) {
    A[i] = (rand() - RAND_MAX / 2) % n*n;
  }

  return A;
}

int main(){
    int* A = get_random_int_array(MAX_SIZE);
    return 0;
}