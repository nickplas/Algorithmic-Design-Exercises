#ifndef __INSERTION_SORT__
#define __INSERTION_SORT__

#include <stdlib.h>

#include "total_order.h"

void insertion_sort(void *A, const unsigned int n, 
                    const size_t elem_size, 
                    total_order_type leq);

#endif
