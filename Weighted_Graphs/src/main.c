#include<graph.h>
#include<utilities.h>
#include<stdio.h>
#include<total_orders.h>

int main(){
    int n = 10;
    node* A = (node*)malloc(sizeof(node)*n);
    int** E = get_random_int_matrix(n, 9999);
    
    
    graph* g_queue = build_graph(A, E, n);
    graph* g_heap = build_graph(A, E, n);

    //dijkstra_queue(g_queue,&g_queue->V[0]);
    dijkstra_heap(g_heap, &g_heap->V[0]);

    //print_matrix(E, n);
    //print_nodes(g_heap, n);
    //printf("\n");
    //print_nodes(g_heap, n);

    //test time on bihher matrix 1000x1000
    //struct timespec start, end;
    //clock_gettime(CLOCK_REALTIME, &start);
    //dijkstra_queue(g_queue,&g_queue->V[0]);
    //clock_gettime(CLOCK_REALTIME, &end);
    //printf("Queue implementation for Dijkstra algorithm take: %lf seconds \n", measure_time(end, start));
    //clock_gettime(CLOCK_REALTIME, &start);
    //dijkstra_heap(g_heap, &g_heap->V[0]);
    //clock_gettime(CLOCK_REALTIME, &end);
    //printf("Heap implementation for Dijkstra algorithm take: %lf seconds \n", measure_time(end, start));
    //printf("node %d has value %d \n", g_queue->V[1].index, g_queue->V[1].value);
    free(A);
    free(E);
    //free(g_queue);
}


