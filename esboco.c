#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CARTAS 32

//32 nomes de 15 letras
char animais[MAX_CARTAS][15] = {"Aguia", "Alce", "Andorinha", "Anta", "Aranha", "Avestruz", "Baleia", "Barata",
 "Boi", "Burro", "Cabra", "Camelo", "Canguru", "Carneiro", "Cavalo", "Cisne", "Cobra", "Coruja", "Corvo", "Crocodilo",
 "Elefante", "Egua", "Esquilo", "Frango", "Fuinha", "Gaivota", "Ganso", "Gato", "Gazela", "Gerbilo", "Girafa", "Golfinho"};

 int qtdJogadas = 0;

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

typedef ANIMAL *PTR_ANIMAL;

typedef struct _baralho {
    PTR_ANIMAL animal[MAX_CARTAS];
} BARALHO;

typedef struct _celula {
    struct _celula *prox;
    PTR_ANIMAL carta;
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

void empilhar(PTR_PILHA pilha, PTR_ANIMAL carta){
    PTR_CELULA celula = (PTR_CELULA)malloc(sizeof(PTR_CELULA));
    celula->carta = carta;
    celula->prox = pilha->topo;
    pilha->topo = celula;
    pilha->tamanho++;
}

void desempilhar(PTR_PILHA pilha, PTR_ANIMAL outCarta){
    if (!esta_vazio(pilha)){
        PTR_CELULA lixo = pilha->topo;
        outCarta = lixo->carta;
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

void inserir_fila(PTR_FILA fila, PTR_ANIMAL carta){
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

PTR_ANIMAL remover_fila(PTR_FILA fila){
    PTR_ANIMAL carta = fila->inicio->carta;

    PTR_CELULA celulaLixo;
    celulaLixo = fila->inicio;

    fila->inicio = fila->inicio->prox;

    fila->tamanho--;

    free(celulaLixo);
    return carta;
}

PTR_ANIMAL criar_animal(int id, float altura, float peso, float comprimento, float velocidade, float instintoAssasino){
    PTR_ANIMAL animal = (PTR_ANIMAL)malloc(sizeof(ANIMAL));
    animal->id = id;
    animal->altura = altura;
    animal->peso = peso;
    animal->comprimento = comprimento;
    animal->velocidade = velocidade;
    animal->instintoAssasino = instintoAssasino;
    return animal;
}

//Cria uma Pilha sendo baralho com cartas geradas
BARALHO criar_baralho(){
    srand(time(NULL));
    int id, i = 0;
    BARALHO baralho;
    for(i=0; i<MAX_CARTAS; i++){
        baralho.animal[i] = criar_animal(i, rand() % 10, rand() % 100,  rand() % 100,  rand() % 100,  rand() % 100);
        strcpy(baralho.animal[i]->nome, animais[i]);
    }
    return baralho;
}

int sorteia_primeiro_jogador() {
    //100 <= Máquina, 100 >= Jogador
    srand(time(NULL));
    int sorteado = rand() % 300;
    if(sorteado <= 100) {
        printf("\n A Maquina comeca");
        return 1;
    } else {
        printf("\n O Jogador comeca");
        return 2;
    }
}

void mostra_cartas_baralho(BARALHO baralho){
    for(int i =0; i<MAX_CARTAS; i++){
        printf("\n");
        printf("id: %d \n", baralho.animal[i]->id);
        printf("nome: %s \n", baralho.animal[i]->nome);
        printf("altura: %2.f metros \n", baralho.animal[i]->altura);
        printf("peso: %2.f kg \n", baralho.animal[i]->peso);
        printf("comprimento: %2.f metros \n", baralho.animal[i]->comprimento);
        printf("velocidade: %2.f km/h \n", baralho.animal[i]->velocidade);
        printf("instinto assasino: %2.f \n", baralho.animal[i]->instintoAssasino);
        printf("_____________________________________________________");
    }
}

void empilha_baralho(PTR_PILHA pilha, BARALHO baralho) {
    int i;
    for(i = 0 ; i<MAX_CARTAS; i++) {
        empilhar(pilha, baralho.animal[i]);
    }
}

void adicionar_cartas_nas_maos(PTR_FILA fila1, PTR_FILA fila2, PTR_PILHA pilha) {
    if (pilha->tamanho > 0) {
        int count = 0;
            printf("\n");
        while(count<16) {
            PTR_CELULA topo = pilha->topo;
            PTR_ANIMAL carta = topo->carta;
            inserir_fila(fila1, carta);
            pilha->topo = topo->prox;
            count++;
            //printf("fila 1, count = %d \n", count);
        }

        while(count<32) {
            PTR_CELULA topo = pilha->topo;
            if (topo) {
                PTR_ANIMAL carta = topo->carta;
                inserir_fila(fila2, carta);
                pilha->topo = topo->prox;
                count++;
            //printf("fila 2, count = %d \n", count);
            }
        }
    }
}

int jogo(PTR_FILA maoJogador, PTR_FILA maoMaquina){
    int jogaPrimeiro = sorteia_primeiro_jogador();
    PTR_ANIMAL atualJogador;
    PTR_ANIMAL atualMaq;
    int teste = 0;
    int op;
    while (1)
    {   
        atualJogador = remover_fila(maoJogador);
        atualMaq = remover_fila(maoMaquina);

        if(jogaPrimeiro == 1){
            printf("Escolha a opcao para jogar sua carta\n");
            printf("nome: %s \n", atualJogador->nome);
            printf("1 - altura: %2.f metros \n", atualJogador->altura);
            printf("2 - peso: %2.f kg \n", atualJogador->peso);
            printf("3 - comprimento: %2.f metros \n", atualJogador->comprimento);
            printf("4 - velocidade: %2.f km/h \n", atualJogador->velocidade);
            printf("5 - instinto assasino: %2.f \n", atualJogador->instintoAssasino);
            printf("Opcao: ");
            scanf("%d", &op);
            switch (op)
            {
            case 1:
                if (atualJogador->altura > atualMaq->altura)
                {
                    // Adiciona na na fila de cartas do jogador       
                }else
                {
                    // Adiciona na na fila de cartas do bot
                }
                // volta para a funcao de jogar, passando por parametro as filas
                break;
            case 2:
                if (atualJogador->peso > atualMaq->peso)
                {
                    // Adiciona na na fila de cartas do jogador       
                }else
                {
                    // Adiciona na na fila de cartas do bot
                }
                // volta para a funcao de jogar, passando por parametro as filas
                break;
            case 3:
                if (atualJogador->comprimento > atualMaq->comprimento)
                {
                    // Adiciona na na fila de cartas do jogador       
                }else
                {
                    // Adiciona na na fila de cartas do bot
                }
                // volta para a funcao de jogar, passando por parametro as filas
                break;
            case 4:
                if (atualJogador->velocidade > atualMaq->velocidade)
                {
                    // Adiciona na na fila de cartas do jogador       
                }else
                {
                    // Adiciona na na fila de cartas do bot
                }
                // volta para a funcao de jogar, passando por parametro as filas
                break;
            case 5:
                if (atualJogador->instintoAssasino > atualMaq->instintoAssasino)
                {
                    // Adiciona na na fila de cartas do jogador       
                }else
                {
                    // Adiciona na na fila de cartas do bot
                }
                // volta para a funcao de jogar, passando por parametro as filas
                break;
            
            default:
                break;
            }
        }


        if (maoJogador->tamanho == 0 || maoMaquina->tamanho == 0)
        {
            return;
        }
        printf("Jogada de numero %d \n", teste);

        if (atualJogador->altura > atualMaq->altura)
        {
            printf("\nA Carta do jogador (%s) eh maior que a do bot\n", atualJogador->nome);        
        }else
        {
            printf("\nA Carta do bot (%s)eh maior que a do player \n", atualMaq->nome);
        }
        teste++;
    }
    return 1;
}

void mostra_mao(PTR_FILA mao) {
    if (mao->tamanho > 0) {
        int count = 0;
        while(count<16 && mao->inicio) {
            count++;
            printf("carta: %d, %s, id: %d \n",count, mao->inicio->carta->nome, mao->inicio->carta->id);
            mao->inicio = mao->inicio->prox;
        }
    }
}

int salva_qtd_jogadas() {
    FILE *f = fopen("totalJogadas.txt", "w");
    if (!f)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }
    /* print integers and floats */
    fprintf(f, "total de jogadas: %d", qtdJogadas);
    fclose(f);
}

int recupera_qtd_jogadas() {
    int c;
    FILE *file;
    file = fopen("totalJogadas.txt", "r");
    if (file) {
        while ((c = getc(file)) != EOF)
            putchar(c);
            printf("%c", c);
            fclose(file);
    }
}

int main(){
    // main nao definitiva, apenas para testes
    BARALHO baralho = criar_baralho();
    PTR_PILHA pilha = criar_pilha();

    PTR_FILA maoJogador = criar_fila();
    PTR_FILA maoMaquina = criar_fila();

    empilha_baralho(pilha, baralho);
    //mostra_cartas_baralho(baralho);
    // separa a pilha do baralho no meio e adiciona em duas filas, uma para o jogador e outra para a máquina
    adicionar_cartas_nas_maos(maoJogador, maoMaquina, pilha);


    jogo(maoJogador, maoMaquina);

    /*
    printf("\n mao do jogador: \n");
    mostra_mao(maoJogador);

    printf("\n mao da maquina: \n");
    mostra_mao(maoMaquina);
    */
    // contar jogadas:
    qtdJogadas++;
    salva_qtd_jogadas();
    recupera_qtd_jogadas();
}
