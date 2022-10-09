#include "trove.h"
#include <sys/stat.h>

void buildtrove(char filename[], char contents[]) {
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Could not build file!");
        exit(EXIT_FAILURE);
    }
    fputs(contents, fp);
    fclose(fp);
}
