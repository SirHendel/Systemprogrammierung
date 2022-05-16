#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>

int isdir(char* dateiname){
    struct stat stats;
    if(stat(dateiname, &stats) == 0){
        if(stats.st_mode & S_IFDIR){
            return 1;
        } 
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}