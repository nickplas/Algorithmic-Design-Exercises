
all: strassen heap sort

strassen: 
		gcc Strassen_Algorithm/main.c Strassen_Algorithm/strassen.c Strassen_Algorithm/matrix.c -o strassen.x

heap:
		gcc Heaps/main.c Heaps/binheap.c Heaps/total_orders.c -o heap.x

#heap2

sort:
		gcc -I./Sort1/include/ Sort1/src/main.c Sort1/src/binheap.c Sort1/src/bubble_sort.c Sort1/src/heap_sort.c Sort1/src/insertion_sort.c Sort1/src/quick_sort.c Sort1/src/select.c Sort1/src/selection_sort.c Sort1/src/swap.c Sort1/src/total_order.c Sort1/src/utilities.c -o sort.x

#sort2

.Phony: all clean
clean: 
	@rm *.x

