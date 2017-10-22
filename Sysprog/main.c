#include "mem_allocator.h"

int main() {
	// some code here;
	void *ptr1, *ptr2, *ptr3, *ptr4,*ptr5,*ptr6, *ptr;
	init_buffer();
	printf("%i\n", sizeof(header_t));
	ptr1 = mem_alloc(10);
	ptr2 = mem_alloc(20);
	ptr3 = mem_alloc(40);
	//ptr4 = mem_alloc(3);
	//ptr5 = mem_alloc(12);
	//ptr6 = mem_alloc(25);
	print_mem_map();
	printf("\n");
	mem_realloc(ptr3, 2);
	//mem_free(ptr1);
	//mem_free(ptr3);
	//print_mem_map();
	//printf("\n");
	//mem_free(ptr2);
	print_mem_map();
	dealloc_buffer();
	
    return 0;
}