//  CITS2002 Project 2 2022
//  Student1:   23136241   MCAULIFFE   JAKE   CONTRIBUTION
//  Student2:   22884473   GAUDIN   LÉO   CONTRIBUTION

#include "trove.h"
#include <getopt.h>

#define	OPTLIST		"bruf:l:"
#define DEFAULT_LENGTH 4
#define DEFAULT_FILE "/tmp/trove"

int main(int argc, char *argv[]) {
    
    int  opt;
    bool build   = false;
    bool remove = false;
    bool update = false;
    char *filenm = DEFAULT_FILE;
    int  length   = DEFAULT_LENGTH;
    char wrongarg;

    opterr	= 0;
    while((opt = getopt(argc, argv, OPTLIST)) != -1)   {  
//  IF b IS SPECIFIED, PROGRAM SHOULD BUILD NEW FILE
	if(opt == 'b') {
            build  =  true;
        }
//  IF r IS SPECIFIED, PROGRAM SHOULD REMOVE CONTENTS OF FILE
    else if(opt == 'r') {
            remove  =  true;
        }
//  IF u IS SPECIFIED, PROGRAM SHOULD UPDATE FILE
    else if(opt == 'u') {
            update  =  true;
        }
//  TAKES THE NAME OF THE FILE
	else if(opt == 'f') {
            strcpy(filenm, optarg);
        }
//  TAKES LENGTH OF 
	else if(opt == 'l') {
            length  =  atoi(optarg);
        }
//  AN UNKNOWN ARGUMENT
        else {
            argc = -1;
            wrongarg = opt;
        }
    }

    if(argc <= 0) {    //  error if unknown argument 
         fprintf(stderr, "%c: Invalid argument\n", wrongarg);
    }
    argc  -= optind;
    argv  += optind;

    // HERE FOR TESTING PURPOSES ONLY FOR THE MOMENT
    if (build) {
        int i = 0;
        while (argv[i] != NULL) {
            listFiles(argv[i]);
            // printf("%s\n", argv[i]);
            i++;
        }
    }
    
    //dummy code so that it compiles
    printf("Length? %i.\nFile name? %s.\nBuild? %i.\nRemove? %i.\nUpdate? %i.\n", length, filenm, build, remove, update);
    
    exit(EXIT_SUCCESS);
}
