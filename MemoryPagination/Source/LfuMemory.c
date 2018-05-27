/*
 * LfuMemory.c
 *
 *  Created on: 14/09/2014
 *      Author: viniciusoliveira
 */
#include "LfuMemory.h"
#include "Page.h"
#include <stdio.h>
#include <stdlib.h>


//*********************************FUNCOES INTERNAS AO TAD:*********************************
//Insere a pagina especificada no final da lista
void insertLfuPage(LfuMemory* lfu, Page page){
	insertBack(&(lfu->list), page);
	(lfu->length)++;
	return;
}

//-----------------------------------------------------------------------------------------
// Remove a pagina especificada da lista
void removeLfuPage(LfuMemory* lfu, Pointer pointer){
	removeArbitrary(&(lfu->list), pointer);
	(lfu->length)--;
	return;
}

//-----------------------------------------------------------------------------------------

//*****************************************************************************************

/*
 * incializa um "objeto" do tipo LfuMemory,
 * especificando o tamanho maximo da memoria e o tamanho da pagina;
 */
void createLfuMemory(LfuMemory* lfu, int memSize, int pageSize){
	lfu->length=0;
	lfu->maxPages=memSize/pageSize;
	lfu->pageFaults=0;
	setListEmpty(&(lfu->list));
	return;
}

//-----------------------------------------------------------------------------------------
//libera o espaco usado para simular a memoria;
void freeLfuMemory(LfuMemory* lfu){
	Page aux;
	aux=createPage(1);
	while(lfu->length>0){
		removeFront(&(lfu->list), &aux);
		lfu->length--;
	}
	return;
}

//-----------------------------------------------------------------------------------------
//Processa as requisoes de acesso a memoria virtual segundo a politica LFU;
void processLfuInstructions(LfuMemory* lfu, int* instructions, int insLength, int pageSize){
	int i=0;
	Pointer leastUsed;
	Page aux;
	aux = createPage(pageSize);

	for(i=0; i<insLength; i++){

		if(!pageExists(lfu->list, (instructions[i]/pageSize))){

			(lfu->pageFaults)++;

			if(lfu->length < lfu->maxPages){
				loadPage(&aux, instructions[i]);
				insertLfuPage(lfu, aux);
			}else{
				leastUsed = searchLeastFrequency(lfu->list);
				removeLfuPage(lfu, leastUsed);
				loadPage(&aux, instructions[i]);
				insertLfuPage(lfu, aux);
			}
		}else{
			//se a pagina ja esta em memoria, incrementar seu numero de acessos
			incrementAccesses(&(lfu->list), instructions[i]/pageSize );
		}
	}
}

