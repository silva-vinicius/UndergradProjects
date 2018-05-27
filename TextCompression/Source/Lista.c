/*
 * Lista.c
 *
 *  Created on: 10/04/2014
 *      Author: Vinicius Oliveira
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
	list->Ultimo->Prox = NULL;
}
//-------------------------------------------------------

//Verifica se a lista especificada esta vazia ou nao
int listaVazia(Lista list){
	if(list.Primeiro == list.Ultimo){
		return 1;
	}
	return 0;
}
//-------------------------------------------------------
//Insere um elemento na lista
void insere(Celula *cell, Lista *list){
	Pointer aux = list->Primeiro;

	Pointer aux2;
	aux2 = (Pointer)malloc(sizeof(Celula));

	while(aux!=NULL){

		if(aux->Prox!=NULL && ((aux->Prox->no.codigo==cell->no.codigo && aux->Prox->no.caracter > cell->no.caracter) || (aux->Prox->no.codigo < cell->no.codigo) || (aux->Prox->no.caracter=='~'))){
			aux2->no = cell->no;
			aux2->Prox = aux->Prox;
			aux->Prox = aux2;
			return;
		}else{
			if(aux==list->Ultimo){
				aux2->no = cell->no;
				aux->Prox = aux2;
				aux2->Prox = NULL;
				list->Ultimo = aux2;
				return;
			}
		}
		aux = aux->Prox;
	}
}

//-------------------------------------------------------
//Retira o ultimo elemento da lista e o retorna
Celula retiraUltimo(Lista *list){

	Pointer aux;
	aux=list->Primeiro;

	Celula removida;
	removida.no.codigo=-1;
	removida.no.caracter='\0';


	while(aux!=NULL){

		if(aux->Prox!=NULL && aux->Prox == list->Ultimo){
			removida.no.caracter = aux->Prox->no.caracter;
			removida.no.codigo = aux->Prox->no.codigo;
			removida.no.direita = aux->Prox->no.direita;
			removida.no.esquerda = aux->Prox->no.esquerda;

			free(aux->Prox);

			list->Ultimo = aux;
			list->Ultimo->Prox = NULL;

			return removida;
		}
		aux = aux->Prox;
	}
	return removida;
}

//-------------------------------------------------------
//Imprime os elementos da lista especificada
void imprimeLista(Lista list){

	Pointer aux;
	aux = list.Primeiro->Prox;

	while(aux != NULL){
		if(aux->no.caracter == '~'){
			printf("%c-%d ([%c / %d] + [%c / %d])\n",aux->no.caracter, aux->no.codigo, aux->no.esquerda->caracter, aux->no.esquerda->codigo, aux->no.direita->caracter, aux->no.direita->codigo);
		}else{

			printf("%c-%d (NULL + NULL)\n",aux->no.caracter, aux->no.codigo);
		}

		aux = aux->Prox;
	}

	return;
}

