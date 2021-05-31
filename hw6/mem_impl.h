// Peter Zhong and Ariel Luo
// CSE 374 HW6
// 05/21/2021

// mem_impl.h is the header file for the implementation details of the
// memory manager

#ifndef MEM_IMPL_H
#define MEM_IMPL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define MIN_SIZE 48
#define HEADER 16
#define BUFFER 16

// data structure for a single block of memory
typedef struct memblock {
  uintptr_t size;
  struct memblock* next;
} memblock;

// stores the total amount of storage acquired in bytes
extern uintptr_t totalSize;

// stores the amount of storage that is free in bytes
extern uintptr_t freeSize;

// stores the number of blocks that are free
extern uintptr_t freeBlocks;

// stores the pointer to the front of the memory linkedlist
extern memblock* front;

void check_heap();
uintptr_t alignWith16(uintptr_t num);
void removeBlock(memblock* block);
void split(memblock* block, uintptr_t blockSize);
void insert(memblock* block);
void printStat();

#endif
