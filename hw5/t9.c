// Peter Zhong and Ariel Luo
// CSE 374 HW5
// 05/14/2021

// t9.c creates a trie based on the input text file, and starts
// an interactive session with the user in the terminal. The user
// can either enter numeric sequences to find words or enter "exit"
// to terminate the interactive session.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "trie.h"

#define MAX_LENGTH 100 // maximum length of a line

TrieNode* createTrie (char* filename);
void startIOSession(TrieNode* root);

// takes a filename as parameter and creates a trie based on the words
// included in the input file. Returns NULL if the file is not found
TrieNode* createTrie (char* filename) {
  FILE *file;
  char line[MAX_LENGTH];
  TrieNode* root;
  char* store;
  
  file = fopen(filename, "r");
  if (!file) { // if the file is not found
    fprintf(stderr, "Cannot open file: %s\n", filename);
    return NULL;
  } else {
    root = makeTrieNode(NULL);
    while (!feof(file)) { // read the file line by line
      if (fgets(line, MAX_LENGTH, file) != NULL) {
	store = malloc(sizeof * store *(strlen(line)+1));
	strcpy(store,line);
	insert(root, store); // insert into the trie
      }
    }
  }
  return root;
}

// takes the root node of the trie and starts a terminal user
// interactive session with the trie
void startIOSession(TrieNode* root) {
  char input[MAX_LENGTH];
  TrieNode* curr;
  char* word;
  printf("Enter \"exit\" to quit.\n");
  printf("Enter Key Sequence (or \"#\" for next word):\n");
  scanf("%s", input);
  while (strcmp(input, "exit") != 0) {
    char* inputPtr = input;
    if (*inputPtr != '#') { // check if searching for T9onyms
      curr = search(root, inputPtr);
    } else {
      curr = search(curr, inputPtr);
    }
    if (curr != NULL) {
      // print out the entire word based on the pointer
      word = curr->word;
      while (*word != '\0') {
	printf("%c", *word);
	word++;
      }
    }
    printf("Enter Key Sequence (or \"#\" for next word):\n");
    scanf("%s", input);
  }
}

int main(int argc, char **argv) {
  // check if there's only one argument
  if (argc != 2) {
    fprintf(stderr, "Error: only one argument can be accepted\n");
    exit(EXIT_FAILURE);
  }
  char* filename = argv[1];
  TrieNode* root;
  root = createTrie(filename);
  if (root != NULL) {
    startIOSession(root);
    deleteTrie(root);
  }
  return EXIT_SUCCESS;
}
