#include "mem_allocator.h"

header_t *head = NULL, *tail = NULL;
pthread_mutex_t global_lock;

void mem_free(void *mem_block) {
	header_t *blk_header, *tmp;
	void *program_break;

	if (!mem_block)
		return;
	pthread_mutex_lock(&global_lock);
	blk_header = (header_t*)mem_block - 1;
	program_break = sbrk(0);

	if ((char*)mem_block + blk_header->size == program_break) {
		if (head == tail) {
			head = tail = NULL;
		} 
		else {
			tail = tail->prev;
			tail->next = NULL;
			if (tail->is_free) {
				if (head == tail) 
					head = tail = NULL;
				else {
					blk_header->size += tail->size;
					tail = tail->prev;
					tail->next = NULL;
				}
				sbrk(-blk_header->size - 2*sizeof(header_t));
				pthread_mutex_unlock(&global_lock);
				return;
			}
		}

		sbrk(-blk_header->size - sizeof(header_t));
		pthread_mutex_unlock(&global_lock);
		return;
	}

	blk_header->is_free = FREE;
	if (blk_header->prev && blk_header->prev->is_free) {
		tmp = blk_header;
		blk_header = blk_header->prev;
	}
	else 
		tmp = blk_header->next;

	while (tmp->is_free) {
		blk_header->size += tmp->size + sizeof(header_t);
		tmp = tmp->next;
	}
	blk_header->next = tmp;
	tmp->prev = blk_header;
	pthread_mutex_unlock(&global_lock);
}

void *mem_alloc(size_t size) {
	size_t total_size;
	void *mem_block;
	header_t *blk_header;
	if (!size)
		return NULL;
	pthread_mutex_lock(&global_lock);
	blk_header = get_free_block(size);

	if (blk_header) {
		blk_header->is_free = ALLOCATED;
		pthread_mutex_unlock(&global_lock);
		return (void*)(blk_header + 1);
	}

	total_size = sizeof(header_t) + size;
	mem_block = sbrk(total_size);
	if (mem_block == (void*) -1) {
		pthread_mutex_unlock(&global_lock);
		return NULL;
	}

	blk_header = (header_t*)mem_block;
	blk_header->size = size;
	blk_header->is_free = ALLOCATED;
	blk_header->next = NULL;
	blk_header->prev = tail;
	if (!head)
		head = blk_header;
	if (tail)
		tail->next = blk_header;
	tail = blk_header;
	pthread_mutex_unlock(&global_lock);
	return (void*)(blk_header + 1);
}

void *mem_realloc(void *addr, size_t size) {
	header_t *blk_header;
	void *new_block;
	if (!addr)
		return mem_alloc(size);
	
	if (!size)
		return NULL;

	blk_header = (header_t*)addr - 1;
	if (blk_header->size >= size)
		return addr;

	new_block = mem_alloc(size);
	if (new_block) {
		memcpy(new_block, addr, blk_header->size);
		mem_free(addr);
	}

	return new_block;
}


/* A debug function to print the entire link list */
void print_mem_map()
{
	header_t *curr = head;
	printf("head = %p, tail = %p \n", (void*)head, (void*)tail);
	while(curr) {
		printf("addr = %p, size = %zu, is_free=%u, next=%p\n",
			(void*)curr, curr->size, curr->is_free, (void*)curr->next);
		curr = curr->next;
	}
}

header_t *get_free_block(size_t size) {
	header_t *curr = head;
	while(curr) {
		if (curr->is_free && curr->size >= size)
			return curr;
		curr = curr->next;
	}
	return NULL;
}