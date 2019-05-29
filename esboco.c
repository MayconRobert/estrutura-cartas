#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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
    float instintoAssasino;
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
        baralho.animal[i] = criar_animal(i, (rand() % 10) + 1, (rand() % 99) + 1,  (rand() % 99) + 1,  (rand() % 99) + 1,  (rand() % 99) + 1);
        strcpy(baralho.animal[i]->nome, animais[i]);
    }
    
    srand ( time(NULL) ); 
    for (int l = 32-1; l > 0; l--) 
    { 
        int j = rand() % (l+1); 
        PTR_ANIMAL temp = baralho.animal[l];
        baralho.animal[l] = baralho.animal[j];
        baralho.animal[j] = temp;

    } 
    return baralho;
}


int sorteia_primeiro_jogador() {
    //100 <= Máquina, 100 >= Jogador
    srand(time(NULL));
    int sorteado = rand() % 300;
    if(sorteado <= 100) {
        printf("\t\tA Maquina comeca\n");
        return 1;
    } else {
        printf("O Jogador comeca\n");
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
    int qmJoga = sorteia_primeiro_jogador();
    PTR_ANIMAL atualJogador;
    PTR_ANIMAL atualMaq;
    int numJogada = 1;
    int op;
    while (1)
    {   
        printf("\t\t\nJogada de numero %d\n\n", numJogada);
        printf("Tamanho da mao do jogador %d \n", maoJogador->tamanho);
        printf("Tamanho da mao do bot %d \n", maoMaquina->tamanho);
        

        if (maoMaquina->tamanho == 0)
        {
            salva_qtd_jogadas(numJogada, 1);
            return 1;
        }else if(maoJogador->tamanho == 0)
        {
            salva_qtd_jogadas(numJogada, 0);
            return 2;
        }
        atualJogador = remover_fila(maoJogador);
        atualMaq = remover_fila(maoMaquina);
        //Alterna entre quem joga na rodada
        if(qmJoga%2 != 1){
            printf("Escolha a opcao para jogar sua carta\n");
            printf("Nome: %s \n", atualJogador->nome);
            printf("1 - Altura: %2.f metros \n", atualJogador->altura);
            printf("2 - Peso: %2.f kg \n", atualJogador->peso);
            printf("3 - Comprimento: %2.f metros \n", atualJogador->comprimento);
            printf("4 - Velocidade: %2.f km/h \n", atualJogador->velocidade);
            printf("5 - Instinto assasino: %2.f \n", atualJogador->instintoAssasino);
            printf("Opcao: ");
            scanf("%d", &op);
            printf("Resultado: ");


        }
        else
        {
            srand ( time(NULL) );
            op = (rand() % 4) + 1;
        }
               
    switch (op)
                {
                case 1:
                    if (atualJogador->altura >= atualMaq->altura)
                    {
                        printf("A carta do jogador (%s) com %.2f ganhou da carta do bot (%s) com %.2f no atributo de altura\n", atualJogador->nome, atualJogador->altura, atualMaq->nome, atualMaq->altura);
                        inserir_fila(maoJogador, atualJogador);
                        inserir_fila(maoJogador, atualMaq);
                    }else if((atualMaq->altura >= atualJogador->altura))
                    {
                        printf("A carta do bot (%s) com %.2f ganhou da carta do jogador (%s) com %.2f no atributo de altura\n", atualMaq->nome, atualMaq->altura, atualJogador->nome, atualJogador->altura);
                        inserir_fila(maoMaquina, atualJogador);
                        inserir_fila(maoMaquina, atualMaq);
                    }
                    break;
                case 2:
                    if (atualJogador->peso >= atualMaq->peso)
                    {
                        printf("A carta do jogador (%s) com %.2f ganhou da carta do bot (%s) com %.2f no atributo de peso\n", atualJogador->nome, atualJogador->peso, atualMaq->nome, atualMaq->peso);
                        inserir_fila(maoJogador, atualJogador);
                        inserir_fila(maoJogador, atualMaq);    
                    }else if((atualMaq->peso >= atualJogador->peso))
                    {
                        printf("A carta do bot (%s) com %.2f ganhou da carta do jogador (%s) com %.2f no atributo de peso\n", atualMaq->nome, atualMaq->peso, atualJogador->nome, atualJogador->peso);
                        inserir_fila(maoMaquina, atualJogador);
                        inserir_fila(maoMaquina, atualMaq);
                    }
                    // volta para a funcao de jogar, passando por parametro as filas
                    break;
                case 3:
                    if (atualJogador->comprimento >= atualMaq->comprimento)
                    {
                        printf("A carta do jogador (%s) com %.2f ganhou da carta do bot (%s) com %.2f no atributo de comprimento\n", atualJogador->nome, atualJogador->comprimento, atualMaq->nome, atualMaq->comprimento);
                        inserir_fila(maoJogador, atualJogador);
                        inserir_fila(maoJogador, atualMaq);
                    }else if((atualMaq->comprimento >= atualJogador->comprimento))
                    {
                        printf("A carta do bot (%s) com %.2f ganhou da carta do jogador (%s) com %.2f no atributo de comprimento\n", atualMaq->nome, atualMaq->comprimento, atualJogador->nome, atualJogador->comprimento);
                        inserir_fila(maoMaquina, atualJogador);
                        inserir_fila(maoMaquina, atualMaq);
                    }
                    // volta para a funcao de jogar, passando por parametro as filas
                    break;
                case 4:
                    if (atualJogador->velocidade >= atualMaq->velocidade)
                    {
                        printf("A carta do jogador (%s) com %.2f ganhou da carta do bot (%s) com %.2f no atributo de velocidade\n", atualJogador->nome, atualJogador->velocidade, atualMaq->nome, atualMaq->velocidade);
                        inserir_fila(maoJogador, atualJogador);
                        inserir_fila(maoJogador, atualMaq);       
                    }else if((atualMaq->velocidade >= atualJogador->velocidade))
                    {
                        printf("A carta do bot (%s) com %.2f ganhou da carta do jogador (%s) com %.2f no atributo de velocidade\n", atualMaq->nome, atualMaq->velocidade, atualJogador->nome, atualJogador->velocidade);
                        inserir_fila(maoMaquina, atualJogador);
                        inserir_fila(maoMaquina, atualMaq);
                    }
                    // volta para a funcao de jogar, passando por parametro as filas
                    break;
                case 5:
                    if (atualJogador->instintoAssasino >= atualMaq->instintoAssasino)
                    {
                        printf("A carta do jogador (%s) com %.2f ganhou da carta do bot (%s) com %.2f no atributo de instinto assasino\n", atualJogador->nome, atualJogador->instintoAssasino, atualMaq->nome, atualMaq->instintoAssasino);
                        inserir_fila(maoJogador, atualJogador);
                        inserir_fila(maoJogador, atualMaq);       
                    }else if((atualMaq->instintoAssasino >= atualJogador->instintoAssasino))
                    {
                        printf("A carta do bot (%s) com %.2f ganhou da carta do jogador (%s) com %.2f no atributo de instinto assasino\n", atualMaq->nome, atualMaq->instintoAssasino, atualJogador->nome, atualJogador->instintoAssasino);
                        inserir_fila(maoJogador, atualJogador);
                        inserir_fila(maoJogador, atualMaq);
                    }
                    // volta para a funcao de jogar, passando por parametro as filas
                    break;
                default:
                    break;
                }
            printf("\n");
            numJogada++;
            qmJoga++;
        }
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

int salva_qtd_jogadas(int qtdJogadas, int ganhador) {
    FILE *f = fopen("totalJogadas.txt", "w");

  time_t now;
  time(&now);


    if (!f)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }
    
    /* print integers and floats */
    if(ganhador == 1)
    {
        fprintf(f, "Data: %s -- Ganhador: Player com %d", ctime(&now), qtdJogadas);
    }else
    {
        fprintf(f, "Data: %s -- Ganhador: Bot com %d", ctime(&now), qtdJogadas);
    }
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

    system("clear");
    // main nao definitiva, apenas para testes
    BARALHO baralho = criar_baralho();
    PTR_PILHA pilha = criar_pilha();

    PTR_FILA maoJogador = criar_fila();
    PTR_FILA maoMaquina = criar_fila();

    empilha_baralho(pilha, baralho);
    //mostra_cartas_baralho(baralho);
    // separa a pilha do baralho no meio e adiciona em duas filas, uma para o jogador e outra para a máquina
    adicionar_cartas_nas_maos(maoJogador, maoMaquina, pilha);

    
    int resultado = jogo(maoJogador, maoMaquina);
    if(resultado == 1){
        printf("O jogador ganhou!!\n");
        return 0;
    }
    printf("O bot ganhou!!\n");
    
    //printf("\n mao do jogador: \n");
    //mostra_mao(maoJogador);

    //printf("\n mao da maquina: \n");
    //mostra_mao(maoMaquina);

    // contar jogadas:
    //qtdJogadas++;
    //salva_qtd_jogadas();
    //recupera_qtd_jogadas();

}
