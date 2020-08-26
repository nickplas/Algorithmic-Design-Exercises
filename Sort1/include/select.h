#ifndef __SELECT__
#define __SELECT__

#include <stdlib.h>

#include "total_order.h"

unsigned int select_index(void *A, const unsigned int n, 
                          const unsigned int i,
                          const size_t elem_size, 
                          total_order_type leq);

void quick_sort_select(void *A, const unsigned int n, 
                       const size_t elem_size, 
                       total_order_type leq);

#endif 
