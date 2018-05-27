/*
 * List.c
 *
 *  Created on: 09/09/2014
 *      Author: viniciusoliveira
 */

#include <stdlib.h>
#include <stdio.h>
#include "List.h"

//Inicializa a lista especificada, alocando memoria para o seu apontador Primeiro
void setListEmpty(List *list){

	//Aloca a memoria para a celula cabeca
	list->first = (Pointer) malloc(sizeof(ListPageFrame));

	//O ultimo elemento da lista eh igual ao primeiro quando a mesma se encontra vazia
	list->last = list->first;

	//Quando a lista se encontra vazia, a celula-cabeca aponta para null;
	list->first->next = NULL;

}

//-----------------------------------------------------------------------------------------
//Verifica se a lista especificada esta vazia ou nao
int isListEmpty(List list){
	if(list.first == list.last){
		return 1;
	}
	return 0;
}

//-----------------------------------------------------------------------------------------
//Pesquisa na lista se uma pagina existe ou nao.
int pageExists(List list, int pageNumber){

	Pointer aux;
	aux = list.first->next;

	while(aux != NULL){
		if((aux->page).pageID==pageNumber){
			return 1;
		}
		aux = aux->next;
	}
	return 0;
}

//-----------------------------------------------------------------------------------------
//Insere uma nova pagina na lista
void insertBack(List *list, Page page){

	if(list->last->next!=NULL){
		printf("ERROR - @List.c -L56");
	}
	//Aloca memoria para o elemento a ser acrescentado no final da lista
	list->last->next = (Pointer) malloc(sizeof(ListPageFrame));

	//Avanca o ponteiro do ultimo elemento;
	list->last = list->last->next;

	//Atribui o elemento recebido ao ultimo elemento da lista
	list->last->page = page;

	//Aponta o pointer prox do novo ultimo elemento para null
	list->last->next = NULL;

	return;

}

//-----------------------------------------------------------------------------------------
//Retira o primeiro elemento da lista e o armazena na pagina especificada no segundo parametro
void removeFront(List *list, Page *page){

	Pointer aux;

	if (isListEmpty(*list)) {
		printf("ERROR: Remove failed - the list is empty");
		return;
	}

	aux = list->first->next;
	*page = aux->page;
	list->first->next = aux->next;

	if(aux->next==NULL){
		list->last = list->first;
		list->last->next=NULL;
	}

	free(aux);
	return;
}

//-----------------------------------------------------------------------------------------
/* recebe um apontador indicando o elemento anterior ao que deve ser removido
 * e faz a remocao do elemento apropriado;
 */
void removeArbitrary(List* list, Pointer pointer){
	Pointer aux;
	aux = pointer->next;
	if(aux==list->last){
		pointer->next=NULL;
		list->last = pointer;
		free(aux);
		return;
	}
	pointer->next = aux->next;
	free(aux);
	return;
}

//-----------------------------------------------------------------------------------------
/*
 *Pesquisa um elemento na lista e o coloca no final.
 *retorna quantos nodes foram pesquisados ate que se encontre o elemento especificado
 */
int moveToLast(List *list, Page page){
	//printf("****************MOVE TO LAST***************************\n");
	//printf("A pagina com ID %d deve ser movida para o final\n", page.pageID);
	int searchedNodes=0;

	Pointer aux;
	aux = list->first;

	if(aux==NULL || aux->next == NULL){
		//printf("aux ou aux->next eh null, vai dar treta\n");
	}
	//printf("LISTA: \n");
	//printList(*list);
	//printf("----------------------\n");
	////printf("entrarei no while\n");
	while(aux->next->page.pageID != page.pageID){
		//printf("entramos no while\n");
		searchedNodes++;
		aux = aux->next;
	}
	////printf("sai do while ileso\n");

	//se o elemento a ser colocado no final ja esta no final, nao troca-lo.
	if(aux->next->next==NULL){
		return searchedNodes;
	}
	//printf("aux->next->next nao eh NULL\n");
	Pointer aux2;
	aux2 = aux->next;

	aux->next = aux->next->next;
	//printf("vou dar free\n");
	free(aux2);
	insertBack(list, page);
	//printf("insertBack com sucesso\n");
	//printf("*******************************************************\n");
	return searchedNodes;
}

//-----------------------------------------------------------------------------------------
//Pesquisa um elemento na lista e o move para a primeira posicao.
//Usado na implementacao MRU.
void moveToFront(List* list, Page page){

	Pointer aux;
	aux = list->first;


	while(aux->next->page.pageID != page.pageID){
		aux = aux->next;
	}

	//se o elemento a ser colocado no comeco ja esta no comeco, nao troca-lo.
	if(aux->next->next==list->first->next){
		return;
	}

	Pointer aux2;
	aux2 = aux->next;

	aux->next = aux->next->next;
	free(aux2);
	insertFront(list, page);

	return;

}
//-----------------------------------------------------------------------------------------
//insere um elemento no comeco da lista.
//Usado na implementacao MRU
void insertFront(List* list, Page page){
	Pointer aux;
	aux = list->first->next;

	/*se aux e nulo, significa que a lista esta vazia, ou seja, a insercao no final
	 *eh permitida.
	*/
	if(aux==NULL){
		insertBack(list, page);
	}else{
		list->first->next = (Pointer)malloc(sizeof(ListPageFrame));
		list->first->next->page=page;
		list->first->next->next = aux;
	}
	return;
}

//-----------------------------------------------------------------------------------------
//Imprime os elementos da lista especificada
//Funcao nao usada neste trabalho.
void printList(List list){

	Pointer aux;
	aux = list.first->next;

	while(aux != NULL){
		printPage(aux->page);
		aux = aux->next;
	}

	return;
}

//-----------------------------------------------------------------------------------------
//retorna um ponteiro indicando o elemento anterior ao de menor frequencia
Pointer searchLeastFrequency(List list){
	Pointer p;

	if(isListEmpty(list)){
		return NULL;
	}

	int leastFrequency;
	leastFrequency = list.first->next->page.accesses;

	Pointer aux;
	aux=list.first;

	while(aux!=NULL){
		if(aux->next!=NULL && aux->next->page.accesses<=leastFrequency){
			p=aux;
			leastFrequency = p->next->page.accesses;
		}
		aux = aux->next;
	}
	return p;
}
//-----------------------------------------------------------------------------------------
//incrementa o numero de acesso de uma determinada pagina na lista
void incrementAccesses(List* list, int pageID){
	Pointer aux;
	aux = list->first->next;

	while(aux != NULL){
		if(aux->page.pageID==pageID){
			aux->page.accesses++;
			return;
		}
		aux = aux->next;
	}
	return;

}
