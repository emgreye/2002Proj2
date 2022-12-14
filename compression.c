#include "trove.h"
#include <unistd.h>
#include <fcntl.h>

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
  int filed[2];
  pid_t pid;
  pipe(filed);

  if ((pid = fork()) == -1){
    perror("fork");
    exit(1);
  }
  // parent loads then reads pipe
  if (pid != 0){
    int comp = open(path, O_RDONLY);
    dup2(comp, STDOUT_FILENO);
    close(filed[1]);
    char buf[BUFSIZ];
    read(filed[0], buf, strlen(buf)+1);
    close(filed[0]);    
    }
  
  // child reads then writes to pipe
  else if (pid == 0){
    dup2(filed[0], STDIN_FILENO);
    close(filed[0]);
    int filed1 = open(path, O_RDONLY);
    dup2(filed1, STDOUT_FILENO);
    close(filed1);

    execl("/usr/bin/zcat","/usr/bin/zcat", (char*)NULL);
    dup2(filed[1], STDOUT_FILENO);
  }
}
