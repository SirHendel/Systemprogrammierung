// Fuer PATH_MAX
#include <linux/limits.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char *isSoftlink(char *dateiname) {
  // Deklaration der benoetigten Variablen
  static char hardlink[PATH_MAX];
  struct stat buffer;
  int retValue = 0;

  // Aufruf von lstat und pruefe auf Fehler
  if(lstat(dateiname, &buffer) == -1) {
    perror("Fehler beim Aufrufen von lstat");
    exit(EXIT_FAILURE);
  }

  // Pruefe ob Softlink oder nicht
  if(S_ISLNK(buffer.st_mode)) {
    // Lese "echten" Dateinamen aus
    if(readlink(dateiname, hardlink, PATH_MAX) == -1) {
      perror("Feher beim Aufrufen von readlink");
      exit(EXIT_FAILURE);
    }
    return hardlink;
  } else {
    return NULL;
  }
}

/*
  Im folgenden eine weitere Methode wie man mit gleicher Signatur auf eine
  static Variable verzichten koennte (mit dem Nachteil, dass man den Speicher
  freigeben muesste.)
*/
char *isSoftlinkDynamic(char *dateiname) {
  // Deklaration der benoetigten Variablen
  char *hardlink;
  struct stat buffer;
  int retValue = 0;

  // Speicher reservieren
  hardlink = malloc(sizeof(char) * PATH_MAX);
  if(!hardlink) {
    fprintf(stderr, "Fehler beim Reservieren von Speicherplatz");
    exit(EXIT_FAILURE);
  }

  // Aufruf von lstat und pruefe auf Fehler
  if(lstat(dateiname, &buffer) == -1) {
    perror("Fehler beim Aufrufen von lstat");
    exit(EXIT_FAILURE);
  }

  // Pruefe ob Softlink oder nicht
  if(S_ISLNK(buffer.st_mode)) {
    // Lese "echten" Dateinamen aus
    if(readlink(dateiname, hardlink, PATH_MAX) == -1) {
      perror("Feher beim Aufrufen von readlink");
      exit(EXIT_FAILURE);
    }
  } else {
    /* 
       Falls kein Softlink, den allok. Speicher 
       wieder freigeben, da sonst der allokierte 
       Speicher nicht geloescht wird.
    */
    free(hardlink);
    hardlink = NULL;
  }
  return hardlink;
}
