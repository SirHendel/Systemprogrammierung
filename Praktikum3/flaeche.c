#include <stdio.h>
#include <stdlib.h>
#include "flaeche.h"
#include <math.h>

//#define PI 3.1415926
double Pi() {
  return asin(1) * 2;
}

/* Definition der Funktion kreisFlaeche() */
double kreisFlaeche(double radius)
{ 
  static int zaehler = 0;
  zaehler++;
  
  if(zaehler > 4){
    printf("Aufruf %d Warnung! \n", zaehler);
  }
    

  return Pi()*radius*radius;
}