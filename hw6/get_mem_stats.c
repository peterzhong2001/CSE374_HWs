// Peter Zhong and Ariel Luo
// CSE 374 HW6
// 05/21/2021

// get_mem_stats.c implements the get_mem_stats function in the
// memory manager block

#include "mem.h"
#include "mem_impl.h"

// get_mem_stats stores the relevant statistics of the current memory manager
// into the pointers given as parameters.
void get_mem_stats(
  uintptr_t* total_size,
  uintptr_t* total_free,
  uintptr_t* n_free_blocks) {
  *total_size = totalSize;
  *total_free = freeSize;
  *n_free_blocks = freeBlocks;
}
