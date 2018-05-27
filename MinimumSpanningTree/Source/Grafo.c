/*
 * Grafo.c
 *
 *  Created on: 11/04/2014
 *      Author: Vinicius Oliveira
 */
#include <stdlib.h>
#include <stdio.h>
#include "Grafo.h"


//================================FUNCOES AUXILIARES================================

void escolheAresta(Grafo graphG, Grafo *graphA, Vertice *v, Vertice *u, int *peso){
	/*
	 * graphG -> Grafo original, informado pelo usuario
	 * graphA -> Grafo que devera ser gerado pelo programa (Arvore Geradora)
	 * v -> vertice qualquer, que sera retornado preenchido com um vertice presente em A e em G.
	 * u -> vertice qualquer, que sera retornado preenchido com um vertice presente somente em G.
	 * */

	Vertice aux;
	int testeComeco=0;

	//Procedimento para verificar se a contagem de vertices da entrada comeca em 0 ou em 1
	aux.Chave=0;
	if(listaAdjVazia(aux, graphG)){
		testeComeco=1;
	}
	//------------------------------------------------------------------------------------

	int i=testeComeco;

	Vertice *vexA;
	vexA=(Vertice *)malloc((graphG.NumVertices+1)*sizeof(Vertice));


	int j=0;

	Pointer apontador;

	//Seta a menor aresta como um milhao. Caso existam arestas com peso superior a um milhao no grafo, poderao ocorrer erros.
	int menorAresta=1000000;


	if(testeComeco==0){
		//PROCEDIMENTOS PARA ESCOLHA DA MENOR ARESTA POSSIVEL CASO A CONTAGEM COMECE EM 0.

		//For que procura todos os vertices de A e os armazena em um array auxiliar;
		for(i=0; i<graphA->NumVertices; i++){
			aux.Chave= i;
			//Se a lista de adjacencia de um vertice esta vazia, significa que ele nao existe no grafo.
			if(!listaAdjVazia(aux, *graphA)){
				vexA[j]=aux;
				j++;
			}
		}

		for(i=0; i<j; i++){
			aux = vexA[i];
			apontador = graphG.Adj[aux.Chave].Primeiro;

			while(apontador!=NULL){
				if(apontador->Prox!=NULL){
					if(apontador->Prox->PesoAresta < menorAresta && listaAdjVazia(apontador->Prox->vertex, *graphA)){
						menorAresta = apontador->Prox->PesoAresta;
						*v = aux;
						*u = apontador->Prox->vertex;
						*peso = menorAresta;
					}
				}
				apontador = apontador->Prox;
			}
		}
	}

	if(testeComeco==1){
		//PROCEDIMENTOS PARA ESCOLHA DA MENOR ARESTA POSSIVEL CASO A CONTAGEM COMECE EM 1.

		//For que procura todos os vertices de A e os armazena em um array auxiliar;
		for(i=1; i<=graphA->NumVertices; i++){
			aux.Chave= i;
			//Se a lista de adjacencia de um vertice esta vazia, significa que ele nao existe no grafo.
			if(!listaAdjVazia(aux, *graphA)){
				vexA[j]=aux;
				j++;
			}
		}

		for(i=0; i<j; i++){
			aux = vexA[i];
			apontador = graphG.Adj[aux.Chave].Primeiro;

			while(apontador!=NULL){
				if(apontador->Prox!=NULL){
					if(apontador->Prox->PesoAresta < menorAresta && listaAdjVazia(apontador->Prox->vertex, *graphA)){
						menorAresta = apontador->Prox->PesoAresta;
						*v = aux;
						*u = apontador->Prox->vertex;
						*peso = menorAresta;
					}
				}
				apontador = apontador->Prox;
			}
		}

	}

	return;
}
//=================================================================================


//================================FUNCOES DISPONIVEIS================================

//Faz a leitura de um grafo a partir de stdin
void leGrafo(Grafo *graph){
	int numVertices;
	int numArestas;

	int i=0;

	scanf("%d %d", &numVertices, &numArestas);

	fazGrafoVazio(graph, numVertices, 0);

	Vertice v1;
	Vertice v2;
	int peso;

	for(i=0; i<numArestas; i++){
		scanf("%d %d %d", &v1.Chave, &v2.Chave, &peso);


		if(!existeAresta(v1, v2, *graph)){

			insereAresta(&v1, &v2, peso, graph);
		}
	}
}
//-------------------------------------------------------

//Inicializa um novo grafo, alocando memoria para todos os seus vertices e inicializando cada lista de adjacencia como vazia.
void fazGrafoVazio(Grafo *graph, int NumVertices, int NumArestas){
	int i=0;
	graph->NumVertices = NumVertices;
	graph->NumArestas = NumArestas;
	graph->Adj = (Lista*)malloc((graph->NumVertices+1)*sizeof(Lista));
	for(i=0; i<=NumVertices; i++){
		fazListaVazia(&(graph->Adj[i]));
	}
}
//-------------------------------------------------------

//Insere uma nova aresta no Grafo. Importante notar que a lista de adjacencia de cada vertice da aresta eh atualizada.
void insereAresta(Vertice *v1, Vertice *v2, int Peso, Grafo *graph){
	Celula aux;
	aux.vertex = *v2;
	aux.PesoAresta = Peso;
	insere(aux, &graph->Adj[v1->Chave]);

	aux.vertex=*v1;
	insere(aux,&graph->Adj[v2->Chave]);
	graph->NumArestas++;
}
//-------------------------------------------------------

