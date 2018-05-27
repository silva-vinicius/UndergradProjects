/*
 * Lista.c
 *
 *  Created on: 10/04/2014
 *      Author: viniciusoliveira
 */

#include <stdlib.h>
#include <stdio.h>
#include "Lista.h"

//Inicializa a lista especificada, alocando memoria para o seu apontador Primeiro
void fazListaVazia(Lista *list){

	//Aloca a memoria para a celula cabeca
	list->Primeiro = (Pointer) malloc(sizeof(Celula));

	//O ultimo elemento da lista eh igual ao primeiro quando a mesma se encontra vazia
	list->Ultimo = list->Primeiro;

	//Quando a lista se encontra vazia, a celula-cabeca aponta para null;
	list->Primeiro->Prox = NULL;
}
//-------------------------------------------------------

//Verifica se a lista especificada esta vazia ou nao
int vazia(Lista list){
	if(list.Primeiro == list.Ultimo){
		return 1;
	}
	return 0;
}
//-------------------------------------------------------

//Insere um novo elemento na lista, em ordem crescente
void insere(Celula cell, Lista *list){

	Pointer aux;
	aux=list->Primeiro;

	Pointer aux2;
	aux2= (Pointer)malloc(sizeof(Celula));

	while(aux!=NULL){
		if(aux->Prox!=NULL && aux->Prox->vertex.Chave > cell.vertex.Chave){
			aux2->vertex = cell.vertex;
			aux2->PesoAresta = cell.PesoAresta;
			aux2->Prox = aux->Prox;
			aux->Prox = aux2;


			return;
		}
		else{
			if(aux->Prox==NULL){ //Inserir no final
				//Aloca memoria para o elemento a ser acrescentado no final da lista
				list->Ultimo->Prox = (Pointer) malloc(sizeof(Celula));

				//Avanca o ponteiro do ultimo elemento;
				list->Ultimo = list->Ultimo->Prox;

				//Atribui o elemento recebido ao ultimo elemento da lista
				list->Ultimo->vertex = cell.vertex;
				list->Ultimo->PesoAresta = cell.PesoAresta;

				//Aponta o pointer prox do novo ultimo elemento para null
				list->Ultimo->Prox = NULL;

				return;
			}
		}
		aux = aux->Prox;
	}
}

//-------------------------------------------------------
//Retira o elemento apontado por p da lista e o armazena no vertice apontado por vertex
//Funcao nao utlizada neste trabalho
void retira(Pointer p, Lista *list, Vertice *vertex){

	Pointer aux;

	if (vazia(*list) || p == NULL || p->Prox == NULL) {
		printf("ERRO: Lista vazia ou posicao inexistente");
		return;
	}

	aux = p->Prox;
	*vertex = aux->vertex;
	p->Prox = aux->Prox;

	if(p->Prox==NULL){
		list->Ultimo = p;
	}
	free(aux);
	return;
}

//-------------------------------------------------------
//iImprime os elementos da fila especificada
void imprime(Lista list){

	Pointer aux;
	aux = list.Primeiro->Prox;

	while(aux != NULL){
		printf("%d\n", aux->vertex.Chave);
		aux = aux->Prox;
	}

	return;
}
