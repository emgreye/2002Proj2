#include "trove.h"
#include <sys/stat.h>

void updatetrove(char *trovepath, char *filepath, int minWordLength) {
    printf("updating \"%s\" in trove-file\n", filepath);
    removetrove(trovepath, filepath);
    findfiles(filepath, minWordLength, trovepath);
}
