#include <stdio.h>
#include <stdlib.h>
#include "flaeche.h"

int main(int argc, char** argv) {
  double r, u, flaeche;
  char jn;
  int erg;

  do {

    printf("Geben Sie den Radius ein : ");

    // Eingabe von der zu berechnenden Zahl
    erg = scanf("%lg", &r);
    while(getchar() != '\n'); // Buffer loeschen

    // Berechnung
    u = 2 * Pi() * r;
    flaeche = kreisFlaeche(r);
    printf("Umfang %lg\tFlaeche: %lg\n", u, flaeche);
    printf("Nochmal (j|n)?");

    // char einlesen fuer Abfrage zum erneuten berechnen
    erg = scanf("%c", &jn);
    while(getchar() != '\n'); // Buffer loeschen

  }while(jn == 'j'); // Falls j gedrueckt, starte neu

  return EXIT_SUCCESS;
}
