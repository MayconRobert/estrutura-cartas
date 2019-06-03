#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct _carta
{
    struct _carta *proximo;
    int valor;
} CARTA;

typedef CARTA *PTR_CARTA;

typedef struct _baralho
{
    PTR_CARTA topo;
    int tamanho;
} BARALHO;

typedef BARALHO *PTR_BARALHO;

int esta_vazio(PTR_BARALHO baralho)
{
    return baralho->tamanho == 0 ? 1 : 0;
}

void inicializar(PTR_BARALHO baralho)
{
    baralho->tamanho = 0;
    baralho->topo = NULL;
}

PTR_BARALHO criar_baralho()
{
    PTR_BARALHO baralho = (PTR_BARALHO)malloc(sizeof(PTR_BARALHO));
    inicializar(baralho);
    return baralho;
}

void empilhador(PTR_BARALHO baralho, int valor)
{
    PTR_CARTA carta = (PTR_CARTA)malloc(sizeof(PTR_CARTA));
    carta->valor = valor;
    carta->proximo = baralho->topo;
    baralho->topo = carta;
    baralho->tamanho++;
}

void despilhador(PTR_BARALHO baralho, int *outValor)
{
    if (!esta_vazio(baralho))
    {
        PTR_CARTA lixo = baralho->topo;
        *outValor = lixo->valor;
        baralho->topo = baralho->topo->proximo;
        free(lixo);
        baralho->tamanho--;
    }
}

void criar_cartas(int *pcartas)
{
    int i,j;
    int x=0;
    for(j=0; j<4; j++)
    {
        for(i=1; i<=13; i++)
        {
            if(i<10)
            {
                *(pcartas+x)=i;

            }
            else
            {
                *(pcartas+x)=10;
            }
            x++;
        }
    }
}

void embaralhar_baralho(int *pcartas)
{
    int i,temp,random;
    srand(time(NULL));
    for (i=0; i<52; i++)
    {
        random=rand()%52;
        temp=*(pcartas+i);
        *(pcartas+i)=*(pcartas+random);
        *(pcartas+random)=temp;
    }
}

void empilhar_baralho()
{
    PTR_BARALHO baralho = criar_baralho();
    int *pcartas;
    int cartas[52];
    pcartas=cartas;
    criar_cartas(pcartas);
    embaralhar_baralho(pcartas);
    int i;
    printf("\n\n");
    for(i=0; i<52; i++)
    {
        empilhador(baralho,cartas[i]);
        printf("%d\t",baralho->topo->valor);//esse print serve apenas como teste para ver se ta tudo funcionando
    }
}

int pegar_carta_topo(PTR_BARALHO baralho)
{
    CARTA *x;
    x = baralho->topo->valor;
    return x;
}

int sorteio_iniciar_partida()
{
    srand(time(NULL));
    int sorteio = rand() % 100;
    if(sorteio <= 100)
    {
        printf("\n Quem começa é a Máquina!!");
    }
    else
    {
        printf("\n Quem começa é o Jogador!!");
    }
    return sorteio;
}


// Começo da parte de fila
typedef struct _celula
{
    struct _celula *prox;
    PTR_CARTA numero;
} CELULA;

typedef CELULA *PTR_CELULA;

typedef struct _fila
{
    PTR_CELULA inicio;
    PTR_CELULA fim;
    int tamanho;
} FILA;

typedef FILA *PTR_FILA;

int filaVazia(PTR_FILA fila)
{
    return fila->tamanho == 0 ? 1 : 0;
}

