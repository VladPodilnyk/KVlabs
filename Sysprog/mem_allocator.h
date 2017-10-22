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

#define TRUE 1
#define FALSE 0
#define dealloc_buffer() (sbrk(-g_buffer_size))

typedef struct {
	unsigned int prev_block_size:31;
	unsigned int is_free:1; 
	unsigned int block_size:32;
} header_t;

//extern header_t *head, *tail;
void *gp_to_buffer;
extern size_t g_buffer_size;
//pthread_mutex_t global_lock;

//
int init_buffer();
//void dealoc_buffer();
// Function allocates memory and returns pointer
void *mem_alloc(size_t size);

// Changes allocated memory size 
void *mem_realloc(void *addr, size_t size);

// Frees allocated memory
void mem_free(void *mem_block);

// Prints memory map;
void print_mem_map();
