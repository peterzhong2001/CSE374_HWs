# Peter Zhong and Ariel Luo
# CSE 374 HW5
# 05/14/2021

# Makefile is a makefile that compiles all programs in the memory manager block.
# It outputs the executable "bench" that can be used to test the functionality
# of the programs.

CC = gcc

CFLAGS = -Wall -std=c11

TARGET = bench

all: $(TARGET)

# the executable
$(TARGET): bench.o freemem.o get_mem_stats.o getmem.o print_heap.o mem_utils.o
	$(CC) $(CFLAGS) -o bench bench.o freemem.o get_mem_stats.o getmem.o print_heap.o mem_utils.o

# recompiling the program and running the executable 
test: bench
	./bench

# making individual source files for all c files written
bench.o: bench.c mem.h mem_impl.h
	$(CC) $(CFLAGS) -c bench.c

freemem.o: freemem.c mem.h
	$(CC) $(CFLAGS) -c freemem.c

get_mem_stats.o: get_mem_stats.c mem.h
	$(CC) $(CFLAGS) -c get_mem_stats.c

getmem.o: getmem.c mem.h
	$(CC) $(CFLAGS) -c getmem.c

print_heap.o: print_heap.c mem.h
	$(CC) $(CFLAGS) -c print_heap.c

mem_utils.o: mem_utils.c mem.h
	$(CC) $(CFLAGS) -c mem_utils.c

# cleaning up the directory to remove everything except for source code
clean:
	rm -f *.o bench *~

