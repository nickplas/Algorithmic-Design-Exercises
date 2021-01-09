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

    dijkstra_queue(g_queue,&g_queue->V[0]);
    dijkstra_heap(g_heap, &g_heap->V[0]);

    // Test if they work
    //print_matrix(E, n);
    //print_nodes(g_queue, n);
    //printf("Now Heaps\n");
    //print_nodes(g_heap, n);

    //Execution time test

    FILE* f = fopen("Results", "w");
    fprintf(f, "Size \t Queue \t\t Heap\n");

    struct timespec start_q, start_h, end_q, end_h;

    for(size_t i = 2; i < 17; i++){
        n = (1<<i);
        printf("Starting Dijkstra with size: %d\n", n);
        A = (node*)malloc(sizeof(node)*n);
        E = get_random_int_matrix(n, 9999);

        g_queue = build_graph(A, E, n);
        g_heap = build_graph(A, E, n);

        clock_gettime(CLOCK_REALTIME, &start_q);
        dijkstra_queue(g_queue,&g_queue->V[0]);
        clock_gettime(CLOCK_REALTIME, &end_q);

        clock_gettime(CLOCK_REALTIME, &start_h);
        dijkstra_heap(g_heap, &g_heap->V[0]);
        clock_gettime(CLOCK_REALTIME, &end_h);

        fprintf(f, "%d \t %lf \t %lf\n", n, measure_time(end_q, start_q), measure_time(end_h, start_h));
    }

    fclose(f);

    free(A);
    free(E);
    free(g_queue);
    free(g_heap);
}


