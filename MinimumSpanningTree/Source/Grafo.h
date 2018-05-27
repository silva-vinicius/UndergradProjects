/*
 * Grafo.h
 *
 *  Created on: 11/04/2014
 *      Author: Vinicius Oliveira
 */

#ifndef GRAFO_H_
#define GRAFO_H_

#include "Lista.h"


typedef struct {
	Lista *Adj;
	int NumVertices;
	int NumArestas;
} Grafo;

void leGrafo(Grafo *graph);
void fazGrafoVazio(Grafo *graph, int NumVertices, int NumArestas);
void insereAresta(Vertice *v1, Vertice *v2, int Peso, Grafo *graph);
int existeAresta(Vertice v1, Vertice v2, Grafo graph);
int listaAdjVazia(Vertice v1, Grafo graph);
Pointer primeiroListaAdj(Vertice v1, Grafo graph);
void retiraAresta(Vertice v1, Vertice v2, int Peso, Grafo *graph);
void arvoreMinima(Grafo source, Grafo *destination);
void liberaGrafo(Grafo *graph);
void imprimeOrdenado(Grafo graph);
void imprimeGrafo(Grafo graph);



#endif /* GRAFO_H_ */
