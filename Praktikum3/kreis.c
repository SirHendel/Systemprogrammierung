#include <stdio.h>
#include <stdlib.h>
#include "flaeche.h"

int main(int argc, char *argv[])
{
  
  double r, u, flaeche;
  char jn;
  int erg;
  int anzDerVersuche = 0; 
    
  
  do {
    anzDerVersuche++;
    printf("Geben Sie den Radius ein : ");
    erg=scanf("%lg",&r);     
        
    u = 2*Pi()*r;
    flaeche = kreisFlaeche(r);
    printf("Umfang: %lg  Flaeche: %lg \n", u, flaeche);
    printf(" Nochmal (j/n)?");
    erg = scanf(" %c", &jn);
  } while(jn == 'j');
  printf("Versuchte versuche: %d", anzDerVersuche);
  return EXIT_SUCCESS;    
}      
