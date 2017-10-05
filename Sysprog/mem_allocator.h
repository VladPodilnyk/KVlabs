/***********************************
* file: mem_dispatcher_maethods.h
* written: 09/25/2017
* last modified: 09/25/2017 
* synopsis: memory allocator interface
* author: Vlad Podilnyk
************************************/

#pragma once
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>


typedef  enum { ALLOCATED, FREE } STATUS;

typedef struct header {
	size_t size;
	STATUS is_free;
	struct header *next;
	struct header *prev;

} header_t;

extern header_t *head, *tail;
//pthread_mutex_t global_lock;

header_t *get_free_block(size_t size);

// Function allocates memory and returns pointer
void *mem_alloc(size_t size);

// Changes allocated memory size 
void *mem_realloc(void *addr, size_t size);

// Frees allocated memory
void mem_free(void *mem_block);

void print_mem_map();