
all: strassen heap sort

strassen: 
		gcc Strassen_Algorithm/main.c Strassen_Algorithm/strassen.c Strassen_Algorithm/matrix.c -o strassen.x

heap:
		gcc -I ./Heaps/include/  -std=c11 ./Heaps/tests/test_delete_min.c ./Heaps/src/binheap.c ./Heaps/src/total_orders.c ./Heaps/tests/common/array_functions.c ./Heaps/tests/common/heap_functions.c ./Heaps/tests/common/test_set.c ./Heaps/tests/common/test_time.c -o test_delete_min.x
		gcc -I ./Heaps/include/ -std=c11 ./Heaps/tests/test_insert.c ./Heaps/src/binheap.c ./Heaps/src/total_orders.c ./Heaps/tests/common/test_time.c -o test_insert.x

		gcc -I ./Heaps2/include/ -std=c11 ./Heaps2/tests/test_delete_min.c ./Heaps2/src/binheap.c ./Heaps2/src/total_orders.c ./Heaps2/tests/common/array_functions.c ./Heaps2/tests/common/heap_functions.c ./Heaps2/tests/common/test_set.c ./Heaps2/tests/common/test_time.c -o test2_delete_min.x
		gcc -I ./Heaps2/include/ -std=c11 ./Heaps2/tests/test_insert.c ./Heaps2/src/binheap.c ./Heaps2/src/total_orders.c ./Heaps2/tests/common/test_time.c -o test2_insert.x

sort:
		gcc -I./Sort1/include/ Sort1/src/main.c Sort1/src/binheap.c Sort1/src/bubble_sort.c Sort1/src/heap_sort.c Sort1/src/insertion_sort.c Sort1/src/quick_sort.c Sort1/src/select.c Sort1/src/selection_sort.c Sort1/src/swap.c Sort1/src/total_order.c Sort1/src/utilities.c -o sort.x

#sort2

.Phony: all clean
clean: 
	@rm *.x

