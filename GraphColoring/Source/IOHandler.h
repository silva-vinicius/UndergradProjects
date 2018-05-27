/*
 * IO.h
 *
 *  Created on: 20/11/2014
 *      Author: viniciusoliveira
 */

#ifndef IO_H_
#define IO_H_
#include <stdio.h>
#include "Graph.h"
#include "Spot.h"


typedef struct IOHandler{

	FILE* input;
	FILE* output;

}IOHandler;

void openInputFile(IOHandler*, char*);
void openOutputFile(IOHandler*, char*);
void readConfig(long int*, double*, IOHandler);
void readState(Graph*, int*, double*, short*, IOHandler);
short doneReading(IOHandler*);
void writeSolution(Graph, int*, int, IOHandler);
void closeInputFile(IOHandler*);
void closeOutputFile(IOHandler*);



#endif /* IO_H_ */
