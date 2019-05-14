#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "jogo21.h"
#define MAX_CARTAS 52



BARALHO gerarBaralho(){
    int i= 0;
    BARALHO baralho;
        for(i=0; i<MAX_CARTAS; i++){
            baralho.cartas[i].valor= 1;
        }

return baralho;
}


/*
void embaralharBaralho(CARTA baralho){
    int i, j, cont;
    CARTA aux;
        for(cont=0;cont<200;cont++){
            i=rand()%52; //(0-51)
            j=rand()%52;
            aux=baralho[i];
            baralho[i]=baralho[j];
            baralho[j]=aux;
        }
}

*/
