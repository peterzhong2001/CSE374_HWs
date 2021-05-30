// Peter Zhong and Ariel Luo
// CSE 374 HW6
// 05/21/2021

// mem_utils.c implements the implementation functions of the memory manager

#include <assert.h>

#include "mem.h"
#include "mem_impl.h"

// defining the initial values for the stats variables
memblock* front = NULL;
uintptr_t totalSize = 0;
uintptr_t freeSize = 0;
uintptr_t freeBlocks = 0;

memblock* curr; // used to iterate the linkedlist


// check_heap checks for possible problems with the current data structure.
void check_heap() {
  curr = front;
  while (curr && curr->next) {
    // check increasing order memory address
    assert(curr < curr->next);

    // check positive size number and greater than min size
    assert(curr->size >= MIN_SIZE);

    // check overlapping
    assert((uintptr_t) curr + curr->size + HEADER < (uintptr_t) curr->next);
    
    // check touching
    assert((uintptr_t) curr + curr->size + HEADER != (uintptr_t) curr->next);
    
    //iterate
    curr = curr->next;
  }
}

// takes a uintptr_t as parameter and align it to the closest number
// that is both larger than the parameter and divisible by 16
uintptr_t alignWith16(uintptr_t num) {
  if (num % 16 == 0) {
    return num;
  }
  return (num / 16) * 16 + 16;
}

// takes a memory block pointer as parameter, remove that block
// from the free list, and update statistics accordingly
void removeBlock(memblock* block) {
  if (block == front) {
    front = front->next;
  } else {
    memblock* curr = front;
    while (curr->next != block) {
      curr = curr->next;
    }
    curr->next = block->next;
  }
  block->next = NULL;
  freeSize -= block->size;
  freeBlocks--;
}

// takes a memory block pointer as parameter and split that block
// into two appropriately sized block
void split(memblock* block, uintptr_t blockSize) {
  uintptr_t remainSize = block->size - blockSize - HEADER - BUFFER;
  uintptr_t addr = ((uintptr_t)block) + blockSize + HEADER + BUFFER;
  memblock* new = (memblock*) addr;
  new->size = remainSize;
  new->next = block->next;
  block->next = new;
  block->size = blockSize;
  freeSize -= (HEADER + BUFFER); // extra size used to make a new block
  freeBlocks++; // turned 1 free blocks into 2
}

// takes a memory block pointer as parameter, and insert that block
// into the free list
void insert(memblock* block) {
  if (!block) { // inserting null
    return;
  } else if (!front) { // no front block
    front = block;
  } else if ((uintptr_t)front >= (uintptr_t)block) { //inserting to front
      block->next = front;
      front = block;
  } else { // iterate and insert
    memblock* curr = front;
    while (curr->next != NULL && ((uintptr_t)curr < (uintptr_t)block)) {
      curr = curr->next;
    }
    block->next = curr->next;
    curr->next = block;
  }
  freeSize += block->size;
  freeBlocks++;
}

// debug method
void printStat() {
  uintptr_t total_size;
  uintptr_t total_free;
  uintptr_t n_free_blocks;
  get_mem_stats(&total_size, &total_free, &n_free_blocks);
  printf("Total Amount of Storage Acquired: %lu bytes\n", total_size);
  printf("Total Number of free blocks: %lu \n", n_free_blocks);
  if (n_free_blocks == 0) { // to prevent arithmetic exception
    printf("Average size of the free blocks: 0 bytes\n");
  } else {
    printf("Average size of the free blocks: %lu bytes\n", total_free / n_free_blocks);
  }
}
