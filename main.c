#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_CARTAS 52

const char valores = "A23456789TJQK";

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
    int i = 0;
    int j = 0;
    BARALHO baralho;
    for(j=0; j>=3; i++){
        for(i=0; i<13; i++){
            baralho.cartas[i].valor= valores[i];
        }
    }
return baralho;
}


/*
BARALHO embaralharBaralho(){
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
    BARALHO baralho = gerarBaralho();
printf("%c",baralho);

}
