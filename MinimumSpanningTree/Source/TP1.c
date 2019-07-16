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

	//Creates a graph and reads the input
	Grafo graph;
        leGrafo(&graph);

    	//Creates a graph representing the minimum spanning tree
	Grafo minimalTree;
	arvoreMinima(graph, &minimalTree);

	imprimeOrdenado(minimalTree);

	return EXIT_SUCCESS;
}
