/*
 * FifoMemory.c
 *
 *  Created on: 10/09/2014
 *      Author: viniciusoliveira
 */

#include <stdio.h>
#include <stdlib.h>
#include "FifoMemory.h"

//*********************************FUNCOES INTERNAS AO TAD:*********************************
//Insere a pagina especificada no final da fila;
void insertFifoPage(FifoMemory* fifo, Page page){
	insertBack(&(fifo->list), page);
	(fifo->length)++;
	return;
}

//-----------------------------------------------------------------------------------------
//Remove a primeira pagina da fila;
void removeFifoPage(FifoMemory* fifo, Page page){
	removeFront(&(fifo->list), &page);
	(fifo->length)--;
	return;
}
//*****************************************************************************************

//-----------------------------------------------------------------------------------------
/*
 * incializa um "objeto" do tipo FifoMemory,
 * especificando o tamanho maximo da memoria e o tamanho da pagina;
 */
void createFifoMemory(FifoMemory* fifo, int memSize, int pageSize){
	setListEmpty(&(fifo->list));
	fifo->maxPages = memSize/pageSize;
	fifo->length=0;
	fifo->pageFaults=0;
	return;
}

//-----------------------------------------------------------------------------------------
//libera o espaco usado para simular a memoria;
void freeFifoMemory(FifoMemory* fifo){
	//Cria uma pagina auxiliar com tamanho minimo para realizar exclusoes na fila
	Page aux;
	aux = createPage(1);
	while(fifo->length!=0){
		removeFifoPage(fifo, aux);
	}
}

/*
 * Recebe e processa as requisicoes de acesso a memoria virtual segundo a politica FIFO.
 * Retorna um array de inteiros contendo as distancias entre as paginas solicitadas;
 */
int* processFifoInstructions(FifoMemory* fifo, int* instructions, int insLength, int pageSize){
	int i=0;
	Page aux;
	aux = createPage(pageSize);

	int* distances;
	distances = (int*)malloc((insLength-1)*sizeof(int));


	for(i=0; i<insLength; i++){

		if(i!=0){
			distances[i-1] = (instructions[i]/ pageSize)-fifo->currentPage;
		}

		fifo->currentPage=(instructions[i]/ pageSize);

		if(!pageExists(fifo->list, (instructions[i]/pageSize))){

			(fifo->pageFaults)++;

			if(fifo->length < fifo->maxPages){
				loadPage(&aux, instructions[i]);
				insertFifoPage(fifo, aux);
			}else{
				removeFifoPage(fifo, aux);
				loadPage(&aux, instructions[i]);
				insertFifoPage(fifo, aux);
			}
		}
	}
	return distances;
}
