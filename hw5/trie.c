// Peter Zhong and Ariel Luo
// CSE 374 HW5
// 05/14/2021

// trie.c implements the trie data structure, where a word is stored
// based on its numeric pattern representation. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "trie.h"

// make a new node with the word passed stored in the node
// and all children branches set to null
TrieNode* makeTrieNode(char* word) {
  TrieNode* n = (TrieNode*) malloc(sizeof(TrieNode));
  n->word = word;
  for (int i = 0; i < 10; i++) {
    n->children[i] = NULL;
  }
  return n;
}

// takes the root node and a word as parameters and insert that
// word into the corresponding node in the trie structure
void insert(TrieNode* root, char* word) {
  int num;
  TrieNode* curr = root;
  char* itr = word; // use this variable so that word is not modified
  while (*itr != '\n') {
    num = getNumber(*itr);
    if (num == -1) {
      return;
    } else {
      if (curr->children[num] == NULL) {
	curr->children[num] = makeTrieNode(NULL);
      }
      curr = curr->children[num];
      // check if the insert is at the end of the word
      if (*(itr + 1) == '\n') {
	if (curr->word == NULL) {
	  curr->word = word;
	} else {
	  while (curr->children[0] != NULL) {
	    curr = curr->children[0];
	  }
	  curr->children[0] = makeTrieNode(word);
	}
      }
      itr++;
    }
  }
}

// takes the root node and a numeric pattern as parameters and
// return the pointer to the corresponding node that stores the word
TrieNode* search (TrieNode* root, char* pattern) {
  TrieNode* curr = root;
  while (*pattern != '\0') {
    int num;
    if (isdigit(*pattern) != 0) {
      num = *pattern - '0';
    } else if (*pattern == '#') {
      num = 0;
    } else { // illegal characters
      printf("Not found in current dictionary.\n");
      return NULL;
    }
    if (curr == NULL) { // check if at null node
      if (num == 0) { // check if searching for T9onyms
	printf("There are no more T9onyms\n");
      } else {
	printf("Not found in current dictionary.\n");
      }
      return NULL;
    }
    curr = curr->children[num];
    if (curr == NULL) { // check if at leaf node
      if (num == 0) { // check if searching T9onyms
	printf("There are no more T9onyms\n");
      } else {
	printf("Not found in current dictionary.\n");
      }
      return NULL;
    }
    else if (*(pattern + 1) == '\0') { // check if at end of word
      if (curr->word == NULL) {
	printf("Not found in current dictionary.\n");
	return NULL;
      } else {
	return curr;
      }
    }
    pattern++;
  }
  return NULL;
}

// takes a root node as the parameter and recursively delete
// all the children of that root node
void deleteTrie(TrieNode* root) {
  for (int i = 0; i < 10; i++) {
    if (root->children[i] != NULL) {
      deleteTrie(root->children[i]);
    }
  }
  free(root->word);
  free(root);
}

// takes a letter and returns its corresponding number
// returns -1 for failed operation
int getNumber(char letter) {
  if (letter == 'a' || letter == 'b' || letter == 'c') {
    return 2;
  } else if (letter == 'd' || letter == 'e' || letter == 'f') {
    return 3;
  } else if (letter == 'g' || letter == 'h' || letter == 'i') {
    return 4;
  } else if (letter == 'j' || letter == 'k' || letter == 'l') {
    return 5;
  } else if (letter == 'm' || letter == 'n' || letter == 'o') {
    return 6;
  } else if (letter == 'p' || letter == 'q' || letter == 'r' || letter == 's') {
    return 7;
  } else if (letter == 't' || letter == 'u' || letter == 'v') {
    return 8;
  } else if (letter == 'w' || letter == 'x' || letter == 'y' || letter == 'z') { 
    return 9;
  }
  return -1;
}
