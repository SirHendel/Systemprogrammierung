#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv) {
  // CHECK: Pruefe ob Argumentenzahl passt
  if(argc != 3) {
    fprintf(stderr, "Die Parameteranzahl stimmt nicht.\n"
	    "Bitte rufe das Program wie folgt auf:\n"
	    "copy [QUELLDATEI] [ZIELDATEI]\n");
    exit(EXIT_FAILURE);
  }
  int retValue = 0;

  // Deklaration und Definition der benoetigten Pfade
  char *pathReadingFile = argv[1];
  char *pathWritingFile = argv[2];

  // Informationen ueber die Quelldatei
  struct stat bufReadingFile;

  // Deklaration der Filedeskriptoren
  int fd_ReadingFile;
  int fd_WritingFile;
  
  // CHECK: Pruefe ob Quelldatei existiert
  if(access(pathReadingFile, F_OK) == -1) {
    fprintf(stderr, "Die Quelldatei existiert nicht.\n");
    exit(EXIT_FAILURE);
  }

  // CHECK: Pruefe ob Leserecht vorhanden ist fuer die Quelldatei
  if(access(pathReadingFile, R_OK) == -1) {
    fprintf(stderr, "Die Quelldatei ist nicht lesbar\n");
    exit(EXIT_FAILURE);
  } 

  // Quelldatei oeffnen
  fd_ReadingFile = open(pathReadingFile, O_RDONLY);
  
  // CHECK: Pruefe ob es ein Problem beim Oeffnen der Quelldatei gab
  if(fd_ReadingFile == -1) { 
    perror("Fehler beim Oeffnen der Quelldatei");
    exit(EXIT_FAILURE);
  }

  // Hole informationen ueber die Quelldatei
  if(fstat(fd_ReadingFile, &bufReadingFile) == -1) {
    perror("Fehler beim Aufruf von fstat");
    exit(EXIT_FAILURE);
  }

  // CHECK: Pruefe ob Quelldatei eine regulaere Datei ist
  if(S_ISREG(bufReadingFile.st_mode) == 0) {
    fprintf(stderr, "Die Quelldatei ist keine requlaere Datei\n");
    exit(EXIT_FAILURE);
  }
  
  if(access(pathWritingFile, F_OK) == 0) { // Die Zieldatei existiert bereits
    // Ueberpruefe ob Nutzer Schreibrecht hat
    if(access(pathWritingFile, W_OK) != 0) {
      fprintf(stderr, "Fuer die Zieldatei besteht kein Schreibrecht.\n");
      exit(EXIT_FAILURE);
    }

    // Oeffnen der Zieldatei
    fd_WritingFile = open(pathWritingFile, O_WRONLY);

    // CHECK: Pruefen ob die Zieldatei ein Verzeichnis ist
    if (errno == EISDIR) { 
      fprintf(stderr, "Die Zieldatei ist ein Verzeichnis\n");
      exit(EXIT_FAILURE);
    } else if(fd_WritingFile == -1) { 
      // CHECK: Pruefe ob Fehler beim Oeffnen der Zieldatei
      perror("Fehler beim Oeffnen der Zieldatei");
      exit(EXIT_FAILURE);
    }

    /* Hier wird gefragt, ob die Datei ueberschriebenw werden soll. */
    char inp = ' ';
    do {
      printf("Wollen Sie die datei ueberschreiben? (y/n)\n");
      inp = getchar();

      if(inp == 'n')
	exit(EXIT_SUCCESS);
    
      while(getchar() != '\n') { }
    } while (inp != 'y');
  } else { // Die Zieldatei existiert noch nicht
    // Erstellen der Datei
    fd_WritingFile = creat(pathWritingFile, bufReadingFile.st_mode);

    // CHECK: Pruefe ob es ein Problem beim Erstellen der Zieldatei gab
    if(fd_WritingFile == -1) {
      perror("Fehler beim Erstellen der Zieldatei");
      exit(EXIT_FAILURE);
    }
  }

  // Puffer entsprechend der optimalen Puffergroesse ermitteln.
  const blksize_t bufSize = bufReadingFile.st_blksize;
  int wdh = (int)bufReadingFile.st_blocks;
  if(bufSize != 512) wdh = wdh / (bufSize/512);
  
  // Den Puffer im Speicher allokieren
  char *buffer = malloc(bufSize);
  
  /* Schleife, die entsprechend der Anzahl der Bloecke die Datei
     Stueckweise kopiert */
  for(int kopieren = 0; kopieren < wdh; ++kopieren) {
    // Einlesen bis zum Ende des Puffers (oder der Datei)
    if(read(fd_ReadingFile, buffer, bufSize) == -1) {
      perror("Fehler beim Lesen");
      exit(EXIT_FAILURE);
    }

    // Schreiben des eingelesen Puffers bis maximal des return Values
    if(write(fd_WritingFile, buffer, retValue) == -1) {
      perror("Fehler beim Schreiben");
      exit(EXIT_FAILURE);
    }
  }

  // Friegeben des Pufferspeichers
  free(buffer);
  buffer = NULL;

  // Schliessen der Filedeskriptoren
  if (close(fd_ReadingFile) == -1) {
    perror("Fehler beim Schliessen der Quelldatei");
    exit(EXIT_FAILURE);
  }

  if (close(fd_WritingFile) == -1) {
    perror("Fehler beim Schliessen der Zieldatei");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
