/*
 * MruMemory.h
 *
 *  Created on: 14/09/2014
 *      Author: viniciusoliveira
 */

#ifndef MRUMEMORY_H_
#define MRUMEMORY_H_

#include "List.h"

//-----------------------------------------------------------------------------------------
typedef struct{
	List list;
	int maxPages;
	int length;
	int pageFaults;
}MruMemory;

//-----------------------------------------------------------------------------------------
void createMruMemory(MruMemory*, int, int);
void freeMruMemory(MruMemory*);
void processMruInstructions(MruMemory*, int*, int, int);


#endif /* MRUMEMORY_H_ */
