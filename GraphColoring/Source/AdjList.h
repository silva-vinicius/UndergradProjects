/*
 * List.h
 *
 *  Created on: 09/09/2014
 *      Author: viniciusoliveira
 */

#ifndef QUEUE_H_
#define QUEUE_H_


//-----------------------------------------------------------------------------------------
typedef struct Cell_str *Pointer;

//-----------------------------------------------------------------------------------------
typedef struct Cell_str {
	long int position;
	Pointer next;
} Cell;

//-----------------------------------------------------------------------------------------
typedef struct AdjList {
	Pointer first;
	Pointer last;
} AdjList;


//-----------------------------------------------------------------------------------------
void setAdjListEmpty(AdjList*);
int isAdjListEmpty(AdjList);
void insertAdj(AdjList*, long int);
void removeAdj(AdjList*, long int*);
int contains(AdjList, long int);
void printAdjList(AdjList);
void freeAdjList(AdjList*);

#endif /* FILA_H_ */
