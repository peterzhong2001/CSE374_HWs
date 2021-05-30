// Peter Zhong and Ariel Luo
// CSE 374 HW6
// 05/21/2021

//freemem.c implements the freemem function in the memory manager block

#include "mem.h"
#include "mem_impl.h"

// freemem takes a pointer to a memory block, and return that memory block
// to the available free storage.
void freemem(void* p) {
  if (p == NULL) {
    return;
  }
  check_heap();
  memblock* curr = front;
  memblock* block = p - HEADER;
  if (!block) { // inserting null
    return;
  } else if (!front) { // no front block
    front = block;
  } else if ((uintptr_t)front >= (uintptr_t)block) { //inserting to front
      block->next = front;
      front = block;
  } else { // iterate and insert
    while (curr->next != NULL && ((uintptr_t)curr->next < (uintptr_t)block)) {
      curr = curr->next;
    }
    block->next = curr->next;
    curr->next = block;
  }
  freeBlocks++;
  freeSize += block->size;
  // check front merge
  if (block != front) {
    if ((uintptr_t)curr + curr->size + BUFFER == (uintptr_t)block - HEADER) {
      curr->size += block->size + HEADER+ BUFFER;
      curr->next = block->next;
      freeBlocks--;
      freeSize += HEADER + BUFFER;
    }
    block = block->next;
  }
  // merge with blocks after
  while ((uintptr_t)block + block->size + BUFFER == (uintptr_t)block->next - HEADER) {
    block->size += block->next->size + HEADER + BUFFER;
    block->next = block->next->next;
    freeBlocks--;
    freeSize += HEADER + BUFFER;
  }
  check_heap();
}
