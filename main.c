#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_CARTAS 52

typedef struct _Carta{
        char valor;
        char naipe;

} CARTA;


typedef struct _Baralho{
    CARTA cartas[MAX_CARTAS];
} BARALHO;


CARTA criarCarta(char valor){
    CARTA carta;
    carta.valor= valor;

    return carta;
}

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

/* gerarBaralho();
void deletarBaralho();
void embaralharBaralho();

void criarMao();
void pegarCarta();
void deletarMao();

void divulgarResultado();

*/

int main(){
    gerarBaralho();


}
