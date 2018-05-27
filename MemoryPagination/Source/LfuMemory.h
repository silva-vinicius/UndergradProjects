/*
 * LfuMemory.h
 *
 *  Created on: 14/09/2014
 *      Author: viniciusoliveira
 */

#ifndef LFUMEMORY_H_
#define LFUMEMORY_H_

#include "List.h"

//-----------------------------------------------------------------------------------------
typedef struct{
	List list;
	int maxPages;
	int length;
	int pageFaults;
}LfuMemory;

//-----------------------------------------------------------------------------------------
void createLfuMemory(LfuMemory*, int, int);
void freeLfuMemory(LfuMemory*);
void processLfuInstructions(LfuMemory*, int*, int, int);


#endif /* LFUMEMORY_H_ */
