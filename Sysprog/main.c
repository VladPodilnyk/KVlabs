#include "mem_allocator.h"

int main() {
	// some code here;
	printf("%i\n", sizeof(header_t));
	void *ptr;
	void *ptr1 = mem_alloc(10);
	void *ptr2 = mem_alloc(23);
	void *ptr3 = mem_alloc(20);
	void *ptr4 = mem_alloc(2);
	void *ptr5 = mem_alloc(6);
	print_mem_map();
	printf("\n\n");
	mem_realloc(ptr2, 20);
	print_mem_map();
	printf("\n\n");
	ptr = mem_realloc(ptr4, 10);
	print_mem_map();
	printf("\n\n");
	mem_free(ptr2);
	mem_free(ptr4);
	mem_free(ptr3);
	mem_free(ptr5);
	mem_free(ptr1);
	mem_free(ptr);
	print_mem_map();
    return 0;
}