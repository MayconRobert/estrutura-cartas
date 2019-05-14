/*
	TA FALTANDO COISA PRA UM SATANAS, NAO ME ODEIE, PAPAI DO CEU TE AMA S2
	USAR A A RAND DO COMPILADOR E FAZER O CAST PARA FLOAT PARA RETORNAR O VALOR RANDOM PARA ATRIBUIR AO VALOR DA CARTA!
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


#define MAX_CARTAS 32

typedef struct _animal {
    int id;
     char[32][2] classe;
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
	char nomeAnimal[] = ["leao", "pato", "gato", "rato"];
	char classeAnimal[] = ["A1", "A2", "A3", "B1"];
    for(i=0; i<MAX_CARTAS; i++){
        baralho.animal[i].altura = random();
        baralho.animal[i].comprimento = random();
        baralho.animal[i].id = i;
        baralho.animal[i].instintoAssasino = random();
        baralho.animal[i].peso = random();
        baralho.animal[i].velocidade = random();
		baralho.animal[i] = nomeAnimal[i];
		//baralho.animal[i].classeAnimal=[i][2] = classeAnimal[i];
		strcpy(baralho.animal[i].classeAnimal[i][2], classeAnimal[i]);
    }
    return baralho;
}


BARALHO randomiza_baralho(BARALHO baralho){
	/*  Fazer a funcao que troca dois caras de lugar e tirar os valores do vetor */
	int numeros[MAX_CARTAS];
	for(int i=0; i<MAX_CARTAS; i++){
		numeros[i] = i;
	}
	int nuemro1;
	int numero2;
	ANIMAL temp;
	/*  Funcao que tira na sorte 2 numeros entre 0 e 31  */
	numero1 = 2;
	numero2 = 6;
	temp = baralho[numero1];
	baralho[numero1] = baralho[numero2];
	baralho[numero2] = temp;
	
	/*  Dentro do vetor numeros, retirar os dois valores e rodar de novo, ate que todos os numeros acabem  */
	return baralho;
}


void cria_fila_de_cartas(BARALHO baralho){
	int i=0;
	/*  Rodar um for ate 0,15 para a primeira mao, assim, atribuindo cada valor com a filha mao1  */
	fila mao1[i] = baralho[i];
	
	/*  Rodar um for ate 16,32 para a primeira mao, assim, atribuindo cada valor com a filha mao2  */
	fila mao2[i] = baralho[i];
	
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
