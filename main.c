#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

typedef struct _carta {
  struct _carta *proximo;
  int valor;
}CARTA;

typedef CARTA *PTR_CARTA;

typedef struct _baralho {
  CARTA x;
  struct _baralho_ *prox;
}BARALHO;

typedef BARALHO *PTR_BARALHO;

PTR_BARALHO criar_fila() {
  PTR_BARALHO nova_celula = ((PTR_BARALHO)malloc(sizeof(BARALHO)));
  nova_celula->x.valor = -1;
  nova_celula->prox = nova_celula;
  return nova_celula;
}

void criar_baralho(PTR_BARALHO *baralho) {
  int i, j;
  for (i=1; i<14; i++) {
    for (j=1; j<5; j++) {
      PTR_BARALHO novo = ((PTR_BARALHO)malloc(sizeof(BARALHO)));
      novo->prox = (*baralho)->prox;
      (*baralho)->prox = novo;
      novo->x.valor = i;
      (*baralho)->prox = novo;
    }
  }
}

void mostrar_baralho(PTR_BARALHO *baralho) {
  BARALHO *aux;
  aux = (*baralho)->prox;
  while (aux->x.valor != -1) {
    printf(" %d |",aux->x.valor);
    aux = aux->prox;
  }
}

CARTA pegar_carta(PTR_BARALHO *baralho) {
  BARALHO *aux;
  CARTA x;
  aux = (*baralho)->prox;
  (*baralho)->prox = aux->prox;
  x = aux->x;
  free(aux);
  return (x);
}

void devolver_carta(PTR_BARALHO *baralho, CARTA carta) {
  BARALHO *aux = ((PTR_BARALHO)malloc(sizeof(BARALHO)));
  aux->x = carta;
  aux->prox = (*baralho)->prox;
  (*baralho)->prox = aux;
}

void embaralhar_baralho(PTR_BARALHO * baralho) {
  srand(time(NULL));
  BARALHO *aux, *aux0;
  PTR_BARALHO aux1 = criar_fila(), aux2 = criar_fila();
  CARTA x;
  int p;
  aux = (*baralho)->prox;
  while(aux->x.valor != -1) {
    x = pegar_carta(&(*baralho));
    p = rand() % 100;
    if (p % 2 == 0)
      devolver_carta(&aux1, x);
    else devolver_carta(&aux2, x);
    aux = (*baralho)->prox;
  }
  (*baralho)->prox = aux1->prox;
  aux = (*baralho);
  aux0 = (*baralho)->prox;
  while(aux0->x.valor != -1) {
    aux = aux->prox;
    aux0 = aux0->prox;
  }
  aux->prox = aux2->prox;
}

void destruir_baralho(PTR_BARALHO *baralho) {
  BARALHO *aux;
  CARTA x;
  aux = (*baralho)->prox;
  while(aux->x.valor != -1) {
    x = pegar_carta(&(*baralho));
    aux = (*baralho)->prox;
  }
}

typedef struct _celula {
  struct _celula *prox;
  PTR_CARTA carta;
}CELULA;

typedef CELULA *PTR_CELULA;

//FILA MÃO DO JOGADOR
typedef struct _fila {
  PTR_CELULA inicio;
  PTR_CELULA fim;
  int tamanho;
}FILA;

typedef FILA *PTR_FILA;

void inicializar_fila(PTR_FILA fila) {
  fila->inicio = NULL;
  fila->fim = NULL;
  fila->tamanho = 0;
}

PTR_FILA criar_fila_() {
  PTR_FILA fila = (PTR_FILA)malloc(sizeof(PTR_FILA));
  inicializar_fila(fila);
  return fila;
}

void inserir_fila(PTR_FILA fila, int valor) {
  PTR_CELULA celula_ = (PTR_CELULA)malloc(sizeof(PTR_CELULA));
  celula_->carta->valor = valor;
  celula_->prox = NULL;

  if (fila->inicio == NULL) {
    fila->inicio = celula_;
  }else{
    fila->fim->prox = celula_;
  }

  fila->fim = celula_;
  fila->tamanho++;
}

