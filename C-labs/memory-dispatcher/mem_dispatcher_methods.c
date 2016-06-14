/***********************************
* file: mem_dispatcher_maethods.c
* written: 03/11/2015
* last modified:
* synopsis: memory dispatcher's function defines
* author: Vlad Podilnyk
************************************/
#include "mem_dispatcher_methods.h"

//defenitions of memory dispatcher's functions

//creates a heap as a single free block  with id 0 and HEAP_SIZE size
void init(mem_dispatcher *md) {
	md->first = (mem_chunk*)malloc(sizeof(mem_chunk));
	md->first->id = 0;
	md->first->size = HEAP_SIZE;
	md->first->status = FREE;
	md->first->next = NULL;
	md->last_id_used = 0;
}

//returns block id if allocated and -1 otherwise
int allocate(mem_dispatcher *md, int size) {
	mem_chunk *check_ptr = NULL, *tmp_ptr = NULL;
	int min_size;
	if (size > HEAP_SIZE)
		return -1;
	//search for a min element in a list
	check_ptr = md->first;
	tmp_ptr = md->first;
	min_size = check_ptr->size;
	while (check_ptr) {
		if ((check_ptr->status == FREE) && (check_ptr->size < min_size)) {
			min_size = check_ptr->size;
			tmp_ptr = check_ptr;
		}
		check_ptr = check_ptr->next;
	}
	//allocate memory for a  new memory block
	if (size < tmp_ptr->size) {
		check_ptr = (mem_chunk*)malloc(sizeof(mem_chunk));
		check_ptr->next = tmp_ptr->next;
		tmp_ptr->next = check_ptr;
		tmp_ptr->size -= size;
		check_ptr->size = size;
		check_ptr->status = ALLOCATED;
		md->last_id_used++;
		check_ptr->id = md->last_id_used;
		md->last_id_used = check_ptr->id;
	} 
	else 
		if (size == tmp_ptr->size) tmp_ptr->status = ALLOCATED;
		else return -1;

	check_ptr = NULL;
	tmp_ptr = NULL;
	return md->last_id_used;
}

//returns nonnegative value if block is deallocated and -1 otherwise
int deallocate(mem_dispatcher *md, int block_id) {
	mem_chunk *search_ptr = NULL, *tmp_ptr = NULL;
	search_ptr = md->first;
	if ((search_ptr->id == block_id) && (search_ptr->status == ALLOCATED)) {
		if ((search_ptr->next) && (search_ptr->next->status == FREE)) {
			search_ptr->size += search_ptr->next->size;
			tmp_ptr = search_ptr->next;
			search_ptr->next = search_ptr->next->next;
			free(tmp_ptr);
			tmp_ptr = NULL;
			search_ptr->status = FREE;
		}
		else {
			search_ptr->status = FREE;
			return 0;
		}
	}
	else if (search_ptr->id == block_id) return -1;

	while (search_ptr) {
		if ((search_ptr->next) && (search_ptr->next->id == block_id) && (search_ptr->next->status == ALLOCATED)) {
			if (search_ptr->status == FREE) {
				tmp_ptr = search_ptr->next;
				search_ptr->size += tmp_ptr->size;
				if ((tmp_ptr->next) && (tmp_ptr->next->status == FREE)) {
					search_ptr->size += tmp_ptr->next->size;
					search_ptr->next = tmp_ptr->next->next;
					free(tmp_ptr->next);
					free(tmp_ptr);
				}
				else {
					search_ptr->next = tmp_ptr->next;
					free(tmp_ptr);
				}
			}
			else {
				search_ptr = search_ptr->next;
				if ((search_ptr->next) && (search_ptr->next->status == FREE)) {
					tmp_ptr = search_ptr->next;
					search_ptr->size += tmp_ptr->size;
					search_ptr->next = tmp_ptr->next;
					free(tmp_ptr);
				}
				else search_ptr->status = FREE;
			}
		}
		else 
			if ((search_ptr->next) && (search_ptr->next->id == block_id))  return -1;
		search_ptr = search_ptr->next;
	}
	if (!search_ptr)
		return -1;
	return 0;
} 

//reunites free blocks that were previously stored in various parts of a heap //into one successive block 
void defragment(mem_dispatcher *md) {
	mem_chunk *search_ptr = NULL, *tmp_ptr = NULL, *del_ptr = NULL;
	search_ptr = md->first;
	while (search_ptr) {
		if (search_ptr->status == FREE) {
			tmp_ptr = search_ptr;
			break;
	    }
		search_ptr = search_ptr->next;
	}
	
	while (tmp_ptr) {
		if ((tmp_ptr->next) && (tmp_ptr->next->status == FREE)) {
			search_ptr->size += tmp_ptr->next->size;
			del_ptr = tmp_ptr->next;
			tmp_ptr->next = del_ptr->next;
			free(del_ptr);
			del_ptr = NULL;
		}
		tmp_ptr = tmp_ptr->next;
	}
}

//displays heap status
void show_memory_map(mem_dispatcher *md) {
	mem_chunk *pointer = md->first;
	while (pointer) {
		printf("block id: %d\n", pointer->id);
		printf("%18s", "size:");
		printf("%2d\n", pointer->size);
		if (pointer->status == ALLOCATED) {
			printf("%20s", "status:");
			printf("%10s\n", "alloctated");
		}
		else {
			printf("%20s", "status:");
			printf("%5s\n", "free");
		}
		pointer = pointer->next;
	}
}