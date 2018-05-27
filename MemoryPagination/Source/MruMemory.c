/*
 * MruMemory.c
 *
 *  Created on: 14/09/2014
 *      Author: viniciusoliveira
 */
#include <stdio.h>
#include <stdlib.h>
#include "MruMemory.h"


//*********************************FUNCOES INTERNAS AO TAD:*********************************
//Insere a pagina especificada no comeco da fila
void insertMruPage(MruMemory* mru, Page page){
	insertFront(&(mru->list), page);
	(mru->length)++;
	return;
}

//-----------------------------------------------------------------------------------------
//Remove a primeira pagina da fila
void removeMruPage(MruMemory* mru, Page page){
	removeFront(&(mru->list), &page);
	(mru->length)--;
	return;
}
//*****************************************************************************************

/*
 * incializa um "objeto" do tipo MruMemory,
 * especificando o tamanho maximo da memoria e o tamanho da pagina;
 */
void createMruMemory(MruMemory* mru, int memSize, int pageSize){
	setListEmpty(&(mru->list));
	mru->maxPages = memSize/pageSize;
	mru->length=0;
	mru->pageFaults=0;
	return;
}

//-----------------------------------------------------------------------------------------
//libera o espaco usado para simular a memoria;
void freeMruMemory(MruMemory* mru){
	//Cria uma pagina auxiliar com tamanho minimo para realizar exclusoes na fila
	Page aux;
	aux = createPage(1);
	while(mru->length!=0){
		removeMruPage(mru, aux);
	}
}

//-----------------------------------------------------------------------------------------
//Processa as requisoes de acesso a memoria virtual segundo a politica MRU.
void processMruInstructions(MruMemory* mru, int* instructions, int insLength, int pageSize){
	int i=0;
	Page aux;
	aux = createPage(pageSize);

	for(i=0; i<insLength; i++){

		if(!pageExists(mru->list, (instructions[i]/pageSize))){

			(mru->pageFaults)++;

			if(mru->length < mru->maxPages){
				loadPage(&aux, instructions[i]);
				insertMruPage(mru, aux);
			}else{
				removeMruPage(mru, aux);
				loadPage(&aux, instructions[i]);
				insertMruPage(mru, aux);
			}
		}else{
			//A pagina ja se encontra em memoria. Move-la para o inicio da fila.
			if(mru->length!=1){
				loadPage(&aux, instructions[i]);
				moveToFront(&(mru->list), aux);
			}
		}
	}
	return;
}
