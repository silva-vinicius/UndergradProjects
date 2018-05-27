/*
 * PaintUtils.c
 *
 *  Created on: 21/11/2014
 *      Author: vinicius
 */

#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <pthread.h>
#include "Graph.h"
#include "Spot.h"
#include "AdjList.h"
#include "ThreadArg.h"

#define NUM_THREADS 2


//=================================FUNCOES INTERNAS AO TAD================================
//testa se um conjunto de cores eh valido
int testColoring(Graph map, int*colors){
	int i=0;
	int currentColor;
	Pointer aux;

	//loop externo percorre cada posicao do vetor de cores
	for(i=0; i<map.size; i++){
		currentColor = colors[i];


		aux = map.map[i].adj.first->next;

		//percorre a lista de adjacencia para ver se um vertice tem a mesma cor do vizinho
		while(aux!=NULL){
			if(colors[aux->position] == currentColor ){
				return 0;
			}
			aux = aux->next;
		}
	}


	return 1;
}

//-----------------------------------------------------------------------------------------
//copia um array para o outro
void copyArray(int* destination, int *source, int length){
	int i=0;
	for(i=0; i<length; i++){
		destination[i] = source[i];
	}

	return;
}

//-----------------------------------------------------------------------------------------
//pesquisa no vetor o numero de cores utilizadas por uma solucao
long int getAmntColors(int *array, int length){

	AdjList exclusiveColors;
	setAdjListEmpty(&exclusiveColors);

	long int numExclusiveColors=0;
	long int i=0;

	for(i=0; i<length; i++){
		if(!contains(exclusiveColors, array[i])){
			numExclusiveColors++;
			insertAdj(&exclusiveColors, array[i]);
		}
	}

	freeAdjList(&exclusiveColors);

	return numExclusiveColors;
}

//-----------------------------------------------------------------------------------------
//converte um numero para uma coloracao equivalente (conversao de base n-aria
void converter (int nDigits,  long long int origNumber, int newBase, int *returnValue){
	long int i;
	for (i=0; i<nDigits; i++){
		returnValue[i] = 0;
	}
	for (i = nDigits-1; i >= 0; i--){
		if (origNumber!=0){
			returnValue[i] = origNumber%newBase;
			origNumber = origNumber/newBase;
		}
	}
}

//-----------------------------------------------------------------------------------------
//Funcao executada pelas threads
void *threadJob(void* arg){


	ThreadArg *argument = (ThreadArg*) arg;

	//-***************limites do loop da thread****************
	long long int i;
	long long int limit = argument->iterations + argument->startIndex;
	//-********************************************************


	//-***********solucao encontrada pela thread**************
	int *colors;
	colors = (int*)malloc((argument->graph.size)*sizeof(int));
	int nColors; //numero de cores da solucao encontrada pela thread


	long long int bestSolution = -1; //melhor solucao encontrada ate o momento pela thread

	int leastColors; //numero de cores da melhor solucao encontrada por essa thread
	leastColors = INT_MAX;
	//-********************************************************



	for(i=argument->startIndex; i<limit; i++){
		converter(argument->graph.size, i, argument->nAgents, colors);

		if(testColoring(argument->graph, colors)){
			nColors = getAmntColors(colors, argument->graph.size);
			if(nColors < leastColors){
				bestSolution = i;
				leastColors = nColors;
			}
		}
	}

	int minColors = INT_MAX; //numero de cores da melhor solucao dentre todas as threads;

	//inicio da secao critica
	pthread_mutex_lock(argument->mutex);

	if((*(argument->solution))!=-1){ //pega o numero de cores da solucao global

		converter(argument->graph.size,(*(argument->solution)), argument->nAgents, colors);
		minColors =  getAmntColors(colors, argument->graph.size);
	}

	if(leastColors < minColors){
		(*(argument->solution)) = bestSolution;
		//minColors = nColors;
		minColors = leastColors;
	}
	pthread_mutex_unlock(argument->mutex);
	//fim da secao critica



	free(colors);

	return NULL;

}

//verifica se existe um vertice da cor especificada na lista de adjacencia
//retorna falso se existe e true se nao existe (checa se a cor e' segura para colorir um vertice)
short safeColor(AdjList list, int searchedColor, int* colors){

	Pointer pointer;
	pointer = list.first->next;

	while(pointer!=NULL){
		if(colors[pointer->position]==searchedColor){
			return 0;
		}
		pointer = pointer->next;
	}
	return 1;
}

//========================================================================================

