#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _carta {
    struct _carta *proximo;
    int valor;
} CARTA;

typedef CARTA *PTR_CARTA;

typedef struct _baralho {
    PTR_CARTA topo;
    int tamanho;
} BARALHO;

typedef BARALHO *PTR_BARALHO;

int esta_vazio(PTR_BARALHO baralho){
    return baralho->tamanho == 0 ? 1 : 0;
}

void inicializar(PTR_BARALHO baralho){
    baralho->tamanho = 0;
    baralho->topo = NULL;
}

PTR_BARALHO criar_baralho(){
    PTR_BARALHO baralho = (PTR_BARALHO)malloc(sizeof(PTR_BARALHO));
    inicializar(baralho);
    return baralho;
}

void empilhador(PTR_BARALHO baralho, int valor){
    PTR_CARTA carta = (PTR_CARTA)malloc(sizeof(PTR_CARTA));
    carta->valor = valor;
    carta->proximo = baralho->topo;
    baralho->topo = carta;
    baralho->tamanho++;
}

void despilhador(PTR_BARALHO baralho, int *outValor){
    if (!esta_vazio(baralho)){
        PTR_CARTA lixo = baralho->topo;
        *outValor = lixo->valor;
        baralho->topo = baralho->topo->proximo;
        free(lixo);
        baralho->tamanho--;
    }
}

void criar_cartas(int *pcartas){
    int i,j;
    int x=0;
    for(j=0; j<4; j++){
        for(i=1; i<=13; i++){
            if(i<10){
                *(pcartas+x)=i;

            }else{
                *(pcartas+x)=10;
            }
            x++;
        }
    }
    }

void embaralhar_baralho(int *pcartas){
int i,temp,random;
srand(time(NULL));
for (i=0;i<52;i++){
    random=rand()%52;
    temp=*(pcartas+i);
    *(pcartas+i)=*(pcartas+random);
    *(pcartas+random)=temp;
}
}

void empilhar_baralho(){
PTR_BARALHO baralho = criar_baralho();
int *pcartas;
int cartas[52];
pcartas=cartas;
criar_cartas(pcartas);
embaralhar_baralho(pcartas);
int i;
printf("\n\n");
for(i=0;i<52;i++){
empilhador(baralho,cartas[i]);
printf("%d\t",baralho->topo->valor);//esse print serve apenas como teste para ver se ta tudo funcionando
}
}

int pegar_carta_topo(PTR_BARALHO baralho){
    CARTA *x;
    x = baralho->topo->valor;
return x;
}

int sorteio_iniciar_partida(){
    srand(time(NULL));
    int sorteio = rand() % 100;
    if(sorteio <= 100) {
        printf("\n Quem começa é a Máquina!!");
    } else {
        printf("\n Quem começa é o Jogador!!");
    }
    return sorteio;
}
// Fila
typedef struct _celula {
    struct _celula *prox;
    CARTA carta;
} CELULA;

typedef CELULA *PTR_CELULA;
// fila para a mao do jogador
typedef struct _fila {
    PTR_BARALHO inicio;
    PTR_BARALHO fim;
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

void inserir_fila(PTR_FILA fila, CARTA carta){
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

CARTA remover_fila(PTR_FILA fila){
    CARTA carta = fila->inicio->carta;

    PTR_CELULA celulaLixo;
    celulaLixo = fila->inicio;

    fila->inicio = fila->inicio->prox;

    fila->tamanho--;

    free(celulaLixo);
    return carta;
}

int main(){
empilhar_baralho();
return 0;
}
