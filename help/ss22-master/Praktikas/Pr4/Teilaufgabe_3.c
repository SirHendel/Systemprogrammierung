#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void ausgabeArray(char **argument, const size_t groesse) {
  for(int x = 0; x < groesse; ++x)
    printf("%s\n", argument[x]);
  printf("\n");
}

int main(int argc, char **argv) {
  printf("Es wurden insgesamt %d Argumente uebergeben.\n\n\n",
	 argc - 1); // - 1, da erstes Argument name des Programs ist

  // Falls keine Argumente uebergeben worden sind, beende Programm
  assert(argc > 1);

  // Reservieren von Speicher
  char **alphabetischeListe = malloc((argc - 1) * sizeof(char*));

  // Pruefen ob Speicherreservierung geklappt hat
  assert(alphabetischeListe != NULL);

  // Setzen der Pointer
  for(int x = 1; x < argc; ++x) {
    alphabetischeListe[x - 1] = argv[x];
  }

  // Deklaration + Definition von benoetigten Variablen
  char *p = NULL;
  int retValue = 0;

  // Teilaufgabe B
  for(int x = 0; x < argc - 1; ++x) {
    for(int y = 1; y < argc - 1; ++y) {
      retValue = strcmp(alphabetischeListe[y - 1],
			alphabetischeListe[y]);

      if(retValue > 0) {
	p = alphabetischeListe[y - 1];
	alphabetischeListe[y - 1] = alphabetischeListe[y];
	alphabetischeListe[y] = p;
      }
    }
  }

  // Ausgabe des Arrays
  printf("Ausgabe fuer Teilaufgabe b:\n");
  ausgabeArray(alphabetischeListe, argc - 1);

  // Teilaufgabe C
  for(int x = 0; x < argc - 1; ++x) {
    for(int y = 1; y < argc - 1; ++y) {
      if(strlen(alphabetischeListe[y - 1]) >
	 strlen(alphabetischeListe[y])) {
	p = alphabetischeListe[y - 1];
	alphabetischeListe[y - 1] = alphabetischeListe[y];
	alphabetischeListe[y] = p;
      }
    }
  }

  // Ausgabe des Arrays
  printf("Ausgabe fuer Teilaufgabe c:\n");
  ausgabeArray(alphabetischeListe, argc - 1);


  // Freigabe des Speichers
  free(alphabetischeListe);
  alphabetischeListe = NULL;

  return EXIT_SUCCESS;
}
