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
    
    printf("removing potentially already existing data of \"%s\" in trove-file\n", filepath);

    int isToDelete = 0;
    char reformattedLine[1024];

    // Checks every line.
    // For each one of them, check if it is a word hash or a path.
    // If it is a path, check if it is the one we want to delete.
    // If it is a hash, check if it belongs to the path we want to delete.
    //      If yes, set isToDelete to true.
    // Check if isToDelete is true, and if not, put the line in the new updated file.
    while(getline(&line, &len, fptr) != -1) {
        // IF LINE SPECIFIES THE START OF A PATH
        if (line[0] == '#') {
            // IF WE WERE DELETING A PATH BEFORE, RESET
            if (isToDelete == 1) isToDelete = 0;
            // CHECK IF THIS PATH IS TO DELETE
            // Ensure proper comparison without # or \n
            size_t length = strlen(line);
            if (line[length-1] == '\n') line[length-1] = '\0';
            memmove(line, line+1, strlen(line));
            // Use of strncmp so that user can choose to delete a file or directly a whole folder
            if (strncmp(line, path, strlen(path)) == 0) {
                isToDelete = 1;
            }
            sprintf(reformattedLine, "#%s\n", line); // Recreates the path as it was found
        } else {
            strcpy(reformattedLine, line);
        }
        if (!isToDelete) {
            fputs(reformattedLine, fptrReplica);
        }
    }

    fclose(fptr);
    fclose(fptrReplica);
    remove(trovepath);
    rename(replicapath, trovepath);
    free(line);
}
