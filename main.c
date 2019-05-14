/*
	TA FALTANDO COISA PRA UM SATANAS, NAO ME ODEIE, PAPAI DO CEU TE AMA S2
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CARTAS 32

typedef struct _animal {
    int id;
    //char[2] classe;
    //char* nome;
    float altura;
    float peso;
    float comprimento;
    float velocidade;
    int instintoAssasino;
} ANIMAL;

typedef struct _baralho {
    ANIMAL animal[MAX_CARTAS];
} BARALHO;

ANIMAL criar_animal(int id,float peso, float altura, float comprimento, float velocidade){
    ANIMAL animal;
    animal.velocidade = velocidade;
    animal.altura = altura;
    animal.comprimento = comprimento;
    animal.peso = peso;
    animal.id = id;
    return animal;
}


BARALHO criar_baralho(){
    int id, i = 0;
    float peso, altura, comprimento, velocidade;
    BARALHO baralho;
    for(i=0; i<MAX_CARTAS; i++){
        baralho.animal[i].altura= i;
        baralho.animal[i].comprimento = i;
        baralho.animal[i].id = i;
        baralho.animal[i].instintoAssasino = i;
        baralho.animal[i].peso = i;
        baralho.animal[i].velocidade = i;
    }
    return baralho;
}



int main(){
    BARALHO baralho = criar_baralho();
    int i =0;
    for(i=0; i<MAX_CARTAS; i++){
        printf("%f\n", baralho.animal[i].comprimento);

    }
	
    char nome[] = "samuel";
    char nome2[6];
    strcpy(nome2, nome);
    printf("%s", nome);
}
