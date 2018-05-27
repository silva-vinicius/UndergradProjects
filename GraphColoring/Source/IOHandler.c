/*
 * IOHandler.c
 *
 *  Created on: 20/11/2014
 *      Author: viniciusoliveira
 */
#include <stdlib.h>
#include "IOHandler.h"
#include "Graph.h"
#include "Spot.h"

//-----------------------------------------------------------------------------------------
void openInputFile(IOHandler* ioControl, char* fileName){
	ioControl->input = fopen(fileName,"r");
}

//-----------------------------------------------------------------------------------------
void openOutputFile(IOHandler* ioControl, char* fileName){
	ioControl->output = fopen(fileName,"w");
}

//-----------------------------------------------------------------------------------------
void readConfig(long int* nAgents, double* radius , IOHandler ioControl){
	fscanf(ioControl.input,"%ld %lf\n", nAgents, radius);
}

//-----------------------------------------------------------------------------------------
void readState(Graph* graph, int* nAgents, double* radius, short* endState, IOHandler ioControl){

	char caractere;
	initializeGraph(graph);
	Spot aux;

	caractere =fgetc(ioControl.input);

	if(caractere!=EOF && caractere!='\n'){
		*endState=0;
		fseek(ioControl.input, -1, 1);
		fscanf(ioControl.input, "%d %lf", nAgents, radius);

		caractere = fgetc(ioControl.input);//pega o \n do final da linha
		caractere = fgetc(ioControl.input);//pega o caractere da linha de baixo

		while(caractere != '\n' && caractere != EOF){
			fseek(ioControl.input, -1, 1);
			fscanf(ioControl.input, "%d %lf %lf", &(aux.ID), &(aux.x_coord), &(aux.y_coord));

			setAdjListEmpty(&(aux.adj));
			insertVertex(graph, aux);
			caractere = fgetc(ioControl.input);
			caractere = fgetc(ioControl.input);
		}

		generateGraph(graph, *radius);
	}else{
		*endState=1;
	}
}

//-----------------------------------------------------------------------------------------
short doneReading(IOHandler* ioControl){
	return feof(ioControl->input);
}

//-----------------------------------------------------------------------------------------
void writeSolution(Graph graph, int* result, int nAgents,  IOHandler ioControl){
	int flagEndLine=0;
	int colorAux=0;

	int i=0;
	int j=0;

	if(result ==NULL){
		fprintf(ioControl.output, "not implemented\n");
		return;
	}

	if(result[0]==-1){
		fprintf(ioControl.output, "no solution\n");
	}else{
		for(i=0; i<nAgents; i++){
			colorAux = i;
			for(j=0; j<graph.size; j++){
				if(result[j] == colorAux){
					fprintf(ioControl.output, "%d ",graph.map[j].ID);
					flagEndLine =1;
				}
			}
			if(flagEndLine){
				fprintf(ioControl.output, "\n");
				flagEndLine=0;
			}

		}
		fprintf(ioControl.output, "\n");
	}
}

//-----------------------------------------------------------------------------------------
void closeInputFile(IOHandler* ioControl){
	fclose(ioControl->input);
}

//-----------------------------------------------------------------------------------------
void closeOutputFile(IOHandler* ioControl){
	fclose(ioControl->output);
}

