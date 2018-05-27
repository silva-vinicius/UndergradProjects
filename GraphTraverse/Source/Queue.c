/*
 * Queue.c
 *
 *  Created on: 09/09/2014
 *      Author: viniciusoliveira
 */

#include <stdlib.h>
#include <stdio.h>
#include "Queue.h"

//Inicializa a fila especificada, alocando memoria para o seu apontador Primeiro
void setQueueEmpty(Queue *queue){

	//Aloca a memoria para a celula cabeca
	queue->first = (Pointer) malloc(sizeof(Cell));

	//O ultimo elemento da fila eh igual ao primeiro quando a mesma se encontra vazia
	queue->last = queue->first;

	//Quando a fila se encontra vazia, a celula-cabeca aponta para null;
	queue->first->next = NULL;

}

//-----------------------------------------------------------------------------------------
//Verifica se a fila especificada esta vazia ou nao
int isQueueEmpty(Queue queue){
	if(queue.first == queue.last){
		return 1;
	}
	return 0;
}

//-----------------------------------------------------------------------------------------
//Insere uma nova esquina no final da fila
void insertBack(Queue *queue, Corner corner){

	if(queue->last->next!=NULL){
		printf("ERROR - @Queue.c -L40");
	}
	//Aloca memoria para o elemento a ser acrescentado no final da fila
	queue->last->next = (Pointer) malloc(sizeof(Cell));

	//Avanca o ponteiro do ultimo elemento;
	queue->last = queue->last->next;

	//Atribui o elemento recebido ao ultimo elemento da fila
	queue->last->corner = corner;

	//Aponta o pointer prox do novo ultimo elemento para null
	queue->last->next = NULL;

	return;
}

//-----------------------------------------------------------------------------------------
//Retira o primeiro elemento da fila e o armazena na esquina especificada no segundo parametro
void removeFront(Queue *queue, Corner* corner){

	Pointer aux;

	corner->amntMinimalPaths=-1;
	corner->distance=-1;
	corner->isClosed=-1;

	if (isQueueEmpty(*queue)) {
		printf("ERROR: Remove failed - the queue is empty");
		return;
	}

	aux = queue->first->next;


	//-----------------------COPIA-----------------------
	(*corner) = (aux->corner);
	//---------------------------------------------------

	queue->first->next = aux->next;

	if(aux->next==NULL){
		queue->last = queue->first;
		queue->last->next=NULL;
	}

	free(aux);

	return;
}
//-----------------------------------------------------------------------------------------
/*
 * Verifica se um determinado elemento esta ou nao na lista
 */
int contains(Queue queue, Corner corner){

	Pointer aux;
	aux = queue.first->next;

	while(aux != NULL){
		if((aux->corner).i==corner.i && (aux->corner).j == corner.j){
			return 1;
		}
		aux = aux->next;
	}
	return 0;
}

//-----------------------------------------------------------------------------------------
//Imprime os elementos da fila especificada
//Funcao nao usada neste trabalho.
void printQueue(Queue queue){

	Pointer aux;
	aux = queue.first->next;

	while(aux != NULL){
		printf(" (%d,%d) ", aux->corner.i, aux->corner.j);
		aux = aux->next;
	}

	return;
}
//-----------------------------------------------------------------------------------------
//Libera a fila
void freeQueue(Queue* queue){
	free(queue->first);
	return;
}

