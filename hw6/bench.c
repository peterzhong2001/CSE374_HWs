// Peter Zhong and Ariel Luo
// CSE 374 HW6
// 05/21/2021

// bench.c is a testbench program for the memory manager

#include <time.h>

#include "mem_impl.h"
#include "mem.h"

void printMessage(time_t startTime, uintptr_t total_size,
		  uintptr_t total_free, uintptr_t n_free_blocks);

int main(int argc, char **argv) {
  // check number of arguments
  if (argc > 6) {
    fprintf(stderr, "Error: too many arguments");
    return EXIT_FAILURE;
  }
  
  // array of default parameters for running the testbench
  int param[] = {10000, 50, 10, 200, 20000, time(NULL)};
  // replacing default arguments with user inputs
  for (int i = 0; i < argc - 1; i++) {
    param[i] = atoi(argv[i + 1]);
  }

  // defining parameters
  int ntrials = param[0];
  int pctget = param[1];
  int pctlarge = param[2];
  int smallLimit = param[3];
  int largeLimit = param[4];
  int randomSeed = param[5];

  // for tracking the status of the memory manager
  uintptr_t total_size = 0;
  uintptr_t total_free = 0;
  uintptr_t n_free_blocks = 0;
  
  int sel; // randomly generated integer for selection
  int count; // count number of gets vs frees
  uintptr_t size; // size of getmem
  void** mems = (void**) malloc(ntrials * sizeof(void*));

  count = 0;
  srand(randomSeed);
  time_t startTime = clock();
  
  for (int i = 0; i < ntrials; i++) {
    sel = rand() % 100; // generating chance for getmem
    if (sel <= pctget) {
      sel = rand() % 100; // generating chance for large size
      if (sel <= pctlarge) {
	size = rand() % (largeLimit - smallLimit) + smallLimit;
      } else {
	size = rand() % smallLimit;
      }
      mems[count] = getmem(size);
      count++;
    } else {
      if (count > 0) { // only free when there are things to be freed
	int index = rand() % count;
	freemem(mems[index]);
	mems[index] = mems[count - 1]; // fill gap with last pointer
	count--;
      }
    }
    
    // check if at print message points
    if ((i + 1) % (ntrials / 10) == 0) {
      int percent = (i + 1) * 100 / ntrials;
      get_mem_stats(&total_size, &total_free, &n_free_blocks);
      printf("The testbench is %d%% complete \n", percent);
      printMessage(startTime, total_size, total_free, n_free_blocks);
    }
  }
  free(mems);
  return EXIT_SUCCESS;
} 

// takes the start time and additional information from get_mem_stats as
// parameters, and prints out the corresponding information in the terminal.
void printMessage(time_t startTime, uintptr_t total_size,
		  uintptr_t total_free, uintptr_t n_free_blocks) {
  time_t endTime = clock();
  double time = (double) (endTime - startTime) / CLOCKS_PER_SEC;
  printf("Total CPU Time: %f s\n", time);
  printf("Total Amount of Storage Acquired: %lu bytes\n", total_size);
  printf("Total Number of free blocks: %lu \n", n_free_blocks);
  if (n_free_blocks == 0) { // to prevent arithmetic exception
    printf("Average size of the free blocks: 0 bytes\n");
  } else {
    printf("Average size of the free blocks: %lu bytes\n", total_free / n_free_blocks);
  }
  printf("\n");
}
