// Peter Zhong and Ariel Luo
// CSE 374 HW6
// 05/21/2021

// print_heap.c implements the print_heap function in the memory manager block

#include "mem.h"
#include "mem_impl.h"

// print_heap prints a formatted listing of blocks on the free list into the
// file f that is passed in as a parameter.
void print_heap(FILE * f) {
  memblock* curr = front;
  while (curr) {
    uintptr_t addr = (uintptr_t) curr;
    uintptr_t size = curr->size;
    fprintf(f, "Address: %lu, Size: %lu \n", addr, size);
    curr = curr->next;
  }
}
