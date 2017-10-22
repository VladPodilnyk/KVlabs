#include "mem_allocator.h"

size_t g_buffer_size = 1024 * 1024;

int init_buffer() {
	header_t *buffer;
	gp_to_buffer = sbrk(g_buffer_size + 4);
	if (buffer == (void*)-1) {
		g_buffer_size = 0;
		return -1;
	}

	gp_to_buffer = (void*)((size_t)gp_to_buffer + (4 - ((size_t)gp_to_buffer % 4)));
	buffer = (header_t*)gp_to_buffer;
	buffer->prev_block_size = 0;
	buffer->is_free = TRUE;
	buffer->block_size = g_buffer_size;
	return 0;
}


void mem_free(void *mem_block) {
	header_t *current_block, *prev_block, *next_block;

	current_block = (header_t*)mem_block - 1;
	prev_block = (header_t*)((size_t)current_block - current_block->prev_block_size);
	next_block = (header_t*)((size_t)current_block + current_block->block_size);

	current_block->is_free = TRUE;
	if ((current_block != prev_block) && ((size_t)prev_block >= (size_t)gp_to_buffer) 
	&& (prev_block->is_free)) {
		prev_block->block_size += current_block->block_size;
		if ((size_t)next_block < (size_t)gp_to_buffer + g_buffer_size)
			next_block->prev_block_size = prev_block->block_size;
		current_block = prev_block;
	}

	if (((size_t)next_block < (size_t)gp_to_buffer + g_buffer_size) && (next_block->is_free)) {
		current_block->block_size += next_block->block_size;
		if ((size_t)next_block + next_block->block_size < (size_t)gp_to_buffer + g_buffer_size) {
			next_block = (header_t*)((size_t)next_block + next_block->block_size);		
			next_block->prev_block_size = current_block->block_size;
		}
	}
	
}


void *mem_alloc(size_t size) {
	header_t *current_block = (header_t*)gp_to_buffer;
	header_t *next_block;
	size_t old_block_size;
	size_t header_size = sizeof(header_t);
	size_t new_size = size + header_size;

	new_size = new_size + (4 - (new_size % 4));

	while ((size_t)current_block < ((size_t)gp_to_buffer + g_buffer_size)) {
		if ((current_block->is_free) && (current_block->block_size >= new_size)) {
			if (current_block->block_size - new_size <= header_size)
				new_size = current_block->block_size;

			else {
				printf("%i\n", current_block->block_size - new_size);
				next_block = (header_t*)((size_t)current_block + new_size);
				next_block->is_free = TRUE;
				next_block->prev_block_size = new_size;
				next_block->block_size = current_block->block_size - new_size;
				if (((size_t)next_block + next_block->block_size) < ((size_t)gp_to_buffer + g_buffer_size)) {
					next_block = (header_t*)((size_t)next_block + next_block->block_size);
					next_block->prev_block_size = current_block->block_size - new_size;
				}
			}
			current_block->is_free = FALSE;
			current_block->block_size = new_size;
			return (void*)(current_block + 1);
		}
		current_block = (header_t*)((size_t)current_block + current_block->block_size);
	}

	return NULL;
}


void *mem_realloc(void *addr, size_t size) {
	// Fix memory reallocation!!!
	header_t *blk_header, *new_block;
	if (!addr)
		return mem_alloc(size);
	
	if (!size) {
		mem_free(addr);
		return NULL;
	}

	new_block = (header_t*)mem_alloc(size);
	blk_header = new_block - 1;
	if (new_block) {
		memcpy((void*)new_block, addr, blk_header->block_size - sizeof(header_t));
		mem_free(addr);
	}

	return (void*)new_block;
}


/* A debug function to print the entire link list */
void print_mem_map() {
	header_t *curr = (header_t*)gp_to_buffer;
	size_t tail = (size_t)gp_to_buffer + g_buffer_size;
	printf("head = %p, tail = %p \n", (void*)gp_to_buffer, (void*)((size_t)gp_to_buffer + g_buffer_size));
	while((size_t)curr < tail) {
		printf("addr = %p, size = %zu, is_free=%u, prevbsize=%u\n",
			(void*)curr, curr->block_size, curr->is_free, curr->prev_block_size);
		curr = (header_t*)((size_t)curr + curr->block_size);
	}
}
