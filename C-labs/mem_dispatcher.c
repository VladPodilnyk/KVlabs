#include "mem_dispatcher_methods.h"
int main() {
	mem_dispatcher *md;
	int size, command_type, block_id;
	md = (mem_dispatcher*)malloc(sizeof(mem_dispatcher));
	init(md);
	//program interface
	do {
		printf("%s\n", "1.Allocate");
		printf("%s\n", "2.Deallocate");
		printf("%s\n", "3.Defragment");
		printf("%s\n", "4.Show memory map");
		printf("%s\n", "0.Exit");
		printf("%s", "Enter command: ");
		scanf("%d", &command_type);
		printf("\n");
		switch (command_type) {
			case 0 : break;
			case 1 : 
				printf("%s", "Enter block size: ");
				scanf("%d", &size);
				if (allocate(md, size) == -1)
					printf("%s\n", "Allocation failed");
				break;

			case 2 :
				printf("%s", "Enter block id: ");
				scanf("%d", &block_id);
				if (deallocate(md, block_id) == -1)
					printf("%s\n", "Deallocation failed");
				break;

			case 3 : 
				defragment(md);
				break;
			case 4 :
  				show_memory_map(md);
				break;
			default :
				printf("%s\n","Wrong command");
		}

		printf("\n");
	} while (command_type != 0);

	return 0;
}