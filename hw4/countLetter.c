// Peter Zhong
// CSE 374 HW4
// 05/04/2021

// This is a C program that counts the number of a certain letter in
// multiple text files.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100 // maximum length of a line that can be read
#define TEMP_FILENAME "temp" // name of the temporary file

void readFile(char *filename);
int countLetters(char letter);

// Process an input file by appending its content to a temporary file
void readFile(char *filename) {
  FILE *file; // pointer to the file being read
  FILE *temp; // pointer to the temporary file
  char line[MAX_LENGTH]; // maximum length of a line
  
  file = fopen(filename, "r");
  if (!file) { // if the file cannot be opened
    fprintf(stderr, "Cannot open file: %s\n", filename);
  } else { // append the current file to the temporary file
    temp = fopen(TEMP_FILENAME, "a");
    while (!feof(file)) {
      if (fgets(line, MAX_LENGTH, file) != NULL) {
	fprintf(temp, "%s", line);
      }
    }
    fclose(file);
    fclose(temp);
  }
}

// takes a letter as argument and returns the count of the number of
// that letter in the temporary file
int countLetters(char letter) {
  FILE *file; // pointer to the the temporary file
  int count = 0;
  char line[MAX_LENGTH]; // current line being read
  
  file = fopen(TEMP_FILENAME, "r");
  // read the temporary file line by line
  while (!feof(file)) {
    if (fgets(line, MAX_LENGTH, file) != NULL) {
      for (int i = 0; i < strlen(line); i++) {
	if (line[i] == letter) {
	  count++;
	}
      }
    }
  }
  fclose(file);
  return count;
}

int main(int argc, char **argv) {
  if (argc < 3) { // check number of arguments
    fprintf(stderr, "Error: not enough arguments passed\n");
    exit(EXIT_FAILURE);
  }
  if (strlen(argv[1]) > 1) { // check if first argument is a single character
    fprintf(stderr, "Error: needs a single letter as first argument\n");
    exit(EXIT_FAILURE);
  }
  if (!isalpha(argv[1][0])) { // check if first argument is a letter
    fprintf(stderr, "Error: first argument is not a letter\n");
    exit(EXIT_FAILURE);
  }
  FILE *temp; // pointer to the temporary file
  char letter; // a single letter to be identified
  int *count = (int*)malloc(sizeof(int));

  temp = fopen(TEMP_FILENAME, "w");
  letter = argv[1][0];
  *count = 0;
  
  // process every file into a single temporary text file
  for (int i = 2; i < argc; i++) {
    readFile(argv[i]);
  }
  *count = countLetters(letter);
  fclose(temp);
  // print out the message based on the number of letters found
  if (*count > 1) {
    printf("There are %d \"%c\"s in the textfiles\n", *count, letter);
  } else if (*count == 1){
    printf("There is %d \"%c\" in the textfiles\n", *count, letter);
  } else {
    printf("There is no \"%c\" in the textfiles\n", letter);
  }
  remove(TEMP_FILENAME);
  free(count);
  return EXIT_SUCCESS;
}