void inicializar_fila(PTR_FILA fila)
{
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

PTR_FILA criar_fila()
{
    PTR_FILA fila = (PTR_FILA)malloc(sizeof(PTR_FILA));
    inicializar_fila(fila);
    return fila;
}

void imprimir_fila(PTR_FILA fila)
{
    PTR_CELULA celula = fila->inicio;
    while (celula != NULL)
    {
        printf("%d ", celula->numero);
        celula = celula->prox;
    }
    printf("\n");
}

void inserir_fila(PTR_FILA fila, PTR_CARTA numero)
{
    PTR_CELULA celula = (PTR_CELULA)malloc(sizeof(PTR_CELULA));
    celula->numero = numero;
    celula->prox = NULL;

    if(fila->inicio == NULL)
    {
        fila->inicio = celula;
    }
    else
    {
        fila->fim->prox = celula;
    }

    fila->fim = celula;
    fila->tamanho++;
}

int remover_fila(PTR_FILA fila)
{
    int numero = fila->inicio->numero;

    PTR_CELULA celulaLixo;
    celulaLixo = fila->inicio;

    fila->inicio = fila->inicio->prox;

    fila->tamanho--;

    free(celulaLixo);
    return numero;
}

void jogar(PTR_BARALHO baralho){
    int numero;
    int soma1=0, soma2=0;
    CARTA x1,x2;
    int sorteio_quem_joga = sorteio_iniciar_partida();
    do
    {
        x1.valor=x2.valor=0;
        system("cls");
        printf("1- Pegar Carta!\n");
        printf("2- Passar a vez!\n");
        printf("\nEscolha a opcao desejada: \n");
        scanf("%d", &numero);

        switch(numero)
        {
        case 1:
            system("cls"); //limpar a tela
            x1.valor = pegar_carta_topo(baralho);
            printf("Você pegou a carta %d\n", x1.valor);
            soma1+= x1.valor;
            break;

        case 2:
            system("cls"); //limpar a tela
            x2.valor = pegar_carta_topo(baralho);
            printf("O computador pegou a carta! %d\n", x2.valor);
            soma2+= x2.valor;
            break;

        default:
            printf("Opcao inválida!\n ");
        }
    }
    while((soma1 < 21) && (soma2 < 21));

    if ((soma1>21) && (soma2>21))
    {
        printf("O jogo ficou empatado\n");
    }
    else if(soma1 > 21)
    {
        printf("Você ganhou esta rodada\n");
    }
    else if(soma2 > 21)
    {
        printf("Você perdeu esta rodada\n");
    }
    else if(soma1 == 21)
    {
        printf("Você ganhou esta rodada\n");
    }
    else if(soma2 == 21)
    {
        printf("Você perdeu esta rodada\n");
    }
    else if ((soma1==21) && (soma2==21))
    {
        printf("O jogo ficou empatado\n");
    }
    else if (soma1>soma2)
    {
        printf("Você ganhou esta rodada\n");
    }
    else if (soma1<soma2)
    {
        printf("Você perdeu esta rodada\n");
    }
    else
    {
        printf("O jogo ficou empatado\n");
    }
}

int main()
{
setlocale(LC_ALL, "Portuguese");

//PTR_FILA fila = criar_fila();
//empilhar_baralho();
//inserir_fila(fila, 3);
//inserir_fila(fila, 5);
//inserir_fila(fila, 7);
//remover_fila(fila);
//imprimir_fila(fila);

//Testar o jogo
    //Primeiro: precisamos dessas funções acionadas:
         /*Criar a Fila*/
        /*Criar o Baralho*/
        /*Embaralhar o Baralho*/

    //Segundo: obter um menu para testar o jogo
int op;
do{
     system("cls");
     printf("\n*************** Menu ***************\n\n");
     printf("\n1- Mostrar o Baralho\n");
     printf("\n2- Jogar\n");
     printf("\n3- Sair \n");
     printf("\nEntre com a sua Opção: \n");
     scanf("%d", &op);
    switch(op){
        case 1:{
           system("cls");
           printf("Mostrando o Baralho\n");
           empilhar_baralho();
           break;
        }
        case 2:{
           system("cls");
           /*Criando o Baralho */
            PTR_BARALHO baralho = criar_baralho();
           jogar(&baralho);
           /*Embaralhando o Baralho*/
           int *pcartas;
           int cartas[52];
           pcartas=cartas;
           embaralhar_baralho(pcartas);
           break;
        }
         case 3:{
           system("cls");
           printf("\nSaindo do Programa\n");
           exit (0);
           break;
        }
        default:{
           printf("\nEntre com um valor válido!\n");
        }
    }
}while (op != 3);
return 0;
}
