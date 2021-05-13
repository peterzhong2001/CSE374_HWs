# Peter Zhong and Ariel Luo
# CSE 374 HW5
# 05/14/2021

# Makefile is a makefile that compiles t9.c and trie.c and outputs to
# an executable t9.

CC = gcc

CFLAGS = -Wall -std=c11

TARGET = t9

all: $(TARGET)

# the executable
$(TARGET): t9.o trie.o
	$(CC) $(CFLAGS) -o t9 t9.o trie.o

# individual source files
t9.o: t9.c trie.h
	$(CC) $(CFLAGS) -c t9.c

trie.o: trie.c trie.h
	$(CC) $(CFLAGS) -c trie.c

clean:
	rm -f *.o output *~
