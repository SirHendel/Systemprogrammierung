#include <stdio.h>
#include <stdlib.h>

int main() {
  // Deklaration benoetigter Variablen
  int einIntArray[2];
  double einDoubleArray[2];

  // Ausgabe der geforderten Daten
  printf("Der Typ int belegt %ld Adressen.\n", sizeof(int));
  printf("\tAdresse [0] %p -- Adresse [1] %p\n",
	 &einIntArray[0], &einIntArray[1]);
  printf("Der Typ double belegt %ld Adressen.\n", sizeof(double));
  printf("\tAdresse [0] %p -- Adresse [1] %p\n",
	 &einDoubleArray[0], &einDoubleArray[1]);
  printf("Der Typ char belegt %ld Adressen.\n", sizeof(char));
  printf("Der Typ short belegt %ld Adressen.\n", sizeof(short));
  printf("Der Typ long belegt %ld Adressen.\n", sizeof(long));
  printf("Der Typ float belegt %ld Adressen.\n", sizeof(float));

  return EXIT_SUCCESS;
}
