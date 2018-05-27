/*
 ============================================================================
 Name        : TP1.c
 Author      : Vinicius de Oliveira
 Version     :
 Copyright   : Your copyright notice
 Description : TP1 - funcao main
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

int main(void) {

	//Cria um grafo e faz a leitura da entrada
	Grafo graph;
    leGrafo(&graph);

    //Cria um grafo representando a arvore minima
	Grafo minimalTree;
	arvoreMinima(graph, &minimalTree);

	imprimeOrdenado(minimalTree);

	return EXIT_SUCCESS;
}
