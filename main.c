#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CARTAS 32

//32 nomes de 15 letras
char animais[MAX_CARTAS][15] = {"Aguia", "Alce", "Andorinha", "Anta", "Aranha", "Avestruz", "Baleia", "Barata",
 "Boi", "Burro", "Cabra", "Camelo", "Canguru", "Carneiro", "Cavalo", "Cisne", "Cobra", "Coruja", "Corvo", "Crocodilo",
 "Elefante", "Egua", "Esquilo", "Frango", "Fuinha", "Gaivota", "Ganso", "Gato", "Gazela", "Gerbilo", "Girafa", "Golfinho"};

typedef struct _animal {
    int id;
    char classe[2];
    char nome[15];
    float altura;
    float peso;
    float comprimento;
    float velocidade;
    int instintoAssasino;
} ANIMAL;

typedef struct _baralho {
    ANIMAL animal[MAX_CARTAS];
} BARALHO;

ANIMAL criar_animal(int id, float altura, float peso, float comprimento, float velocidade, float instintoAssasino){
    ANIMAL animal;
    animal.id = id;
    animal.altura = altura;
    animal.peso = peso;
    animal.comprimento = comprimento;
    animal.velocidade = velocidade;
    animal.instintoAssasino = instintoAssasino;
    return animal;
}

//Cria uma Pilha sendo baralho com cartas geradas
BARALHO criar_baralho(){
    int id, i = 0;
    BARALHO baralho;
    for(i=0; i<MAX_CARTAS; i++){
        baralho.animal[i] = criar_animal(i, rand() % 10, rand() % 100,  rand() % 100,  rand() % 100,  rand() % 100);
        strcpy(baralho.animal[i].nome, animais[i]);
    }
    return baralho;
}

int sorteia_primeiro_jogador() {
    //100 <= Máquina, 100 >= Jogador
    int sorteado = rand() % 300;
    if(sorteado <= 100) {
        printf("A Maquina comeca");
    } else {
        printf("O Jogador comeca");
    }
    return sorteado;
}

void mostra_cartas_baralho(BARALHO baralho){
    for(int i =0; i<MAX_CARTAS; i++){
        printf("\n");
        printf("id: %d \n", baralho.animal[i].id);
        printf("nome: %s \n", baralho.animal[i].nome);
        printf("altura: %2.f metros \n", baralho.animal[i].altura);
        printf("peso: %2.f kg \n", baralho.animal[i].peso);
        printf("comprimento: %2.f metros \n", baralho.animal[i].comprimento);
        printf("velocidade: %2.f km/h \n", baralho.animal[i].velocidade);
        printf("instinto assasino: %2.f \n", baralho.animal[i].instintoAssasino);
        printf("_____________________________________________________");
    }
}

int main(){
    // main nao definitiva, apenas para testes
    BARALHO baralho = criar_baralho();
    mostra_cartas_baralho(baralho);
    sorteia_primeiro_jogador();
}
