/*
 * ThreadArg.h
 *
 *  Created on: 18/11/2014
 *      Author: viniciusoliveira
 */

#ifndef THREADARG_H_
#define THREADARG_H_
#include "Graph.h"
#include <pthread.h>

typedef struct ThreadArg{
	Graph graph;
	int nAgents;
    long long int startIndex;
    long long int iterations;
    long long int* solution; //não posso usar unsigned pois solucao -1 significa que nao existe solucao
	pthread_mutex_t* mutex;
}ThreadArg;

#endif /* THREADARG_H_ */
