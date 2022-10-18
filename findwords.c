#include "trove.h"

#define MAX_WORD_SIZE 50

char *strlwr(char *str) { // Custom strlwr() method to ensure compatibility
  unsigned char *p = (unsigned char *)str;

  while (*p) {
     *p = tolower((unsigned char)*p);
      p++;
  }

  return str;
}

void findwords(const char *path, int minLength) {
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

    int i, len, index, isUnique;

    char **words; // List of all the distinct words in the file
    words = malloc(size * size * sizeof(char*));

    for(int i = 0; i < size; i++) {
        words[i] = malloc((size * MAX_WORD_SIZE + 1) * sizeof(char));
    }

    // char words[size][MAX_WORD_SIZE]; // List of all the distinct words in the file
    int  count[size]; // List of occurences of each word in the words[] array
    char word[MAX_WORD_SIZE];

    // Initialize words count to 0
    for (i=0; i<size; i++) count[i] = 0;
    index = 0;
    
    while (fscanf(fptr, "%s", word) != EOF) {
        // Skips the iteration if word is too short
        if (strlen(word) < minLength) continue;

        // Remove special characters
        char cleanWord[MAX_WORD_SIZE];
        int i = 0, c = 0;
        for(; i < strlen(word); i++) {
            if (isalnum(word[i])) {
                cleanWord[c] = word[i];
                c++;
            }
        }
        cleanWord[c] = '\0';
        strcpy(word, cleanWord);

        // Convert word to lowercase
        strlwr(word);
        // Remove last punctuation character
        len = strlen(word);
        if (ispunct(word[len - 1])) word[len - 1] = '\0';

        // Check if word exists in list of all distinct words
        isUnique = 1;
        for (i=0; i<index && isUnique; i++) {
            if (strcmp(words[i], word) == 0)
                isUnique = 0;
        }

        // If word is unique then add it to distinct words list
        // and increment index. Otherwise increment occurrence 
        // count of current word.
        if (isUnique) {
            strcpy(words[index], word);
            count[index]++;

            index++;
        }
        else {
            count[i - 1]++;
        }
    }

    // Close file
    fclose(fptr);


    /*
     * Print occurrences of all words in file. 
     */
    printf("Occurrences of all distinct words in file %s\n", path);
    for (i=0; i<index; i++) {
        /*
         * %-15s prints string in 15 character width.
         * - is used to print string left align inside
         * 15 character width space.
         */
        printf("%-15s => %d\n", words[i], count[i]);
    }    
    free(words);
}
