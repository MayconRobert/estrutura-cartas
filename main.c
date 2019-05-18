/*<<<<<<< HEAD*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct elem{
    int info;
    struct elem *lig;
}tipo_elem;

typedef struct{
    tipo_elem *inicio;
    tipo_elem *fim;
}fila;

fila q;

void definir(fila *q){
/*Cria uma fila vazia. Deve ser usado antes de qualquer outra operação*/
    q->inicio = NULL;
    q->fim = NULL;
}

int vazia (fila *q){
/*Retorna true se fila não contém elementos, false caso contrário*/
    return (q->inicio == NULL);
}

void tornar_vazia (fila *q){
/*Reinicializa uma fila existente q como uma fila vazia removendo todos os seus elementos.*/
    tipo_elem *ndel, *nextno;
        if(!vazia(q)){
            nextno = q->inicio;
                while (nextno != NULL){
                    ndel = nextno;
                    nextno = nextno->lig;
                    free(ndel);
                }
        }
    definir(q);
}

int inserir(fila *q, int info){
/*Adiciona um item no fim da fila q. Retorna true se operação realizada com sucesso, false caso contrário*/
    tipo_elem *p;
    p = malloc(sizeof(tipo_elem));
        if (p == NULL){
        return 0;
        }
            p->info = info;
            p->lig = NULL;
                if (vazia(q)){
                q->inicio = p;

                }else{
                 q->fim->lig = p;
                 q->fim = p;
                 return 1;
}
}

int remover(fila *q, int *info){
/*Remove um item do início da fila q. Retorna true se operação realizada com sucesso, false caso contrário*/
    tipo_elem *p;
        if(vazia(q)){
            return 0;
        }
        p = q->inicio;
        *info = p->info;
        q->inicio = p->lig;
            if(q->inicio == NULL){
                q->fim = NULL;
                }
                free(p);
                return 1;
}

int tamanho(fila *q){
/*Retorna o tamanho da fila*/
    tipo_elem *p;
    int cont = 0;
    p = q->inicio;
        while(p != NULL){
            cont ++;
            p = p->lig;
        }
            return cont;
}

int comecoFila(fila *q, int *item){
/*Mostra o começo da fila sem remover o item. Retorna true se operação realizada com sucesso, false caso contrário*/
    if(vazia(q)){
        return 0;
    }
        *item = q->inicio->info;
        return 1;
}


/*int main(){
    printf("Hello world!\n");
    return 0;
}*/

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



int main(){
empilhar_baralho();
getchar();
return 0;
}
/*>>>>>>> 12f8c0c641769482b9fa1de0d725bce19af5d9a3*/
