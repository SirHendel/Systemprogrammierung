#include "flaeche.h"
#include <stdio.h>
#include <math.h>

// Pi Funktion die die Zahl Pi zurueckgibt
double Pi() {
  return asin(1) * 2;
}

// kreisFlaeche Funktion welche
double kreisFlaeche(double radius) {
  // Counter inkrementation
  static int counter = 0;
  counter++;

  // Warnung fuer Aufruf der haeufiger als 5 mal stattgefunden hat
  if(counter >= 5)
    printf("\nWarnung: Funktion wurde %d aufgerufen.\n", counter);

  return Pi()*radius*radius;
}
