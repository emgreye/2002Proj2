#include "trove.h"
#include <sys/stat.h>

void updatetrove(char filelist[]) {
    FILE *fptr;
    fptr = fopen(filename, "w");
    if (fptr == NULL) {
        printf("Unable to update trove-file.\n");
        exit(EXIT_FAILURE);
    }
  
  
    fclose(fptr);
}
