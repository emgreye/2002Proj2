#include "trove.h"

#define MAX_WORD_SIZE 2000

char *strlwr(char *str) { // Custom strlwr() method to ensure compatibility
  unsigned char *p = (unsigned char *)str;

  while (*p) {
     *p = tolower((unsigned char)*p);
      p++;
  }

  return str;
}

void parsewords(const char *path, int minLength, char *trovepath) {
    FILE *fptr;
    fptr = fopen(path, "r");

    // Exit if file not opened successfully
    if (fptr == NULL) {
        printf("Unable to open file.\n");
        exit(EXIT_FAILURE);
    }

    // Determine file size
    fseek(fptr, 0L, SEEK_END);
    int size = ftell(fptr);
    rewind(fptr);


    int i = 0, index = 0, position = 0;

    char **words; // List of all the words in the file
    words = malloc(size * sizeof(char*));
    for(i = 0; i < size; i++) {
        words[i] = malloc((MAX_WORD_SIZE + 1) * sizeof(char));
    }

    // Parse file char by char.
    // Stop every time a non-alnum char is encountered.
    //    Record all the previous chars as a word and store it.
    char word[MAX_WORD_SIZE];
    char c;
    while (fscanf(fptr, "%c", &c) != EOF) {
        if (isalnum(c)) { // If character is alnum, keep recording the word
          word[position] = c;
          position++;
        } else { // If stumbling upon non-alnum char, stop recording and put the word in words[]
          if (position >= minLength) {
            for (i = 0; i < position; i++) {
              words[index][i] = word[i];
            }
            for (i = 0; i < MAX_WORD_SIZE; i++) word[i] = 0; // Clear word[]
            index++; // Put window on next slot in words[]
          }
          position = 0; // Reset window
        }
    }

    // Close file
    fclose(fptr);

    // Look for duplicates.
    int maxSize = index;
    index = 0;
    char **uniqueWords; // List of all the distinct words in the file
    uniqueWords = malloc(maxSize * sizeof(char*));
    for(i = 0; i < maxSize; i++) {
        uniqueWords[i] = malloc((MAX_WORD_SIZE + 1) * sizeof(char));
    }
    for (i = 0; i < maxSize; i++) {
      int isUnique = 1;
      for (int j = 0; j < maxSize; j++) {
        if (strcmp(words[i], uniqueWords[j]) == 0) isUnique = 0;
      }
      if (isUnique) {
        strcpy(uniqueWords[index], words[i]);
        index++;
      }
    }
    if (index > 0) {
      char completepath[MAX_WORD_SIZE];
      realpath(path, completepath);
      appendtrove(trovepath, "\n#");
      appendtrove(trovepath, completepath);
    }
    
    // Hashes the words and puts them in the trove file
    for (i=0; i<index; i++) {
        char buffer[16];
        sprintf(buffer, "\n%d", hashFunction(uniqueWords[i]));
        appendtrove(trovepath, buffer);
    }    
    printf("found %d unique words.\n", index);
    free(words);
    free(uniqueWords);
    // compresstrove(trovepath);
}
