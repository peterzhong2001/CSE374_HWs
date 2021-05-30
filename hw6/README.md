# Ariel Luo and Peter Zhong (AP) - CSE 374 HW6, Memory Manager
## Dividing the Workload
**Ariel Luo:** freemem, Makefile, get_mem_stats, print_heap, both header files\
**Peter Zhong:** getmem, mem_utils, bench, both header files

## Brief Overview of the Algorithm
This program is a linked-list-based memory manager. It keeps a list of blocks of free memories. When getmem is called, the memory manager traverses through the list of free memory to allocate a block of memory for the user based on the size specified. When freemem is called, the memory manager returns the block of previously requested memory into the free list, and combine adjacent blocks of memory into a bigger free block of memory

**getmem:** When the function is first called, the program will first traverse through the free list to look for a free block that has a larger size than the size requested. If no such block is found, the program will use malloc to request a substantially large block of memory from the underlying system and insert that newly allocated block of memory into the free list. If a block is found, but the size of that block is substantially larger than the request size, the program will split the free block, add the remainder to the free list, and return the allocated block to the user.

**freemem:** When freemem is called, the program will first traverse through the free list and find the location to insert the block using its address. The free list will always have the addresses in ascending order. The block will be merged with the adjacent free blocks after being inserted if there are any. The program will check the block before the inserted block first, then it will check the blocks after for any possible merges. The program will eventually insert the block with all adjacent blocks combined to one. 


## Additional Features
Other than what is requested by the assignment spec, we did not implement any additional features to our memory manager.

## Summary of "Bench" Test Results
**getmem:** We experimented with how substantially large a block should be when malloc is called to best optimize the runtime. To test the most optimal malloc operation size, we tweaked our "FIRST_BLOCK" parameter and ran 100 getmem operations with 50% chance of getting a large request. We discovered that the run time stays at around 0.074s for the values between 48k - 96k. The time starts increasing after the parameter goes below 48k or above 96k. Therefore, we eventually chose 72k as our malloc parameter.


**Overall:** The average total CPU run time is around 0.005s. With the default parameters of 10000 trials, it ended up creating around 45 free memory blocks at the completion of the bench program. 

## Acknowledgements
You might notice that the commits are very imbalanced - Peter Zhong have a lot more commits than Ariel Luo. This is because we are working with each other in person through pair programming on Peter Zhong's PC.

Other than helping each other out and referring to the resources provided by the CSE374 course, we did not use any additional resource to program and debug HW6.
