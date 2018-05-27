/*
 * LruMemory.h
 *
 *  Created on: 13/09/2014
 *      Author: viniciusoliveira
 */

#ifndef LRUMEMORY_H_
#define LRUMEMORY_H_

#include "List.h"

//-----------------------------------------------------------------------------------------
typedef struct{
	List list;
	int maxPages;
	int length;
	int pageFaults;
}LruMemory;

//-----------------------------------------------------------------------------------------
void createLruMemory(LruMemory*, int, int);
void freeLruMemory(LruMemory*);
int* processLruInstructions(LruMemory*, int*, int, int);


#endif /* LRUMEMORY_H_ */
