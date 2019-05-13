#ifndef _JOGO21_H
#define _JOGO21_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Definição da estrutura que representa uma carta struct
typedef struct _carta{
    char naipe;
    int valor;

} CARTA;

CARTA baralho[52];

void gerarBaralho();
void deletarBaralho();
void embaralharBaralho();

void criarMao();
void pegarCarta();

void divulgarResultado();

#endif
