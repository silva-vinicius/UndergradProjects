/*
 * List.h
 *
 *  Created on: 09/09/2014
 *      Author: viniciusoliveira
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "Corner.h"

//-----------------------------------------------------------------------------------------
typedef struct Cell_str *Pointer;

//-----------------------------------------------------------------------------------------
typedef struct Cell_str {
	Corner corner;
	Pointer next;
} Cell;

//-----------------------------------------------------------------------------------------
typedef struct {
	Pointer first;
	Pointer last;
} Queue;


//-----------------------------------------------------------------------------------------
void setQueueEmpty(Queue*);
int isQueueEmpty(Queue);
void insertBack(Queue*, Corner);
void removeFront(Queue*, Corner*);
int contains(Queue, Corner);
void printQueue(Queue);
void freeQueue(Queue*);

#endif /* FILA_H_ */
