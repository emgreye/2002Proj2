#include "trove.h"
#include <dirent.h>

void findfiles(const char* dirname, int minWordLength) {
    DIR* dir = opendir(dirname);
    if (dir == NULL) {
        return;
    }

    printf("\nReading files in: %s\n", dirname);

    struct dirent* entity;
    entity = readdir(dir);
    // GOES THROUGH EVERY ENTITY IN THE DIRECTORY
    while (entity != NULL) {
        // ACTION TO BE PERFORMED REGARDLESS OF THE ENTITY

        char path[100] = { 0 };
        strcat(path, dirname);
        strcat(path, "/");
        strcat(path, entity->d_name);

        // printf("%hhd %s\n", entity->d_type, path); // Prints the type and the path to the entity

        // RECURSIVELY GOES THROUGH THE SUBDIRECTORIES
        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            // UPDATES PATH AND RUNS FUNCTION AGAIN RECURSIVELY
            findfiles(path, minWordLength);
        }

        else if (entity->d_type == DT_REG) {
            // ACTION TO BE PERFORMED IF THE ENTITY IS A FILE
            // (i.e. going through the words, etc)
            printf("Reading the words in %s\n", path);
            findwords(path, minWordLength);
        }

        // GOES TO NEXT ENTITY IN FOLDER
        entity = readdir(dir);
    }

    closedir(dir);
}
