// Peter Zhong and Ariel Luo
// CSE 374 HW6
// 05/21/2021

// getmem.c implements the function "getmem" in the memory manager block

#include "mem.h"
#include "mem_impl.h"

#define FIRST_BLOCK 72000

// getmem takes unsigned integer pointer size as parameter and return a
// pointer to a new block of storage with at least size bytes of memory.
void* getmem(uintptr_t size) {
  check_heap();

  // check if parameter is valid
  if (size <= 0) {
    return NULL;
  }
  
  uintptr_t blockSize = alignWith16(size);
  
  memblock* curr = front;
  // adjusting the size
 if (blockSize < MIN_SIZE) {
    blockSize = MIN_SIZE;
  }

  // search for a suitable block
  while (curr && curr->size < blockSize) {
    curr = curr->next;
  }
  
  // when no proper block is found, create a properly sized block
  // with substantial extra space
  if (!curr) {
    curr = (memblock*) malloc(blockSize + HEADER + FIRST_BLOCK + BUFFER);
    curr->size = blockSize + FIRST_BLOCK;
    curr->next = NULL;
    totalSize += blockSize + FIRST_BLOCK + HEADER + BUFFER;
    insert(curr);
  }
  
  // proper block is found but with inappropriate size
  if (curr->size > (blockSize + MIN_SIZE + HEADER)) {
    split(curr, blockSize);
  }
  removeBlock(curr);

  void* requestedBlock = (void*) ((uintptr_t)curr) + HEADER;
  check_heap();
  return requestedBlock;
}
