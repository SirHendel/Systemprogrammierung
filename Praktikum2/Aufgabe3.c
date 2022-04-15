#include <stdio.h>
#include <stdlib.h>

int main(int args, char *argc[]){
    printf("Der Typ char belegt %d Adressen \n",sizeof(char));
    printf("Der Typ short belegt %d Adressen \n",sizeof(short));
    printf("Der Typ int belegt %d Adressen \n",sizeof(int));
    printf("Der Typ long belegt %d Adressen \n",sizeof(long));
    printf("Der Typ float belegt %d Adressen \n",sizeof(float));
    printf("Der Typ double belegt %d Adressen \n",sizeof(double));

    return 0;
}