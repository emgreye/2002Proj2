#include "trove.h"
#include <sys/stat.h>

void updatetrove(char *trovepath, char *filepath, int minWordLength) {
    removetrove(trovepath, filepath);
    findfiles(filepath, minWordLength, trovepath);
}
