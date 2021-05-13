// Peter Zhong and Ariel Luo
// CSE 374 HW5
// 05/14/2021

// trie.h is the header file for trie.c. It contains the struct named
// TrieNode and all the functions in trie.c.

// nodes for the trie structure
typedef struct TrieNode {
   struct TrieNode* children[10];
   char* word; // word stored at node
} TrieNode;

TrieNode* makeTrieNode(char* word);
void insert(TrieNode* root, char* word);
TrieNode* search(TrieNode* root, char* pattern);
void deleteTrie(TrieNode* root);
int getNumber(char letter);
