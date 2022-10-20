#include "trove.h"
#include <unistd.h>

void compresstrove(const char *path) {
  // char command[1024];
  // sprintf(command, "gzip -9c %s > %s", path, path);
  // execl("/bin/sh", "/bin/sh", "-c", command, NULL);
  char command[6 + strlen(path)];
  strcpy(command, "gzip -f ");
  strcat(command, path);
  system(command);
}

void readcompressed(const char *path){
  char command[9 + strlen(path)];
  strcpy(command, "zcat -f ");
  strcat(command, path);
  system(command);
}
