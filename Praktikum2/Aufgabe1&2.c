#include <stdio.h>
#include <stdlib.h>

int main(int args, char *argc[]){
    int scanres_;
    char cvar;
    while(scanf(" %c", &cvar) && cvar!='q'){
        //scanres_ = scanf(" %d", &ivar);
        printf("Anzeige '%c': %c 0%d 0x%02x  \n",cvar,cvar,cvar,cvar);
    }
    printf("Anzeige '%c': %c %d %02x  \n",cvar,cvar,cvar,cvar);
    return 0;
}