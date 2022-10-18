#include "trove.h"

#define MAX_WORD_SIZE 50

void findwords(const char *path) {
    FILE *fptr;
    fptr = fopen(path, "r");

    /* Exit if file not opened successfully */
    if (fptr == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check you have read previleges.\n");

        exit(EXIT_FAILURE);
    }

    fseek(fptr, 0L, SEEK_END);    // seek to the EOF
    int size = ftell(fptr);       // get the current position
    rewind(fptr);                // rewind to the beginning of file

    int i, len, index, isUnique;

    // List of distinct words
    char words[size][MAX_WORD_SIZE];
    char word[MAX_WORD_SIZE];

    // Count of distinct words
    int  count[size];

    // Initialize words count to 0
    for (i=0; i<size; i++) count[i] = 0;

    index = 0;
    
    while (fscanf(fptr, "%s", word) != EOF)
    {
        // Convert word to lowercase
        // strlwr(word);

        // Remove last punctuation character
        len = strlen(word);
        if (ispunct(word[len - 1]))
            word[len - 1] = '\0';


        // Check if word exits in list of all distinct words
        isUnique = 1;
        for (i=0; i<index && isUnique; i++)
        {
            if (strcmp(words[i], word) == 0)
                isUnique = 0;
        }

        // If word is unique then add it to distinct words list
        // and increment index. Otherwise increment occurrence 
        // count of current word.
        if (isUnique) 
        {
            strcpy(words[index], word);
            count[index]++;

            index++;
        }
        else
        {
            count[i - 1]++;
        }
    }

    // Close file
    fclose(fptr);


    /*
     * Print occurrences of all words in file. 
     */
    printf("\nOccurrences of all distinct words in file: \n");
    for (i=0; i<index; i++)
    {
        /*
         * %-15s prints string in 15 character width.
         * - is used to print string left align inside
         * 15 character width space.
         */
        printf("%-15s => %d\n", words[i], count[i]);
    }    
}
