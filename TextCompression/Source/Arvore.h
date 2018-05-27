/*
 * arvore.h
 *
 *  Created on: 23/05/2014
 *      Author: Vinicius Oliveira
 */

#ifndef ARVORE_H_
#define ARVORE_H_

//-------------------------------------------------------
typedef struct Node* Arvore;

//-------------------------------------------------------
typedef struct Node{

	int codigo; //guarda as frequencias
	char caracter;
	char* byte;
	Arvore esquerda;
	Arvore direita;
} Node;
//-------------------------------------------------------

//-------------------------------------------------------
void fazArvoreVazia(Arvore *tree);
Arvore construir(char* texto, Node** tabelaFreq);
char* getBytes(char letra, Arvore tree);
void imprimeBytes(Node* tabelaFreq, Arvore tree,  char* texto);
void imprimeCompactado(Node* tabelaFreq, Arvore tree,  char* texto);

//-------------------------------------------------------

#endif /* ARVORE_H_ */
