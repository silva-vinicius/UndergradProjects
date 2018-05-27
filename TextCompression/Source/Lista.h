/*
 * Lista.h
 *
 *  Created on: 10/04/2014
 *      Author: Vinicius Oliveira
 */

#ifndef LISTA_H_
#define LISTA_H_
#include "Arvore.h"

//-------------------------------------------------------

typedef struct Celula_Str *Pointer;
//-------------------------------------------------------

typedef struct Celula_Str{
	Node no;
	Pointer Prox;
}Celula;


typedef struct {
	Pointer Primeiro;
	Pointer Ultimo;
} Lista;

//-------------------------------------------------------
void fazListaVazia(Lista *list);
int listaVazia(Lista list);
void insere(Celula *cell, Lista *list);
Celula retiraUltimo(Lista *list);
void imprimeLista(Lista list);

//-------------------------------------------------------

#endif /* LISTA_H_ */


