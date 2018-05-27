/*
 * Lista.h
 *
 *  Created on: 10/04/2014
 *      Author: viniciusoliveira
 */

#ifndef LISTA_H_
#define LISTA_H_


typedef struct {
	int Chave;
} Vertice;
//-------------------------------------------------------

typedef struct Celula_str *Pointer;
//-------------------------------------------------------

typedef struct Celula_str {
	Vertice vertex;
	int PesoAresta;
	Pointer Prox;
} Celula;
//-------------------------------------------------------

typedef struct {
	Pointer Primeiro;
	Pointer Ultimo;
} Lista;

//-------------------------------------------------------
void fazListaVazia(Lista *list);
int vazia(Lista list);
void insere(Celula cell, Lista *list);
void retira(Pointer p, Lista *list, Vertice *vertex);
void imprime(Lista list);

//-------------------------------------------------------

#endif /* LISTA_H_ */


