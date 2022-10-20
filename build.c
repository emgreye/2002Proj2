#include "trove.h"
#include <sys/stat.h>

void buildtrove(char filename[]) {
    FILE *fptr;
    fptr = fopen(filename, "w");
    if (fptr == NULL) {
        printf("Unable to build trove-file.\n");
        exit(EXIT_FAILURE);
    }
    fclose(fptr);
    printf("building trove-file\n");
}

void appendtrove(char filename[], char contents[]) {
    FILE *fptr;
    fptr = fopen(filename, "a");
    if (fptr == NULL) {
        printf("Unable to build trove-file.\n");
        exit(EXIT_FAILURE);
    }
    fputs(contents, fptr);
    fclose(fptr);
}
