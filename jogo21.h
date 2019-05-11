#ifndef _JOGO21_H
#define _JOGO21_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _carta_{
    int valor; // valor numerico da carta

} CARTA; //carta


typedef struct _jogador{
    int pontos;
    int qtdCartas;
    CARTA * cartas[12];

}JOGADOR;


typedef struct _jogo{
    CARTA *baralho[52];
    JOGADOR player1;
    JOGADOR player2;
}JOGO;


void gerarBaralho();
void deletarBaralho();
void embaralharBaralho();

void criarMao();
void pegarCarta();

void divulgarResultado();

#endif
