#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void* mem_alloc(size_t size) {
	int *ptr = (int*)malloc(sizeof(int) * size);
	ptr[0] = 34567;
	return (void*)ptr;
}


int main() {
	//code
	int *arr = (int*)mem_alloc(5);
	printf("%i\n", arr);
	free(arr);
	return 0;
}