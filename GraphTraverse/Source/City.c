/*
 * City.c
 *
 *  Created on: 17/10/2014
 *      Author: viniciusoliveira
 */
#include "City.h"
#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/*
 *Cria uma matriz de esquinas de forma que cada esquina aponte para o seu vizinho da
 *direita e de baixo;
 */
City createCity(int avenues, int streets){

	City city;

	city.avenues = avenues;
	city.streets = streets;
	city.cornerGrid = (Corner**)malloc(streets*sizeof(Corner*));

	//alocar memoria para cada corner da matriz
	int i=0;
	for(i=0; i<(streets); i++){
		city.cornerGrid[i] =  (Corner*)malloc((avenues)*sizeof(Corner));
		if (city.cornerGrid[i] == NULL) {
			printf("\nFatal Error! (function: createCity)\n");
			exit(1);
		}
	}
	int j=0;

	//Incializa as esquinas como abertas
	for(i=0; i<(streets); i++){
		for(j=0; j<(avenues); j++){
			(city.cornerGrid[i][j]).isClosed=0;
			(city.cornerGrid[i][j]).amntMinimalPaths=0;
			(city.cornerGrid[i][j]).distance = LONG_MAX;
			(city.cornerGrid[i][j]).i = i;
			(city.cornerGrid[i][j]).j = j;
		}
	}
	//existe um unico caminho minimo para o vertice (0,0): ficar parado
	city.cornerGrid[0][0].amntMinimalPaths = 1;

	return city;
}
//-----------------------------------------------------------------------------------------

//Faz com que uma esquina da cidade seja fechada
void closeCorner(City* city, int streetNumber, int avenueNumber){
	city->cornerGrid[streetNumber][avenueNumber].isClosed =1;
}

//-----------------------------------------------------------------------------------------
/*
 * Funcao principal do programa. Calcula o menor numero de caminhos
 * para cada esquina da cidade
 */
