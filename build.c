#include "trove.h"
#include <sys/stat.h>

void buildtrove(char filename[], char contents[]) {
    FILE *fptr;
    fptr = fopen(filename, "w");
    if (fptr == NULL) {
        printf("Unable to build trove-file.\n");
        exit(EXIT_FAILURE);
    }
    fputs(contents, fptr);
    fclose(fptr);
}
