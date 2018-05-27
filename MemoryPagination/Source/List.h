/*
 * List.h
 *
 *  Created on: 09/09/2014
 *      Author: viniciusoliveira
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "Page.h"

//-----------------------------------------------------------------------------------------
typedef struct ListPageFrm_str *Pointer;

//-----------------------------------------------------------------------------------------
typedef struct ListPageFrm_str {
	Page page;
	Pointer next;
} ListPageFrame;

//-----------------------------------------------------------------------------------------
typedef struct {
	Pointer first;
	Pointer last;
} List;


//-----------------------------------------------------------------------------------------
void setListEmpty(List*);
int isListEmpty(List);
int pageExists(List, int);
void insertFront(List*, Page);
void insertBack(List*, Page);
void removeFront(List*, Page*);
void removeArbitrary(List*, Pointer);
int moveToLast(List*, Page);
void moveToFront(List*, Page);
void printList(List);
Pointer searchLeastFrequency(List);
void incrementAccesses(List*, int);


#endif /* FILA_H_ */
