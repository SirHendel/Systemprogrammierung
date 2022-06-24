#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void zeigeFeldSortiert(int *, const int);

int main() {
  // Setzen der Parameter:
  const int groesse = 10;

  // Reservieren des Speicherplatzes:
  int *array = malloc(groesse * sizeof(int));

  // Auf Fehler pruefen:
  if(array == NULL) {
    fprintf(stderr, "Fehler beim reservieren des Speicherplatzes!\n");
    return EXIT_FAILURE;
  }

  // Initialisieren der srand() Funktion
  time_t t;
  srand((unsigned) time(&t));

  // Werte dem Feld zuweisen
  for(int i = 0; i < groesse; i++) {
    array[i] = (int)(rand() % 1000000);
  }

  // Aufruf der Funktion:
  zeigeFeldSortiert(array, groesse);

  // Freigeben des Speichers
  free(array);
  array = NULL;

  return EXIT_SUCCESS;
}

void zeigeFeldSortiert(int *iFeld, const int groesse) {
  // Zeiger speichern
  int **zeigerFeld = malloc(groesse * sizeof(int*));
  
  // Setzen der Zeiger auf die entsprechenden Werte in iFeld
  for(int x = 0; x < groesse; ++x) {
    zeigerFeld[x] = &iFeld[x];
  }

  // Sortierfunktion
  int *hilfsZeiger = NULL;
  for(int x = 0; x < groesse; ++x) {
    for(int y = 1; y < groesse; ++y) {
      if(*zeigerFeld[y - 1] < *zeigerFeld[y]) {
	hilfsZeiger = zeigerFeld[y];
	zeigerFeld[y] = zeigerFeld[y - 1];
	zeigerFeld[y - 1] = hilfsZeiger;
      }
    }
  }

  // Ausgabe der geforderten Werte
  printf("Index   AdresseWert   Wert\n");
  printf("=================================\n");
  for(int x = 0; x < groesse; ++x) {
    printf("%5d   %p    %10d\n", x, zeigerFeld[x], *zeigerFeld[x]);
  }

  // Speicherplatz freigeben
  free(zeigerFeld);
  zeigerFeld = NULL;
}
