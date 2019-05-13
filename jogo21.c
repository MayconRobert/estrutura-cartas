#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "jogo21.h"

void gerarBaralho(CARTA baralho){
    char naipes[4]={'o','c','e','p'};
    int i, j, k;
    k=0;
        for(i=0;i<4;i++){
            for(j=2;j<=14;j++){
                baralho[k]->naipe=naipes[i];
                baralho[k]->valor=j;
                k++;                
            }
        }
}

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

