#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <string.h> 
#include <fcntl.h>
 
int main(int argc,char* argv[]) 
{ 
    int fd = 0,fz = 0; 
    struct stat st; 
    char* copyfile = argv[1];
    char* zielfile = argv[2];

    fd = open(copyfile,O_RDONLY); 
    fz = open(zielfile,O_WRONLY);
    if(-1 == fd || fstat(fd, &st)) 
    { 
        printf("\n NULL File descriptor\n"); 
        return EXIT_FAILURE; 
         
    }
    char* buffer = malloc(512);
    if(S_ISREG(st.st_mode)) 
    {
        fread(buffer,512,3,copyfile);
        printf("\n File is a regular file\n"); 

    } 
    
    // Close the file 
    close(fd); 
 
    return 0; 
}