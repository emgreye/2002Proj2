#include "trove.h"

void findwords(char *trovefile, char *word) {
    FILE *fptr = fopen(trovefile, "r");
    if(fptr == NULL) {
        printf("Unable to build trove-file.\n");
        exit(EXIT_FAILURE);
    }
    printf("reading trove-file\n");
 
    char *line = NULL;
    size_t len = 0;
    char currentPath[1024];
 
    printf("searching for \"%s\"\n", word);

    // Checks every line.
    // For each one of them, check if it is a word hash or a path.
    // If it is a path, tell the program every next hash belongs to this path's file.
    // If it is a hash, check if it is the one we are looking for.
    //      If yes, printf() the path it is in.
    while(getline(&line, &len, fptr) != -1) {
        if (line[0] == '#') {
            memmove(line, line+1, strlen(line)); // Gets rid of the # identifier
            strcpy(currentPath, line);
        }
        if (hashFunction(word) == atoi(line)) {
            printf("%s", currentPath);
        }
    }
  
    fclose(fptr);
    free(line);  
}
