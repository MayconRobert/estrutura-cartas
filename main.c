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

typedef struct _celula {
    struct _celula *prox;
    ANIMAL carta;
} CELULA;

typedef CELULA *PTR_CELULA;

//Cria pilha para baralho
typedef struct _pilha {
    PTR_CELULA topo;
    int tamanho;
} PILHA;

typedef PILHA *PTR_PILHA;

int esta_vazio(PTR_PILHA pilha){
    return pilha->tamanho == 0 ? 1 : 0;
}

void inicializar(PTR_PILHA pilha){
    pilha->tamanho = 0;
    pilha->topo = NULL;
}

PTR_PILHA criar_pilha(){
    PTR_PILHA pilha = (PTR_PILHA)malloc(sizeof(PTR_PILHA));
    inicializar(pilha);
    return pilha;
}

void empilhar(PTR_PILHA pilha, ANIMAL carta){
    PTR_CELULA celula = (PTR_CELULA)malloc(sizeof(PTR_CELULA));
    celula->carta = carta;
    celula->prox = pilha->topo;
    pilha->topo = celula;
    pilha->tamanho++;
}

void desempilhar(PTR_PILHA pilha, ANIMAL *outCarta){
    if (!esta_vazio(pilha)){
        PTR_CELULA lixo = pilha->topo;
        *outCarta = lixo->carta;
        pilha->topo = pilha->topo->prox;
        free(lixo);
        pilha->tamanho--;
    }
}

// fila para a mao do jogador
typedef struct _fila {
    PTR_CELULA inicio;
    PTR_CELULA fim;
    int tamanho;
} FILA;

typedef FILA *PTR_FILA;

void inicializar_fila(PTR_FILA fila){
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

PTR_FILA criar_fila(){
    PTR_FILA fila = (PTR_FILA)malloc(sizeof(PTR_FILA));
    inicializar_fila(fila);
    return fila;
}

void inserir_fila(PTR_FILA fila, ANIMAL carta){
    PTR_CELULA celula = (PTR_CELULA)malloc(sizeof(PTR_CELULA));
    celula->carta = carta;
    celula->prox = NULL;

    if (fila->inicio == NULL){
        fila->inicio = celula;
    } else {
        fila->fim->prox = celula;
    }

    fila->fim = celula;
    fila->tamanho++;
}

ANIMAL remover_fila(PTR_FILA fila){
    ANIMAL carta = fila->inicio->carta;

    PTR_CELULA celulaLixo;
    celulaLixo = fila->inicio;

    fila->inicio = fila->inicio->prox;

    fila->tamanho--;

    free(celulaLixo);
    return carta;
}

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
    srand(time(NULL));
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
    srand(time(NULL));
    int sorteado = rand() % 300;
    if(sorteado <= 100) {
        printf("\n A Maquina comeca");
    } else {
        printf("\n O Jogador comeca");
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