//Inicia a busca por solucao usando paralelismo
int* parallel(Graph map, int nAgents){

	int* colors;
	colors = (int*)malloc((map.size)*sizeof(int));

	//Cria um vetor de threads
	pthread_t *threads;
	threads = (pthread_t*)malloc(NUM_THREADS*sizeof(pthread_t));


	int i=0;

	//Definicao dos argumentos de cada thread
	ThreadArg *arguments;
	arguments = (ThreadArg*) malloc(NUM_THREADS*sizeof(ThreadArg));

	//cria um mutex comum a todas as threads
	pthread_mutex_t* mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex, NULL); //inicializa a exclusao mutua

	//cria uma solucao comum a todas as threads
	long long int* solution;
	solution = (long long int*)malloc(sizeof(long long int));
	*solution =-1;

	//auxilar no controle de trabalho de cada thread
	int j=0;

	//inicializa os argumentos de cada thread
	for(i=0; i<NUM_THREADS; i++){
		arguments[i].graph = map;
		arguments[i].mutex = mutex;
		arguments[i].nAgents = nAgents;
		arguments[i].solution = solution;
		arguments[i].iterations = (pow(nAgents, map.size) /NUM_THREADS);

		arguments[i].startIndex = j;

		j+=arguments[i].iterations;
	}


	//corrigir problemas de arredondamento do trabalho das threads
	//a ultima thread pode ter mais trabalho que as demais
	i--;
	long int totalIterations = pow(nAgents, map.size);

	if(arguments[i].startIndex + arguments[i].iterations != totalIterations){

		arguments[i].iterations += (totalIterations - (arguments[i].startIndex + arguments[i].iterations));
	}

	//criar as threads
	for(i=0; i< NUM_THREADS; i++){
		pthread_create(&(threads[i]), NULL,threadJob, &(arguments[i]));
	}

	//Finaliza as threads depois de serem executadas
	for(i=0; i<NUM_THREADS; i++){
		pthread_join(threads[i], NULL);
	}

	if(*(solution)!=-1){

		converter(map.size, *(solution), nAgents, colors);
	}else{
		colors[0]=-1; //indicativo que nao houve solucao encontrada
	}

	free(threads);
	free(arguments);
	free(mutex);
	free(solution);


	return colors;
}

//-----------------------------------------------------------------------------------------
//Inicia a busca por solucoes usando forca bruta
int* bruteForce(Graph map, int nAgents){

	long long int counter=0;
	int *colors; //vetor que armazenara cada coloracao possivel
	colors = (int*)malloc((map.size)*sizeof(int));

	int *solution;
	solution = (int*)malloc((map.size)*sizeof(int));
	solution[0]=-1; //posicao 0 igual a -1 quer dizer que nao foi encontrada solucao;

	int solutionAmntColors = INT_MAX; //numero de cores da melhor solucao
	int amntColors; //numero de cores da coloracao que acabou de ser encontrada

	//testar cada combinacao possivel de cores
	for(counter=0; counter < pow(nAgents, map.size); counter++){

		converter(map.size, counter, nAgents, colors);

		if(testColoring(map, colors)){
			amntColors = getAmntColors(colors, map.size);

			/* se a  coloracao que acabou de ser encontrada usar menos
			 * cores que a melhor solucao ate entao, substituir
			 * a melhor solucao pela nova.
			 */
			if(solutionAmntColors > amntColors ){
				copyArray(solution, colors, map.size);
				solutionAmntColors = amntColors;
			}
		}
	}

	free(colors);
	return solution;
}

//-----------------------------------------------------------------------------------------
//Inicia a busca por solucoes usando heuristica
int* heuristic(Graph map, int nAgents){


	int* colors;
	int blankVertexes = map.size;

	colors = (int*)malloc(blankVertexes*sizeof(int));

	int i=0;

	for(i=0; i< blankVertexes; i++){
		colors[i]=-1; //todos os vertices estao em branco
	}


	int cor=0;

	i=0; //contador do grafo
	int j=0;

	while(blankVertexes!=0){

		if(colors[i]==-1 && safeColor(map.map[i].adj,cor, colors)){
			colors[i]=cor;
			blankVertexes--;
		}
		i++;
		if(i==map.size){
			j++;
			i=j;
			cor++;
		}

	}

	/*verifica se o numero de cores usadas na solucao heurisitica
	 * eh maior que o numero de agentes disponiveis, caso seja,
	 * imprimir que nao existe solucao. Para que seja impresso tambem
	 * a solucao com numero excessivo de cores, basta que seja impresso
	 * o vetor colors pela funcao writeSolution do TAD IOHandler.
	 * Nao houve contudo, tempo para implementar as mudancas estruturais
	 * para permitir a chamada a essa funcao de maneira adequada, sem que
	 * seja ferido o encapsulamento implementado.
	 *
	 */
	if(cor>nAgents){
		colors[0]=-1;
	}

	return colors;

}


