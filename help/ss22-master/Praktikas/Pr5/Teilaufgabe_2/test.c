#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

char *isSoftlink(char *dateiname);
char *isSoftlinkDynamic(char *dateiname);

int main(int argc, char **argv) {
  /* 
     Da nicht nach expliziten Fehlermeldungen die Rede war,
     verwende ich lediglich assert() um das Programm ueber-
     sichtlicher zu halten und es schneller zu Programmieren,
     aber trotzdem vor Fehlnutzung zu schuetzen.
  */
  assert(argc == 2);  // Passende Argumentenzahl

  // Pruefen ob die Datei existiert.
  assert(access(argv[1], F_OK) == 0); 

  // Funktion aufrufen und an die Variable uebergeben
  char *test = isSoftlink(argv[1]);

  if(test == NULL) { // Falls NULL, ist es kein Softlink, ...
    printf("Die Datei -%s- ist kein Softlink.\n",
	   argv[1]);
  } else { //  ... andernfalls schon.
    printf("Die Datei -%s- ist ein Sotflink zu -%s-.\n",
	   argv[1], test);
  }

  return EXIT_SUCCESS;
}