void getAmntPaths(City* city){

	Queue queue;
	setQueueEmpty(&queue);


	(city->cornerGrid[0][0]).amntMinimalPaths=1;
	(city->cornerGrid[0][0]).distance = 0;
	insertBack(&queue, city->cornerGrid[0][0]);

	Corner aux;


	while(!isQueueEmpty(queue)){

		removeFront(&queue, &aux);

		if( (aux.j)+1 < city->avenues){
			//vizinho da direita

			//verifica se o vizinho nao esta fechado
			if(!(city->cornerGrid[aux.i][(aux.j)+1]).isClosed){

				//verifica se o vizinho ta na fila
				if(contains(queue, city->cornerGrid[aux.i][(aux.j)+1])){
					city->cornerGrid[aux.i][(aux.j)+1].amntMinimalPaths += city->cornerGrid[aux.i][aux.j].amntMinimalPaths;
				}

				//verifica se ja passei pelo vizinho
				if( (city->cornerGrid[aux.i][(aux.j)+1]).distance == LONG_MAX){
					//se nao: inserir na fila
					//		  distancia = distancia_aux+1
					//		  ncaminhos = auxilar
					city->cornerGrid[aux.i][(aux.j)+1].amntMinimalPaths = city->cornerGrid[aux.i][(aux.j)].amntMinimalPaths;
					city->cornerGrid[aux.i][(aux.j)+1].distance = city->cornerGrid[aux.i][(aux.j)].distance+1;
					insertBack(&queue, city->cornerGrid[aux.i][(aux.j)+1]);
				}
				//se sim: nada a fazer
			}
		}

		if((aux.j)-1 >= 0){
			//vizinho da esquerda

			//verifica se o vizinho nao esta fechado
			if(!(city->cornerGrid[aux.i][(aux.j)-1]).isClosed){

				//verifica se o vizinho ta na fila
				if(contains(queue, city->cornerGrid[aux.i][(aux.j)-1])){
					//ncaminhos+=
					city->cornerGrid[aux.i][(aux.j)-1].amntMinimalPaths += city->cornerGrid[aux.i][aux.j].amntMinimalPaths;
				}

				//verifica se ja passei pelo vizinho
				if( (city->cornerGrid[aux.i][(aux.j)-1]).distance == LONG_MAX){
					//se nao: inserir na fila
					//		  distancia = distancia_aux+1
					//		  ncaminhos = auxilar
					city->cornerGrid[aux.i][(aux.j)-1].amntMinimalPaths = city->cornerGrid[aux.i][(aux.j)].amntMinimalPaths;
					city->cornerGrid[aux.i][(aux.j)-1].distance = city->cornerGrid[aux.i][(aux.j)].distance+1;
					insertBack(&queue, city->cornerGrid[aux.i][(aux.j)-1]);
				}
				//se sim: nada a fazer
			}
		}

		if((aux.i)+1 < city->streets){
			//vizinho de baixo

			//verifica se o vizinho nao esta fechado
			if(!(city->cornerGrid[(aux.i)+1][aux.j]).isClosed){

				//verifica se o vizinho ta na fila
				if(contains(queue, city->cornerGrid[(aux.i)+1][aux.j])){
					//ncaminhos+=
					city->cornerGrid[(aux.i)+1][aux.j].amntMinimalPaths += city->cornerGrid[aux.i][aux.j].amntMinimalPaths;
				}

				//verifica se ja passei pelo vizinho
				if( (city->cornerGrid[(aux.i)+1][aux.j]).distance == LONG_MAX){
					//se nao: inserir na fila
					//		  distancia = distancia_aux+1
					//		  ncaminhos = auxilar
					city->cornerGrid[(aux.i)+1][aux.j].amntMinimalPaths = city->cornerGrid[aux.i][(aux.j)].amntMinimalPaths;
					city->cornerGrid[(aux.i)+1][aux.j].distance = (city->cornerGrid[aux.i][(aux.j)].distance)+1;
					insertBack(&queue, city->cornerGrid[(aux.i)+1][aux.j]);
				}
				//se sim: nada a fazer
			}
		}

		if((aux.i)-1 >= 0){

			//verifica se o vizinho nao esta fechado
			if(!(city->cornerGrid[(aux.i)-1][aux.j]).isClosed){

				//verifica se o vizinho ta na fila
				if(contains(queue, city->cornerGrid[(aux.i)-1][aux.j])){
					//ncaminhos+=
					city->cornerGrid[(aux.i)-1][aux.j].amntMinimalPaths += city->cornerGrid[aux.i][aux.j].amntMinimalPaths;
				}

				//verifica se ja passei pelo vizinho
				if( (city->cornerGrid[(aux.i)-1][aux.j]).distance == LONG_MAX){
					//se nao: inserir na fila
					//		  distancia = distancia_aux+1
					//		  ncaminhos = auxilar
					city->cornerGrid[(aux.i)-1][aux.j].amntMinimalPaths = city->cornerGrid[aux.i][(aux.j)].amntMinimalPaths;
					city->cornerGrid[(aux.i)-1][aux.j].distance = (city->cornerGrid[aux.i][(aux.j)].distance)+1;
					insertBack(&queue, city->cornerGrid[(aux.i)-1][aux.j]);
				}
				//se sim: nada a fazer
			}
		}
	}
	freeQueue(&queue);
}

//-----------------------------------------------------------------------------------------
//libera a matriz da cidade
void freeCity(City* city){

	city->avenues=0;
	city->streets=0;
	//desalocar memoria para cada corner da matriz
	int i=0;
	for(i=0; i<(city->streets); i++){
		free(city->cornerGrid[i]);
	}
	free(city->cornerGrid);
}

//-----------------------------------------------------------------------------------------
//Imprime a cidade em stdout.
//Funcao nao utilizada neste trabalho.
void printCity(City city){
	printf("Imprimindo a cidade: \n");
	int i=0;
	int j=0;

	for(i=0; i<(city.streets); i++){
		for(j=0; j<(city.avenues); j++){

			if((city.cornerGrid[i][j]).isClosed){
				printf("    X     ");
			}else{
				if(i==0 && j==0){
					printf("    J     ");
				}else{
					printf(" (%02d, %02d) ", i, j);
				}

			}
		}
		printf("\n");
	}
}
