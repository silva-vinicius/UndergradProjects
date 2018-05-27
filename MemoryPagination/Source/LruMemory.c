/*
 * LruMemory.c
 *
 *  Created on: 13/09/2014
 *      Author: viniciusoliveira
 */
#include "LruMemory.h"
#include <stdio.h>
#include <stdlib.h>


//*********************************FUNCOES INTERNAS AO TAD:*********************************
//Insere a pagina especificada no final da fila
void insertLruPage(LruMemory* lru, Page page){
	insertBack(&(lru->list), page);
	(lru->length)++;
	//printf("inseriu neh? %d\n", page.pageID);
	return;
}

//-----------------------------------------------------------------------------------------
//Remove a primeira pagina da fila
void removeLruPage(LruMemory* lru, Page page){
	removeFront(&(lru->list), &page);
	(lru->length)--;
	//printf("removeu a primeira pagina da fila, que eh: %d\n", page.pageID);
	return;
}
//*****************************************************************************************

/*
 * incializa um "objeto" do tipo LruMemory,
 * especificando o tamanho maximo da memoria e o tamanho da pagina;
 */
void createLruMemory(LruMemory* lru, int memSize, int pageSize){
	setListEmpty(&(lru->list));
	lru->maxPages = memSize/pageSize;
	lru->length=0;
	lru->pageFaults=0;
	////printf("Criou uma LRU Memory\n");
	return;
}

//-----------------------------------------------------------------------------------------
//libera o espaco usado para simular a memoria;
void freeLruMemory(LruMemory* lru){
	//Cria uma pagina auxiliar com tamanho minimo para realizar exclusoes na fila
	Page aux;
	aux = createPage(1);
	while(lru->length!=0){
		removeLruPage(lru, aux);
	}
	////printf("Espaco LRU liberado\n");
	return;

}

//-----------------------------------------------------------------------------------------
/*Processa as requisoes de acesso a memoria virtual segundo a politica LRU.
 *retorna um array de inteiros contendo as distancias de pilha;
 */
int* processLruInstructions(LruMemory* lru, int* instructions, int insLength, int pageSize){
	int i=0;
	Page aux;
	aux = createPage(pageSize);
	int *stackDistance;

	////printf("Vou alocar stackDistance\n");
	stackDistance = (int*)malloc(insLength*sizeof(int));
	//printf("aloquei stack distance\n");

	for(i=0; i<insLength; i++){
		//printf("------------------------------------------------------------------\n");

		if(!pageExists(lru->list, (instructions[i]/pageSize))){
			stackDistance[i]=-1;

			//printf("Deu pagefault no acesso: %d\n", (instructions[i]/pageSize));
			(lru->pageFaults)++;

			if(lru->length < lru->maxPages){
				loadPage(&aux, instructions[i]);
				//printf("Tentaremos inserir pagina %d\n", aux.pageID);
				insertLruPage(lru, aux);
				//printf("Inserimos?\n");
			}else{
				//printf("Tentaremos remover a primeira pagina\n");
				removeLruPage(lru, aux);
				//printf("removemos?\n");
				loadPage(&aux, instructions[i]);
				//printf("carregamos pagina %d\n", aux.pageID);
				insertLruPage(lru, aux);
				//printf("inserimos?\n");
			}
		}else{
			//Pagina requisitada ja esta em memoria
			//Mover a pagina para o final da fila
			//printf("Pagina %d ja em memoria, move-la para o final\n", (instructions[i]/pageSize));
			if(lru->length!=1){

				loadPage(&aux, instructions[i]);
				//printf("Carregou pagina com ID %d \n", aux.pageID);
				stackDistance[i] = (lru->length - moveToLast(&(lru->list) ,aux)-1);
			}
		}

		//printf("------------------------------------------------------------------\n");
	}
	return stackDistance;
}
