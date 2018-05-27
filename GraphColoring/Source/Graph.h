/*
 * Map.h
 *
 *  Created on: 14/11/2014
 *      Author: viniciusoliveira
 */

#ifndef MAP_H_
#define MAP_H_
#include "Spot.h"

typedef struct Graph{
	Spot* map;
	long int size; //numero de vertices no grafo
}Graph;

//-----------------------------------------------------------------------------------------
void initializeGraph(Graph*);
void insertVertex(Graph*, Spot);
void generateGraph(Graph* map,double radius);
void printGraph(Graph);
int* paintGraph(Graph,long int, int);
void freeGraph(Graph*);

//-----------------------------------------------------------------------------------------

#endif /* MAP_H_ */
