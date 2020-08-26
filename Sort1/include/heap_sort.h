#ifndef __HEAP_SORT__
#define __HEAP_SORT__

#include <stdlib.h>

#include "total_order.h"

void heap_sort(void *A, const unsigned int n, 
               const size_t elem_size, 
               total_order_type leq);

#endif
