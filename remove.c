#include "trove.h"

void removetrove(char *trovepath, char *filepath) {
    char replicapath[1024];
    strcpy(replicapath, trovepath);
    strcat(replicapath, "replica");
    FILE *fptr = fopen(trovepath, "r");
    FILE *fptrReplica = fopen(replicapath, "w");
    if(fptr == NULL) {
        printf("Unable to build trove-file.\n");
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t len = 0;
    char path[1024];
    realpath(filepath, path);
    // char currentPath[1024];
    
    printf("deleting data of \"%s\"\n", filepath);

    int isToDelete = 0;
    while(getline(&line, &len, fptr) != -1) {
        // IF LINE SPECIFIES THE START OF A PATH
        if (line[0] == '#') {
            // IF WE WERE DELETING A PATH BEFORE, RESET
            if (isToDelete == 1) isToDelete = 0;
            // CHECK IF THIS PATH IS TO DELETE
            // Ensures proper comparison without # or \n
            size_t length = strlen(line);
            if (line[length-1] == '\n') line[length-1] = '\0';
            memmove(line, line+1, strlen(line));
            // Ensures data is deleted regardless of folder or file specification
            if (strncmp(line, path, strlen(path)) == 0) {
                isToDelete = 1;
            }
        }
        if (!isToDelete) {
            // ACTIONS FOR COPYING THE LINE
            fputs(line, fptrReplica);
            printf("%s", line);
        }
    }

    fclose(fptr);
    fclose(fptrReplica);
    remove(trovepath);
    rename(replicapath ,trovepath);
    free(line);
}


void removetrove(char *trovepath, char *filepath) {
    char replicapath[1024];
    strcpy(replicapath, trovepath);
    strcat(replicapath, "replica");
    FILE *fptr = fopen(trovepath, "r");
    FILE *fptrReplica = fopen(replicapath, "w");
    if(fptr == NULL) {
        printf("Unable to build trove-file.\n");
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t len = 0;
    char path[1024];
    realpath(filepath, path);
    // char currentPath[1024];
    
    printf("deleting data of \"%s\"\n", filepath);

    int isToDelete = 0;
    while(getline(&line, &len, fptr) != -1) {
        // IF LINE SPECIFIES THE START OF A PATH
        if (line[0] == '#') {
            // IF WE WERE DELETING A PATH BEFORE, RESET
            if (isToDelete == 1) isToDelete = 0;
            // CHECK IF THIS PATH IS TO DELETE
            // Ensures proper comparison without # or \n
            size_t length = strlen(line);
            if (line[length-1] == '\n') line[length-1] = '\0';
            memmove(line, line+1, strlen(line));
            // Ensures data is deleted regardless of folder or file specification
            if (strncmp(line, path, strlen(path)) == 0) {
                isToDelete = 1;
            }
        }
        if (!isToDelete) {
            // ACTIONS FOR COPYING THE LINE
            fputs(line, fptrReplica);
            printf("%s", line);
        }
    }

    fclose(fptr);
    fclose(fptrReplica);
    remove(trovepath);
    rename(replicapath ,trovepath);
    free(line);
}

