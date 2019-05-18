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


int main(){
    printf("Hello world!\n");
    return 0;
}
