/*
 * Page.c
 *
 *  Created on: 08/09/2014
 *      Author: viniciusoliveira
 */
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "Page.h"


//*********************************FUNCOES INTERNAS AO TAD:*********************************

//carrega o valor especificado em uma pagina de memoria
void addByte(Page* page, long int byte){
	int i=0;
	while(i<page->length){
		i++;
	}
	if(i<=page->max_size){
		(page->page)[i]=byte;
		(page->length)++;
	}else{
		printf("\nPage violation: @addByte \nByte not included \n");
	}

	return;
}
//*****************************************************************************************

//Gera uma pagina em branco com o tamanho maximo especificado
Page createPage(int size){
	Page pagina;
	pagina.page = (long int*)malloc(size*sizeof(long int));
	pagina.max_size = size;
	pagina.length=0;
	pagina.pageID=-1; //Page ID = -1 significa que a pagina nao esta carregada
	pagina.accesses=0;
	return pagina;
}

//-----------------------------------------------------------------------------------------
//Dado um valor que a pagina deve conter, carrega a pagina com os demais
void loadPage(Page* page, int value){

	*page = createPage(page->max_size);
	page->accesses=1;

	int numPag;
	numPag = (value/page->max_size);

	page->pageID = numPag;

	long int includedByte = numPag*page->max_size;

	int i=0;

	for(i=0; i<page->max_size; i++){

		addByte (page,includedByte);
		includedByte++;
	}
	return;
}

//-----------------------------------------------------------------------------------------
//imprime uma pagina em stdout
//Funcao nao utilizada no trabalho
void printPage(Page page){
	if(page.page!=NULL){
		int i=0;
		printf("PageID: %d\n", page.pageID);
		printf("Page content:\n");
		for(i=0;i<page.length;i++){
			printf("%li\n", page.page[i]);
		}
		printf("\n\n");
	}else{
		printf("CANNOT PRINT NULL PAGE\n");
	}
}
