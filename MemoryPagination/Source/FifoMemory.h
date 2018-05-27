/*
 * FifoMemory.h
 *
 *  Created on: 10/09/2014
 *      Author: viniciusoliveira
 */

#ifndef FIFOMEMORY_H_
#define FIFOMEMORY_H_

#include "List.h"

//-----------------------------------------------------------------------------------------
typedef struct{
	List list;
	int maxPages;
	int length;
	int pageFaults;
	int currentPage;
}FifoMemory;

//-----------------------------------------------------------------------------------------
void createFifoMemory(FifoMemory*, int, int);
void freeFifoMemory(FifoMemory*);
int* processFifoInstructions(FifoMemory*, int*, int, int);



#endif /* FIFOMEMORY_H_ */
