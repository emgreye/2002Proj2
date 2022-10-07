#include "trove.h"

void buildtrove(char filename[], char contents[]) {
    FILE *fp;
    fp = fopen(filename, "rw");
    fclose(fp);
}