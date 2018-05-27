/*
 * Grafo.c
 *
 *  Created on: 14/11/2014
 *      Author: viniciusoliveira
 */
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <math.h>
#include "Graph.h"
#include "Spot.h"
#include "AdjList.h"
#include "PaintUtils.h"

//-----------------------------------------------------------------------------------------
void initializeGraph(Graph* graph){
	graph->map = (Spot*)malloc(sizeof(Spot));
	graph->size=0;
}

//-----------------------------------------------------------------------------------------
void insertVertex(Graph* graph, Spot spot){
	(graph->size)++;
	//aumenta a memoria a medida que seja necessario incluir vertices no grafo
	graph->map= (Spot*)realloc(graph->map, ((graph->size)*sizeof(Spot)));
	graph->map[(graph->size)-1] = spot;
}

//-----------------------------------------------------------------------------------------
//preenche as listas de adjacencia, gerando o grafo
void generateGraph(Graph* graph, double radius){
	int i=0;
	int j=0;

	for(i=0; i<graph->size;i++){
		for(j=0; j<graph->size; j++){
			if(radius <= sqrt(pow(((graph->map[i].x_coord) - (graph->map[j].x_coord) ),2) + pow(((graph->map[i].y_coord) - (graph->map[j].y_coord) ),2)) && (graph->map[i].ID != graph->map[j].ID)){
				insertAdj(&(graph->map[i].adj), j);
			}
		}
	}
}

//-----------------------------------------------------------------------------------------
//Imprime uma representacao do grafo na tela
//Funcao nao usada no TP.
void printGraph(Graph graph){
	int i=0;
	printf("Grafo criado: \n\n");

	for(i=0; i<graph.size; i++){
		printf("Vertice %d:\n", graph.map[i].ID);
		printAdjList(graph.map[i].adj);
		printf("\n\n");
	}
}

//-----------------------------------------------------------------------------------------
//colore o grafo usando o algoritmo especificado
int* paintGraph(Graph map, long int nAgents, int algorithm){

	switch(algorithm){

	case 1: //Forca Bruta
		return bruteForce(map, nAgents);


	case 2: //Paralelo
		return parallel(map, nAgents);


	case 3: //Heuristica
		return heuristic(map, nAgents);

	default:
		break;
	}

	return NULL;
}

//-----------------------------------------------------------------------------------------
void freeGraph(Graph* graph){
	int i=0;
	for(i=0; i<graph->size; i++){
		freeAdjList(&(graph->map[i].adj));
	}
	free(graph->map);

}







