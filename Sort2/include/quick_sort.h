#ifndef __QUICK_SORT__
#define __QUICK_SORT__

#include <stdlib.h>

#include "total_order.h"

int* new_partition(void *A, const size_t elem_size, size_t i, size_t j ,size_t p, total_order_type leq);

void quick_sort(void *A, const unsigned int n, 
                const size_t elem_size, 
                total_order_type leq);

#endif
