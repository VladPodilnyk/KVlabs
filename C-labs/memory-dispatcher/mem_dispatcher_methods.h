/***********************************
* file: mem_dispatcher_maethods.h
* written: 03/11/2015
* last modified:
* synopsis: memory dispatcher interface
* author: Vlad Podilnyk
************************************/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define HEAP_SIZE 10

typedef  enum { FREE, ALLOCATED } STATUS;

typedef struct tag_mem_chunk {
	int id;
	int size;
	STATUS status;
	struct tag_mem_chunk* next;
}mem_chunk;

typedef struct {
	int last_id_used;
	mem_chunk* first;//pointer to the first memory block
}mem_dispatcher;

//function prototypes

void init(mem_dispatcher *md);
int allocate(mem_dispatcher *md, int size);
int deallocate(mem_dispatcher *md, int block_id); 
void defragment(mem_dispatcher *md);
void show_memory_map(mem_dispatcher *md);
