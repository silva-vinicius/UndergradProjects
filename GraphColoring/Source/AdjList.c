/*
 * AdjList.c
 *
 *  Created on: 09/09/2014
 *      Author: viniciusoliveira
 */

#include <stdlib.h>
#include <stdio.h>
#include "AdjList.h"

//Inicializa a fila especificada, alocando memoria para o seu apontador Primeiro
void setAdjListEmpty(AdjList *adjList){

	//Aloca a memoria para a celula cabeca
	adjList->first = (Pointer) malloc(sizeof(Cell));

	//O ultimo elemento da fila eh igual ao primeiro quando a mesma se encontra vazia
	adjList->last = adjList->first;

	//Quando a fila se encontra vazia, a celula-cabeca aponta para null;
	adjList->first->next = NULL;

}

//-----------------------------------------------------------------------------------------
//Verifica se a fila especificada esta vazia ou nao
int isAdjListEmpty(AdjList adjList){
	if(adjList.first == adjList.last){
		return 1;
	}
	return 0;
}

//-----------------------------------------------------------------------------------------
//Insere uma nova esquina no final da fila
void insertAdj(AdjList *adjList, long int position){

	if(adjList->last->next!=NULL){
		printf("ERROR - @AdjList.c -L40");
	}
	//Aloca memoria para o elemento a ser acrescentado no final da fila
	adjList->last->next = (Pointer) malloc(sizeof(Cell));

	//Avanca o ponteiro do ultimo elemento;
	adjList->last = adjList->last->next;

	//Atribui o elemento recebido ao ultimo elemento da fila
	adjList->last->position = position;

	//Aponta o pointer prox do novo ultimo elemento para null
	adjList->last->next = NULL;

	return;
}

//-----------------------------------------------------------------------------------------
//Retira o primeiro elemento da fila e o armazena na inteiro especificado no segundo parametro
void removeAdj(AdjList *adjList, long int* position){

	Pointer aux;

	(*position)=-1;

	if (isAdjListEmpty(*adjList)) {
		printf("ERROR: Remove failed - the adjList is empty");
		return;
	}

	aux = adjList->first->next;


	//-----------------------COPIA-----------------------
	(*position) = (aux->position);
	//---------------------------------------------------

	adjList->first->next = aux->next;

	if(aux->next==NULL){
		adjList->last = adjList->first;
		adjList->last->next=NULL;
	}

	free(aux);

	return;
}

//-----------------------------------------------------------------------------------------
//Verifica se um determinado elemento esta ou nao na lista
int contains(AdjList adjList, long int position){

	Pointer aux;
	aux = adjList.first->next;

	while(aux != NULL){
		if((aux->position)==position){
			return 1;
		}
		aux = aux->next;
	}
	return 0;
}

//-----------------------------------------------------------------------------------------
//Imprime os elementos da fila especificada
//Funcao nao usada neste trabalho.
void printAdjList(AdjList adjList){
	printf("\nLista de Adjacencia:\n");
	Pointer aux;
	aux = adjList.first->next;

	while(aux != NULL){
		printf("%ld ", aux->position);
		aux = aux->next;
	}
	printf(" lista de adjacencia printada");

	return;
}

//-----------------------------------------------------------------------------------------
//Libera a fila
void freeAdjList(AdjList* adjList){
	long int aux=0;

	//Remover cada elemento
	while(!isAdjListEmpty(*adjList)){
		removeAdj(adjList, &aux);
	}
	//Remover celula cabeca
	free(adjList->first);
	return;
}

