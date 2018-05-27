/*
 ============================================================================
 Name        : tp2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "City.h"

int main(int argc, char *argv[]) {

	FILE *inputFile;
	FILE *outputFile;

	inputFile = fopen (argv[1], "r");
	outputFile = fopen (argv[2],"w");

	int tasks; //variavel N
	int counter=0;

	int streets, avenues; //variaveis Y e X, respectivamente

	int amntBlockedCorners; //variavel E

	int amntDestinations; //variavel C

	int blockedSt=0;
	int blockedAv=0;
	int i=0;

	City johnville; //variavel da cidade
	Corner* destinations;

	//Numero de instancias
	fscanf (inputFile,"%d", &tasks);

	//executa o programa tasks vezes
	for(counter=0; counter < tasks; counter++){

		//Dimensoes da cidade
		fscanf (inputFile,"%d %d", &streets, &avenues);

		johnville = createCity(avenues,streets);

		//Numero de esquinas bloqueadas
		fscanf (inputFile,"%d", &amntBlockedCorners);

		//leitura das esquinas bloqueadas
		for(i=0; i<amntBlockedCorners; i++){
			fscanf (inputFile,"%d %d", &blockedSt, &blockedAv);
			closeCorner(&johnville, blockedSt-1, blockedAv-1);
		}

		//Numero de destinos
		fscanf (inputFile,"%d", &amntDestinations);

		//aloca memoria
		destinations = (Corner*)malloc(((amntDestinations+1) * sizeof(Corner)));

		//Le as coordenadas dos destinos bloqueados
		for(i=1; i<=amntDestinations; i++){

			fscanf (inputFile,"%d %d", &(destinations[i].i), &(destinations[i].j));

			(destinations[i].j)--;
			(destinations[i].i)--;
		}

		//Chamada da funcao principal
		getAmntPaths(&johnville);

		for(i=1; i<=amntDestinations; i++){
			fprintf(outputFile,"%ld\n",(johnville.cornerGrid[destinations[i].i][destinations[i].j]).amntMinimalPaths);
		}
		if(counter!=tasks-1){
			fprintf(outputFile,"\n");
		}

		freeCity(&johnville);
		free(destinations);
	}

	return EXIT_SUCCESS;
}
