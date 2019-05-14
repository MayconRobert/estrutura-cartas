#ifndef _JOGO21_H
#define _JOGO21_H

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


// gerarBaralho();
void deletarBaralho();
void embaralharBaralho();

void criarMao();
void pegarCarta();
void deletarMao();

void divulgarResultado();

#endif
