/*
 * arvore.c
 *
 *  Created on: 23/05/2014
 *      Author: Vinicius Oliveira
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Lista.h"
#include "Arvore.h"
#define DISTINCT_CHARS 53


//=============================FUNCOES INTERNAS DO TAD=============================
//Cria um no interno tendo como filho da esquerda filhoEsq e filho da direita filhoDir
//O Codigo do no interno e igual a soma dos codigos de seus filhos
Node criaNoInt(Node* filhoEsq, Node* filhoDir ){
	Node nointerno;
	nointerno.caracter = '~';

	Node* esq;
	esq = (Node*) malloc(sizeof(Node));
	*esq = *filhoEsq;

	Node* dir;
	dir = (Node*) malloc(sizeof(Node));
	*dir = *filhoDir;

	nointerno.esquerda = esq;
	nointerno.direita = dir;
	nointerno.codigo = filhoEsq->codigo + filhoDir->codigo;
	nointerno.byte = "\0";

	return nointerno;
}

//-------------------------------------------------------
//Atribui o codigo binario para todas os nos da arvore
void preencheBytes(Arvore tree){

	if(tree==NULL){
		return;
	}

	if(tree->esquerda !=NULL && tree->direita!=NULL){

		tree->esquerda->byte = (char*)malloc((strlen(tree->byte)*sizeof(char))+1);
		tree->direita->byte = (char*)malloc((strlen(tree->byte)*sizeof(char))+1);
		strcpy(tree->esquerda->byte, tree->byte);
		strcat(tree->esquerda->byte, "0");
		strcpy(tree->direita->byte, tree->byte);
		strcat(tree->direita->byte, "1");
	}
	preencheBytes(tree->esquerda);
	preencheBytes(tree->direita);
}


//-------------------------------------------------------
//Pesquisa a posicao de uma determinada letra na tabela de frequencia. Retorna -1
//caso nao seja encontrada.
int posicao(Node* array, char letra){
	int i=0;
	for(i=0; i<=DISTINCT_CHARS; i++){
		if(array[i].caracter==letra){
			return i;
		}
	}
	//retorna -1 caso a letra nao seja encontrada
	return -1;
}

//-------------------------------------------------------
//converte uma cadeia binaria para um numero inteiro.
int byteToInt(char* byte){
	int num=0;
	int i=0;
	for(i=0; i<8; i++){
		if(byte[7-i]=='1'){
			num += pow(2,i);
		}
	}
	return num;
}
//===================================================================================

//Aloca memoria para o no raiz da arvore e o inicializa com atributos nulos
void fazArvoreVazia(Arvore *tree){

	*tree = (Arvore)malloc(sizeof(Arvore));
	(*tree)->caracter='\0';
	(*tree)->codigo=0;
	(*tree)->byte = (char*)malloc(2*sizeof(char));
	(*tree)->direita=NULL;
	(*tree)->esquerda=NULL;

	return;
}

//-------------------------------------------------------
//Gera a arvore propriamente ditas a partir de um array de nos folhas
Arvore construir(char *texto, Node** tabelaFreq){

	int tamanho = strlen(texto);
	*tabelaFreq = (Node*)malloc(53*(sizeof(Node)));

	int i=0;
	int j=0;
	int pos=0;
	Node auxiliar;

	for(i=0; i<tamanho; i++){
		pos = posicao(*tabelaFreq, texto[i]);
		//se a letra atual ainda nao existir no array, acrescenta-la
		if(pos==-1 && texto[i]!='\n'){
			auxiliar.caracter=texto[i];
			auxiliar.codigo=1;
			auxiliar.direita=NULL;
			auxiliar.esquerda=NULL;
			(*tabelaFreq)[j] = auxiliar;
			j++;
		}else{ //se a letra atual ja existir no array, aumentar a frequencia da mesma.
			(*tabelaFreq)[pos].codigo++;
		}
	}

	Arvore tree;
	fazArvoreVazia(&tree);


	Lista leaves;
	fazListaVazia(&leaves);


	Celula aux;
	Celula aux2;
	Celula aux3;

	for(i=0; i<j; i++){
		aux.no = (*tabelaFreq)[i];
		insere(&aux, &leaves);
	}

	while(i>1){

		aux = retiraUltimo(&leaves);
		if(aux.no.codigo==-1){
			printf("ERRO\n");
		}

		aux2 = retiraUltimo(&leaves);
		if(aux2.no.codigo==-1){
			printf("ERRO\n");
		}
		aux3.no=criaNoInt(&aux2.no, &aux.no);
		insere(&aux3, &leaves);
		i--;
	}
	tree=&(leaves.Primeiro->Prox->no);
	preencheBytes(tree);

	return tree;
}

//-------------------------------------------------------
//Faz a pesquisa na arvore pelo codigo binario de uma letra especificada
char* getBytes(char letra, Arvore tree){

	char* retorno=NULL;

	if (tree == NULL){
		return "NULO";
	}
	if(tree->caracter == letra){
		return tree->byte;
	}
	if(tree->esquerda !=NULL){
		retorno = getBytes(letra, tree->esquerda);

		if(strcmp(retorno, "NULO") == 0){
			if(tree->direita!=NULL){
				return getBytes(letra, tree->direita);
			}
		}else{
			return retorno;
		}
	}
	return "NULO";
}

//-------------------------------------------------------
//imprime em stdout, a string codificada
void imprimeBytes(Node* tabelaFreq, Arvore tree,  char* texto){

	int i=0;
	for(i=0; i<=DISTINCT_CHARS; i++){
		tabelaFreq[i].byte = getBytes(tabelaFreq[i].caracter, tree);
	}
	int index;
	for(i=0; i<(strlen(texto)-1); i++){
		index = posicao(tabelaFreq, texto[i]);
		printf("%s",tabelaFreq[index].byte);
	}
}
//-------------------------------------------------------
//imprime em stdout, a string compactada
void imprimeCompactado(Node* tabelaFreq, Arvore tree,  char* texto){

	int i=0;
	for(i=0; i<=DISTINCT_CHARS; i++){
		tabelaFreq[i].byte = getBytes(tabelaFreq[i].caracter, tree);
	}

	int index;
	int stringlenght=0;

	for(i=0; i<(strlen(texto)-1); i++){
		index = posicao(tabelaFreq, texto[i]);
		stringlenght += (strlen(tabelaFreq[index].byte));
	}
	stringlenght++; //espaco extra para o \0

	char* completestring;
	completestring = (char*)malloc(stringlenght*sizeof(char));
	strcpy(completestring, "\0");

	for(i=0; i<(strlen(texto)-1); i++){
		index = posicao(tabelaFreq, texto[i]);
		strcat(completestring, tabelaFreq[index].byte);
	}

	char* byte=(char*)malloc(9*sizeof(char)); //espaco extra para o \0
	int j=0;
	int convertido=0;

	for(i=0; i<(stringlenght-1); i++){
		for(j=0; j<8; j++){
			if(i<stringlenght){
				byte[j] = completestring[i];
				i++;
			}
			if(i>=stringlenght){
				byte[j]='1';
			}
		}
		byte[9] = '\0';
		i--;
		convertido=byteToInt(byte);
		printf("%c", convertido);
	}
}

//-------------------------------------------------------

