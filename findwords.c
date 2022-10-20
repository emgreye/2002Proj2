#include "trove.h"

void findwords(char *trovefile, char *word) {
    FILE *fptr = fopen(trovefile, "r");
    if(fptr == NULL) {
        printf("Unable to build trove-file.\n");
        exit(EXIT_FAILURE);
    }
 
    char *line = NULL;
    size_t len = 0;
    char currentPath[1024];
 
    printf("looking for word \"%s\"\n", word);

    // TODO: Handle duplicates (when a word is found multiple times in a file)
    while(getline(&line, &len, fptr) != -1) {
        if (line[0] == '#') {
            memmove(line, line+1, strlen(line));
            strcpy(currentPath, line);
        }
        if (hashFunction(word) == atoi(line)) {
            printf("%s\n", currentPath);
        }
    }
  
    fclose(fptr);
    free(line);  
}
