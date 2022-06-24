#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char *argv[]){
    
  struct stat buf;
    
  //Fehler - falsche Parameteranzahl
    
  if(argc != 2){
    fprintf(stderr,"Falsche Parameteranzahl - Aufruf mit einem "
	    "Parameter in Form des Dateinamens\n");
    return EXIT_FAILURE;
  }    
    
  if(stat(argv[1], &buf)==0){
    printf("Gerätenummer:\t %ld\n", buf.st_dev);
    printf("i-Node Nummer:\t %ld\n", buf.st_ino);
    printf("Linkzähler:\t %d\n", buf.st_nlink);
        
    int Dateityp;

    Dateityp = buf.st_mode & S_IFMT;
    switch (Dateityp) {
    case S_IFREG: puts("Dateityp:\t reguläre Datei"); break; //warum puts?
    case S_IFLNK: puts("Dateityp:\t Symbolischer Link"); break;
    case S_IFDIR: puts("Dateityp:\t Verzeichnis"); break;
    default: puts("Dateityp:\t Sonstiges");
    }
        
    int i;
    char datei_rwx[10];
    char rechte_rwx[] = "rwxrwxrwx";

    int rechte[] = {
      S_IRUSR,S_IWUSR,S_IXUSR,   /* Zugriffsrechte User    */
      S_IRGRP,S_IWGRP,S_IXGRP,   /* Zugriffsrechte Gruppe  */
      S_IROTH,S_IWOTH,S_IXOTH    /* Zugriffsrechte der Rest */
    };
        
    for(i = 0; i < 9; i++) {
      if(buf.st_mode & rechte[i])
	datei_rwx[i]=rechte_rwx[i];  
      else
	datei_rwx[i] = '-'; 
    }
        
    printf("Zugriffsrechte:\t %s\n",datei_rwx);
        
        
    struct passwd *nameb;
    nameb = getpwuid(buf.st_uid);
        
    printf("Benutzer Name:\t %s\n", nameb->pw_name);
    printf("Benutzer ID:\t %d\n", buf.st_uid);
        
    struct group *nameg;
    nameg = getgrgid(buf.st_gid);
        
    printf("Gruppen Name:\t %s\n", nameg->gr_name);
    printf("Gruppen ID:\t %d\n", buf.st_gid);
        
    printf("Dateigröße:\t %ld Bytes\n", buf.st_size);
        
    char datum[20]; //warum 20?
        
    strftime(datum,20,"%d.%m.%Y %H:%M:%S",localtime(&buf.st_atime));
        
    printf("letzter Zugriff:\t %s\n", datum);
    
    strftime(datum,20,"%d.%m.%Y %H:%M:%S",localtime(&buf.st_mtime));
        
    printf("letzte Änderung:\t %s\n", datum);
        
    strftime(datum,20,"%d.%m.%Y %H:%M:%S",localtime(&buf.st_ctime));
        
    printf("letzte Statusänderung:\t %s\n", datum);
        
    return EXIT_SUCCESS;
        
  } else {
    fprintf(stderr, "Die Datei wurde nicht gefunden.\n");
    return EXIT_FAILURE;
  }
}
