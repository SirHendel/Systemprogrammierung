#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

void printFileProperties(struct stat stats);

int main(int argc,char* argv[]){
    struct stat stats;
    if (argc != 2) {
        printf("To many variables || zu viele variablen  \n");
        exit(EXIT_FAILURE);
    }
    assert(argv[1] != NULL);
    if(stat(argv[1], &stats) == 0){
        printf("Dateiname: '%s' \n",argv[1]);
        printFileProperties(stats);
    }
    else{
        printf("Kann die Datei nicht finden.\n");
        printf("Bitte überprüfe ob die Datei: '%s' vorhanden ist. \n",argv[1]);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}

void printFileProperties(struct stat stats){

    //Gerätenummer
    printf("Geraetenummer: '%lu'\n",stats.st_dev);
    //I-Node Nummer
    printf("I-Node Nummer: '%lu'\n",stats.st_ino);
    //Linkzähler
    printf("Linkzähler: '%d'\n",(int)stats.st_nlink);
    //Dateityp
    printf("File type: ");
    switch (stats.st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device\n");            break;
        case S_IFCHR:  printf("character device\n");        break;
        case S_IFDIR:  printf("directory\n");               break;
        case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  printf("symlink\n");                 break;
        case S_IFREG:  printf("regular file\n");            break;
        case S_IFSOCK: printf("socket\n");                  break;
        default:       printf("unknown?\n");                break;
    }
    //Zugriffsrechte (beispiel rw-rw-rwx)
    printf("File Permissions: ");
    printf( (S_ISDIR(stats.st_mode)) ? "d" : "-");
    printf( (stats.st_mode & S_IRUSR) ? "r" : "-");
    printf( (stats.st_mode & S_IWUSR) ? "w" : "-");
    printf( (stats.st_mode & S_IXUSR) ? "x" : "-");
    printf( (stats.st_mode & S_IRGRP) ? "r" : "-");
    printf( (stats.st_mode & S_IWGRP) ? "w" : "-");
    printf( (stats.st_mode & S_IXGRP) ? "x" : "-");
    printf( (stats.st_mode & S_IROTH) ? "r" : "-");
    printf( (stats.st_mode & S_IWOTH) ? "w" : "-");
    printf( (stats.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    //Besitzer und Gruppe
    struct passwd *pwd;
    if ((pwd = getpwuid(stats.st_uid)) != NULL)
        printf("Besitzer: %-8.8s",pwd->pw_name);
    else
        printf(" %-8d", stats.st_uid); 

    struct group *grp;
    if ((grp = getgrgid(stats.st_gid)) != NULL)
        printf("Gruppe: %-8.8s", grp->gr_name);
    else
        printf(" %-8d", stats.st_gid);
    
    //Dateigröße
    printf("Dateigröße: '%ld'\n",stats.st_size);
    //Zeiteinträge
    printf("Last status change:       %s", ctime(&stats.st_ctime));
    printf("Last file access:         %s", ctime(&stats.st_atime));
    printf("Last file modification:   %s", ctime(&stats.st_mtime));

}