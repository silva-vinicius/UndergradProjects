/*
 ============================================================================
 Name        : TP2.c
 Author      : 
 Version     :
 Copyright   :
 Description : main function of TP2 in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arvore.h"

//-------------------------------------------------------------------------------
int main(void) {

	//Leitura da Entrada;
	char* texto;
	texto = (char*)malloc(10001*sizeof(char)); //espaco extra para o '\n'
	fgets(texto, 10001, stdin);
	Arvore tabelaFrequencia;

	Arvore tree;
	tree = construir(texto, &tabelaFrequencia);
	imprimeCompactado(tabelaFrequencia, tree, texto);

	return EXIT_SUCCESS;
}
