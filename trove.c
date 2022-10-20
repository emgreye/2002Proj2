//  CITS2002 Project 2 2022
//  Student1:   23136241   MCAULIFFE   JAKE   20
//  Student2:   22884473   GAUDIN   LÉO   80
//
//  Calculation detail:
//      Léo contributed 66 commits with 2,785 additions and 1,370 deletions
//          Net contribution of 1,415 → 84.78%
//      Jake contributed 23 commits with 307 additions and 53 deletions:
//          Net contribution of 254 →   15.22%

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
    char filenm[1024];
    strcpy(filenm, DEFAULT_FILE);
    int  length   = DEFAULT_LENGTH;
    char wrongarg;

    opterr	= 0;
    while((opt = getopt(argc, argv, OPTLIST)) != -1)   {  
        //  IF b IS SPECIFIED, PROGRAM SHOULD BUILD NEW FILE
		if(opt == 'b') {
        	build = true;
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
        //  TAKES MINIMUM LENGTH OF WORD
		else if(opt == 'l') {
            length  =  atoi(optarg);
    }
        //  AN UNKNOWN ARGUMENT
        else {
            argc = -1;
            wrongarg = opt;
        }
    }
	
	if (build+remove+update > 1){
		fprintf(stderr, "Only one action can be performed to trovefile\n");
	}

    if(argc <= 0) {    //  error if unknown argument 
    	fprintf(stderr, "%c: Invalid argument\n", wrongarg);
    }
    argc  -= optind;
    argv  += optind;

    if (build) {
        buildtrove(filenm);
        int i = 0;
        while (argv[i] != NULL) {
            findfiles(argv[i], length, filenm);
            i++;
        }
    }
	else if (remove) {
        int i = 0;
        while (argv[i] != NULL) {
            removetrove(filenm, argv[i]);
            i++;
        }
    }
	else if (update) {
        int i = 0;
        while (argv[i] != NULL) {
            updatetrove(filenm, argv[i], length);
            i++;
        }
    }

    if (!(build || update || remove)) {
        int i = 0;
        while (argv[i] != NULL) {
            findwords(filenm, argv[i]);
            i++;
        }
    }
    
    exit(EXIT_SUCCESS);
}
