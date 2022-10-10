#include "trove.h"
#include <dirent.h>

void listFiles(const char* dirname) {
    DIR* dir = opendir(dirname);
    if (dir == NULL) {
        return;
    }

    printf("Reading files in: %s\n", dirname);

    struct dirent* entity;
    entity = readdir(dir);
    // GOES THROUGH EVERY ENTITY IN THE DIRECTORY
    while (entity != NULL) {
        // ACTION TO BE PERFORMED REGARDLESS OF THE ENTITY
        printf("%hhd %s/%s\n", entity->d_type, dirname, entity->d_name);

        // RECURSIVELY GOES THROUGH THE SUBDIRECTORIES
        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            // UPDATES PATH AND RUNS FUNCTION AGAIN RECURSIVELY
            char path[100] = { 0 };
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entity->d_name);
            listFiles(path);
        }

        else if (entity->d_type == DT_REG) {
            // ACTION TO BE PERFORMED IF THE ENTITY IS A FILE
            // (i.e. going through the words, etc)
        }

        // GOES TO NEXT ENTITY IN FOLDER
        entity = readdir(dir);
    }

    closedir(dir);
}
