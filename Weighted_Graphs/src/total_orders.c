#include <stdlib.h>
#include <total_orders.h>
#include <queue.h>

int leq_float(const void *a, const void *b)
{
  return *((float*)a)<=*((float*)b);
}

int leq_int(const void *a, const void *b)
{
  return *((int*)a)<=*((int*)b);
}

int geq_int(const void *a, const void *b)
{
  return *((int*)a)>=*((int*)b);
}

int leq_int_node(const void* v1, const void* v2){
    node* n1 = (node*) v1;
    node* n2 = (node*) v2;
    return leq_int((void*)&n1->value, (void*)&n2->value);
}