void imprimir_fila(PTR_FILA fila) {
  PTR_CELULA celula_ = fila->inicio;
  while (celula_ != NULL) {
    printf("%d ", celula_->carta->valor);
    celula_ = celula_->prox;
  }
  printf("\n");
}

void salvarJogo(int soma_jogador, int soma_computador){
  FILE *file;

  file = fopen("leaderboards.txt", "a");
  if(!file)
  {
    printf("Erro ao abrir o arquivo.\n");
    exit(1);
  }
  fprintf(file, "\nResultado da partida passada do jogo 21.\n");
  fprintf(file, "Total de pontos do jogador: %d", soma_jogador); // colocar aqui a variável de somatoria do jogador.
  fprintf(file, "\nTotal de pontos do computador: %d", soma_computador); // colocar aqui a variavel de somatoria do computador.
  fprintf(file, "\n-----------------------------\n");
  fclose(file);
}

void jogar(PTR_BARALHO *baralho, int *placar_jogador, int *placar_computador) {
  srand(time(NULL));
  int soma_jogador = 0, soma_computador = 0;
  CARTA carta_jogador, carta_computador;
  char ch;
  int op2;
  PTR_FILA maojogador = criar_fila_();
  PTR_FILA maocomputador = criar_fila_();

  do {
    carta_jogador.valor = carta_computador.valor = 0;
    system("cls");
    printf("\n----------------- MENU DO JOGO -----------------\n");
    printf("\n1. Pegar carta \n");
    printf("\n2. Nao pegar carta \n");
    printf("\n3. Mao do jogador\n");
    printf("\n4. Mao do computador!\n");
    printf("\n5. Sair do jogo \n");
    printf("\nDigite um numero correspondente a opcao desejada: \n");
    scanf("%d", &op2);
    switch(op2){
    case 1:
      {
        system("cls");
        carta_jogador = pegar_carta(&(*baralho));
        printf("Voce pegou a carta: |%d| \n\n", carta_jogador.valor);
        //inserir_fila(maojogador, carta_jogador.valor);
        if (soma_computador == 0) {
          carta_computador = pegar_carta(&(*baralho));
          printf("Computador pegou a carta: |%d| \n\n", carta_computador.valor);
          //inserir_fila(maocomputador, carta_computador.valor);
          soma_computador += carta_computador.valor;
        } else {
          int r = rand() % 2;
          if (r == 1) {
            carta_computador = pegar_carta(&(*baralho));
            soma_computador += carta_computador.valor;
            printf("Computador pegou a carta |%d| \n\n", carta_computador.valor);
            //inserir_fila(maocomputador, carta_computador.valor);
          } else printf("Computador nao pegou nenhuma carta! \n\n");
        }
        soma_jogador += carta_jogador.valor;
        scanf("%c", &ch);
        break;
      }
    case 2:
      {
        system("cls");
        printf("Voce nao pegou nenhuma carta! \n\n");
        if (soma_computador == 0) {
          carta_computador = pegar_carta(&(*baralho));
          printf("Computador pegou a carta |%d| \n\n", carta_computador.valor);
          //inserir_fila(maocomputador, carta_computador.valor);
          soma_computador += carta_computador.valor;
        } else {
          int r = rand() % 2;
          if (r == 1) {
            carta_computador = pegar_carta(&(*baralho));
            soma_computador += carta_computador.valor;
            printf("Computador pegou a carta |%d| \n\n", carta_computador.valor);
            //inserir_fila(maocomputador, carta_computador.valor);
          } else printf("Computador nao pegou nenhuma carta! \n\n");
        }
        soma_jogador += carta_jogador.valor;
        scanf("%c", &ch);
        break;
      }
    case 3:
      {
        system("cls");
        printf("\nMao do jogador:");
        //imprimir_fila(maojogador);
        scanf("%c", &ch);
        break;
      }
    case 4:
      {
        system("cls");
        printf("\nMao do computador:");
        //imprimir_fila(maocomputador);
        scanf("%c", &ch);
        break;
      }
    case 5:
      {
        system("cls");
        printf("\nSaindo do Jogo\n");
        scanf("%c", &ch);
        break;
      }
    default:
      {
        printf("\nValor incorreto!!\n\n");
        scanf("%c", &ch);
      }
    }
    printf("--------- PONTUACAO DO JOGO ----------\n\n");
    printf("Soma do Jogador = %d\n\n", soma_jogador);
    printf("Soma do Computador = %d\n\n", soma_computador);
    scanf("%c", &ch);
  } while ((soma_jogador < 21) && (soma_computador < 21) && (op2 != 3));
  if ((soma_jogador > 21) && (soma_computador > 21))
    printf("O jogo ficou empatado\n");
   
  else if (soma_jogador > 21) {
    printf("Voce perdeu esta rodada\n");
    (*placar_computador) ++;
    
  } else if (soma_computador > 21) {
    printf("Voce ganhou esta rodada\n");
    (*placar_jogador) ++;
    
  } else if (soma_jogador == 21) {
    printf("Voce ganhou esta rodada\n");
    (*placar_jogador) ++;
    
  } else if (soma_computador == 21) {
    printf("Voce perdeu esta rodada\n");
    (*placar_computador) ++;
    
  } else if ((soma_jogador == 21) && (soma_computador == 21))
    printf("O jogo ficou empatado\n");
    
  else if (soma_jogador > soma_computador) {
    printf("Voce ganhou esta rodada\n");
    (*placar_jogador) ++;
    
  }else if (soma_jogador < soma_computador) {
    printf("Voce perdeu esta rodada\n");
    (*placar_computador) ++;
    
  } else printf("O jogo ficou empatado\n");
  destruir_baralho(&(*baralho));
  
}
int main() {
  
  char ch;
  int op;
  system("cls");
  PTR_BARALHO baralho = criar_fila();
  criar_baralho(&baralho);
  int i;
  for (i = 0; i < 10; i++)
    embaralhar_baralho(&baralho);
  int placar_jogador = 0, placar_computador = 0;
  do {
    system("cls");
    printf("\n----------------- MENU DO JOGO -----------------\n\n");
    printf("\n1.Olhar o Baralho\n");
    printf("\n2.Jogar\n");
    printf("\n3.Olhar a Pontuacao do jogo\n");
    printf("\n4.Zerar a Pontuacao do jogo\n");
    printf("\n5.Sair do jogo e salvar\n");
    printf("\nDigite o numero da opcao desejada: \n");
    scanf("%d", &op);
    switch (op) {
    case 1:
      {
        system("cls");
        printf("Mostrando o Baralho\n\n");
        mostrar_baralho(&baralho);
        scanf("%c", &ch);
        break;
      }
    case 2:
      {
        system("cls");
        jogar(&baralho, &placar_jogador, &placar_computador);
        scanf("%c", &ch);
        criar_baralho( &baralho);
        int i;
        for (i = 0; i < 10; i++)
          embaralhar_baralho(&baralho);
        break;
      }
    case 3:
      {
        system("cls");
        printf("Placar de %s : %d \n", "Jogador: ", placar_jogador);
        printf("Placar do %s : %d \n", "Computador: ", placar_computador);
        scanf("%c", &ch);
        break;
      }
    case 4:
      {
        system("cls");
        placar_jogador = placar_computador = 0;
        printf("Placar Zerado\n");
        scanf("%c", &ch);
        break;
      }
    case 5:
      {
        system("cls");
        salvarJogo(placar_jogador, placar_computador);
        printf("\nSaindo do Programa e salvar\n");
        scanf("%c", &ch);
        exit(0);
        break;
      }
    default:
      {
        printf("\nValor incorreto!\n");
        scanf("%c", &ch);
      }
    }
    scanf("%c", &ch);
  } while (op != 5);

  return 0;
}
