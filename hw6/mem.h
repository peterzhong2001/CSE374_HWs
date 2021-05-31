// Peter Zhong and Ariel Luo
// CSE 374 HW6
// 05/21/2021

// mem.h is the header file for the clients of the memory manager

#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void* getmem(uintptr_t size);
void freemem(void* p);
void get_mem_stats(
  uintptr_t* total_size,
  uintptr_t* total_free,
  uintptr_t* n_free_blocks);
void print_heap(FILE * f);

#endif