//Verifica se a aresta especificada existe ou nao no grafo
int existeAresta(Vertice v1, Vertice v2, Grafo graph){
	Pointer apontador;
	int encontrouAresta = 0;
	apontador = graph.Adj[v1.Chave].Primeiro->Prox;

	while(apontador!= NULL && encontrouAresta == 0){
		if(v2.Chave == apontador->vertex.Chave){
			encontrouAresta = 1;
		}
		apontador = apontador->Prox;
	}
	return encontrouAresta;
}
//-------------------------------------------------------

//Verifica se um vertice existe ou nao no grafo
int listaAdjVazia(Vertice v1, Grafo graph){
	if(vazia(graph.Adj[v1.Chave])){
		return 1;
	}
	return 0;
}
//-------------------------------------------------------

//Retorna um ponteiro que aponta para o primeiro vertice da lista de adjacencia de um vertice especificado.
//Essa funcao nao eh utilizada no trabalho pratico
Pointer primeiroListaAdj(Vertice v1, Grafo graph){
	return graph.Adj[v1.Chave].Primeiro->Prox;
}
//-------------------------------------------------------

//Remove a aresta especificada do Grafo especificado.
void retiraAresta(Vertice v1, Vertice v2, int Peso, Grafo *graph){
	Pointer anterior;
	Pointer aux;
	int EncontrouAresta=0;
	Vertice x;
	anterior = graph->Adj[v1.Chave].Primeiro;
	aux = graph->Adj[v1.Chave].Primeiro->Prox;

	while(aux!=NULL && EncontrouAresta==0){
		if(v2.Chave == aux->vertex.Chave){
			retira(anterior, &graph->Adj[v1.Chave], &x);
			graph->NumArestas--;
			EncontrouAresta =1;
		}
		anterior=aux;
		aux=aux->Prox;
	}
}
//-------------------------------------------------------

//Armazena em destination, a arvore geradora minima do grafo source
void arvoreMinima(Grafo source, Grafo *destination){

	Vertice aux1; //v
	Vertice aux2; //u
	int peso=0;

	int testeComeco=0;

	aux1.Chave=0;
	if(listaAdjVazia(aux1, source)){
		testeComeco=1;

	}


	fazGrafoVazio(destination, source.NumVertices, 0);
	(*destination).Adj[testeComeco].Primeiro = source.Adj[testeComeco].Primeiro; //Celula Cabeca

	int i=testeComeco;

	if(testeComeco==0){

		while(i<(source.NumVertices-1)){
			escolheAresta(source, destination, &aux1, &aux2, &peso);

			if(i==0){
				fazListaVazia(&( (*destination).Adj[0] ));
			}
			insereAresta(&aux1, &aux2,peso,destination);
			i++;
		}
	}

	if(testeComeco==1){
		while(i<(source.NumVertices)){
			escolheAresta(source, destination, &aux1, &aux2, &peso);
			if(i==1){
				fazListaVazia(&( (*destination).Adj[1] ));
			}

			insereAresta(&aux1, &aux2,peso,destination);
			i++;
		}
	}

}
//-------------------------------------------------------

//Libera o espaco de memoria ocupado por um grafo especificado
void liberaGrafo(Grafo *graph){
	Pointer anterior;
	Pointer aux;
	int i=0;
	for(i=0; i<graph->NumVertices; i++){
		aux = graph->Adj[i].Primeiro->Prox;
		free(graph->Adj[i].Primeiro);
		graph->Adj[i].Primeiro = NULL;
		while(aux!=NULL){
			anterior =aux;
			aux = aux->Prox;
			free(anterior);
		}
	}
	graph->NumVertices=0;
	graph->NumArestas=0;
}
//-------------------------------------------------------

//Faz a impressao ordenada de um grafo no seguinte formato:
//<vertice1> <vertice2> <peso_aresta>
void imprimeOrdenado(Grafo graph){
	int i=0;

	Pointer aux;
	printf("%d %d\n",graph.NumVertices, graph.NumArestas);
	for(i=0; i<graph.NumVertices; i++){
		if(!vazia(graph.Adj[i])){
			aux = graph.Adj[i].Primeiro->Prox;
			while(aux!=NULL){
				if(i<aux->vertex.Chave){
					printf("%d %d %d\n", i, aux->vertex.Chave, aux->PesoAresta);
				}
				aux = aux->Prox;
			}
		}
	}
}
//-------------------------------------------------------

//Faz a impressao padrao de um grafo.
//Funcao nao utilizada neste trabalho.
void imprimeGrafo(Grafo graph){
	int i;
	Pointer aux;
	for(i=0; i<(graph.NumVertices + 1); i++){
		printf("Vertice%2d", i);
		if(!vazia(graph.Adj[i])){
			aux = graph.Adj[i].Primeiro->Prox;
			while(aux!=NULL){
				printf("%3d(%d)", aux->vertex.Chave, aux->PesoAresta);
				aux = aux->Prox;
			}
		}
		printf("\n");
	}

}
//===================================================================================

