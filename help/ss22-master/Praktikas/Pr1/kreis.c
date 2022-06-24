/* ----------------------- Berechnungen am Kreis ------------------------ */

/* Definition der Konstanten Pi durch Präprozessoranweisung #define       */
/* jedes PI wird im Text durch 3.1415926 ersetzt                          */

#define PI 3.1415926

/* Einfügen benötigter Headerdateien in Quelltext   */
/* - enthalten Prototypen von Bibliotheksfunktionen */
/*   wie printf(), scanf()                          */

#include <stdio.h>
#include <stdlib.h>

/* Definition der Funktion kreisFlaeche() */
double kreisFlaeche(double radius)
{
  return PI*radius*radius;
}

/* Definition der Funktion main()                   */
int main(int argc, char *argv[])
{
  /* Definition lokaler Variablen                 */
  double r, u, flaeche;
  char jn;
  int erg;
  int anzDerVersuche = 0; // Anzahl der Versuche
    
  /* Anweisungsteil */
  do {
    anzDerVersuche++;
    printf("Geben Sie den Radius ein : ");
    erg=scanf("%lg",&r);     // erg sollte ueberprueft werden!
        
    u = 2*PI*r;
    flaeche = kreisFlaeche(r);
    printf("Umfang: %lg  Flaeche: %lg \n", u, flaeche);
    printf(" Nochmal (j/n)?");
    erg = scanf(" %c", &jn);
  } while(jn == 'j');
  printf("Versuchte versuche: %d", anzDerVersuche);
  return EXIT_SUCCESS;     /* EXIT_SUCCESS (0) alles ok */
}                           
