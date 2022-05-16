#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include "function.h"

int main(int argc,char* argv[]){
    struct stat stats;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    assert(argv[1] != NULL);
    if(stat(argv[1], &stats) == 0){
        printf("Dateiname: '%s' \n",argv[1]);
        if(isdir(argv[1]))
            printf("Ist ein ordner \n");
        else
            printf("Ist kein ordner \n");
    }
    else{
        printf("Kann die Datei nicht finden.\n");
        printf("Bitte überprüfe ob die Datei: '%s' vorhanden ist. \n",argv[1]);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}