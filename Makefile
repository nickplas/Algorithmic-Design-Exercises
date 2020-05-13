
all: strassen heap

strassen: 
		gcc Strassen_Algorithm/main.c Strassen_Algorithm/strassen.c Strassen_Algorithm/matrix.c -o strassen.x

heap:
		gcc Heaps/main.c Heaps/binheap.c Heaps/total_orders.c -o heap.x

.Phony: all clean
clean: 
	@rm *.x

