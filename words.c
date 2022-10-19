#include "trove.h"

#define MAX_WORD_SIZE 2000
#define MAX_LINE_SIZE 4000

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

    printf("File is %d bytes.\n", size);

    int i, index, isUnique;

    char **words; // List of all the distinct words in the file
    words = malloc(size * sizeof(char*));

    for(int i = 0; i < size; i++) {
        words[i] = malloc((MAX_WORD_SIZE + 1) * sizeof(char));
    }

    // char words[size][MAX_WORD_SIZE]; // List of all the distinct words in the file
    int  count[size]; // List of occurences of each word in the words[] array
    char word[MAX_WORD_SIZE];

    // Initialize words count to 0
    for (i=0; i<size; i++) count[i] = 0;
    index = 0;
    
	char line[MAX_LINE_SIZE];
	int lineno = 0;
	
    while (fgets(line ,MAX_LINE_SIZE, fptr) != NULL) {
        int start = 0;
        int end = 0;

		const char alphanum[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
        while (end<MAX_LINE_SIZE && line[end]!='\n') {
			//sets the initial character to be the first alphanumeric char
            start = start + end + strcspn(line+start+end, alphanum);
			//end is no of letters before you find a non-alphanumeric char
            end = strspn(line+start, alphanum);
			// If word is unique then add it to distinct words list
			// and increment index. Otherwise increment occurrence 
			// count of current word.
            // Check if word exists in list of all distinct words
            isUnique = 1;
            for (i=0; i<index && isUnique; i++) {
                if (strcmp(words[i], word) == 0)
                    isUnique = 0;
            }

			if (isUnique) {
				//copy chars from start to end into the words array
				memcpy(&words[lineno][index], &line[start], end);
				//terminates string with a null byte.
				words[lineno][end] = '\0';
				count[index]++;

				index++;
				} else {
					count[i - 1]++;
				}
			}
            ++lineno; 			
	}

    // Close file
    fclose(fptr);


    /*
     * Print occurrences of all words in file. 
     */
    for (i=0; i<index; i++) {
        /*
         * %-15s prints string in 15 character width.
         * - is used to print string left align inside
         * 15 character width space.
         */
        printf("%-15s => %d\n", words[i], count[i]);
    }    
    printf("found %d words.\n", index);
    free(words);
}
