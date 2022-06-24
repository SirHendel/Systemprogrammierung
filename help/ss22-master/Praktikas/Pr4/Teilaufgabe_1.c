#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void zeigeFeld(int *, int);

int main(int argc, char **argv) {
  // Setzen der Paramter:
  const int groesse = 10;

  // Reservieren des Speichers:
  int *array = malloc(groesse * sizeof(int));
 
  // Pruefen auf Fehler:
  if(array == NULL) {
    fprintf(stderr, "Fehler beim Initialisieren des array - Pointers!\n");
    return EXIT_FAILURE;
  }

  // Initialisierung der srand() Funtkion
  time_t t;
  srand((unsigned) time(&t));

  // Initialisieren der integer Werte mit entsprechenden Zufallszahlen
  for(int i = 0; i < groesse; i++)
    array[i] = (int)(rand() % 1000000);

  // Aufruf der Funktion:
  zeigeFeld(array, groesse);

  // Freigeben des Speichers:
  free(array);
  array = NULL;

  return EXIT_SUCCESS;
}

void zeigeFeld(int *zeiger, const int groesse) {
  // Header ausgeben
  printf("Index   Werte\n===============\n");

  // Ausgabe der Werte
  for(int x = 0; x < groesse; ++x) {
    printf("%5d     %7d\n", x, zeiger[x]);
  }
}
