#ifndef __UTILITIES__
#define __UTILITIES__

#include <stdlib.h>
#include <time.h>
#include <queue.h>
#include <graph.h>

int *get_random_int_array(const unsigned int n);
int **get_random_int_matrix(const unsigned n, const unsigned int max);
void print_nodes(graph* A, int size);
void print_matrix(int** A, int size);
double measure_time(const struct timespec end, const struct timespec start);

#endif