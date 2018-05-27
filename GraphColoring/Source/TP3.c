/*
 ============================================================================
 Name        : TP3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "Spot.h"
#include "IOHandler.h"

int main(int argc, char* argv[]) {

	Graph graph;
	int algorithm = atoi(argv[1]);

	IOHandler streamHandler;

	openInputFile(&streamHandler, argv[2]);
	openOutputFile(&streamHandler, "coloring.txt");

	int nAgents;
	double radius;

	short endState=0;

	int* solution;

	while(!doneReading(&streamHandler)){

		readState(&graph, &nAgents, &radius, &endState, streamHandler);
		if(!endState){
			solution = paintGraph(graph, nAgents, algorithm);
			writeSolution(graph, solution, nAgents, streamHandler);
			free(solution);
		}
		freeGraph(&graph);
	}

	closeInputFile(&streamHandler);
	closeOutputFile(&streamHandler);
	return 0;
}
