/*
 * TipoImagem.c
 *
 *  Created on: 21/03/2014
 *      Author: viniciusoliveira
 */

#include <stdio.h>
#include <stdlib.h>
#include "TipoImagem.h"


/*
 * Funcao que le a imagem do arquivo e atribui os "pixels" a matriz do objeto
 * "image
*/
void LeImagem(TipoImagem *image){
	//Le e ignora a string de identificacao
	char desprezivel='a';
	int  dispensavel=0;
	scanf("%c%d", &desprezivel, &dispensavel);


	//Le as dimensoes da Imagem
	scanf("%d %d", &(image->largura), &(image->altura));


	//Aloca a memoria para o ponteiro de ponteiros
	image->imagem = (int **) malloc((image->altura)*sizeof(int*));

	int x=0;
	for(x=0; x<(image->altura); x++){
		image->imagem[x] =  (int*)malloc((image->largura)*sizeof(int) );
		if (image->imagem[x] == NULL) {
		      printf("\nFatal Error! (function: LeImagem)\n");
		      exit(1);
		 }
	}

	//Faz a leitura dos "pixels" da imagem para a matriz
	int i=0;
	int j=0;
	for(i=0; i<(image->altura); i++){
		for(j=0;j<(image->largura); j++){

			scanf("%d",&(image->imagem[i][j]));
		}
	}
	return;
}

//----------------------------------------------------------------
/*
 * Funcao que aplica o filtro a imagem.
*/
void DetectaBorda(TipoImagem *image){

	int i=0;
	int j=0;


	//uma matriz auxiliar e' criada para armazenar a imagem a ser gerada
	int **aux;

	//alocamos memoria para a nova matriz de acordo com o tamanho da imagem original
	aux = (int **) malloc(image->altura*sizeof(int*));
	int x=0;
	for(x=0; x<(image->altura); x++){
		aux[x]=(int*)malloc(image->largura*sizeof(int*));
	}


	//o filtro e' aplicado na figura
	for(i=0; i<(image->altura); i++){
		for(j=0; j<(image->largura); j++){

			if( (i==0) || (j==0) || (i==((image->altura)-1)) || (j==((image->largura)-1))){
				aux[i][j] = 0;
			}else{
				aux[i][j] = (8 * image->imagem[i][j]) - (image->imagem[i-1][j-1] + image->imagem[i-1][j] + image->imagem[i-1][j+1] + image->imagem[i][j-1] + image->imagem[i][j+1] + image->imagem[i+1][j-1] + image->imagem[i+1][j] + image->imagem[i+1][j+1]);
				if(aux[i][j] < 0){
					aux[i][j] = 0;
				}
				if (aux[i][j] > 1){
					aux[i][j] = 1;
				}
			}
		}
	}

	//copia a matriz auxiliar para a matriz principal, sobrescrevendo os seus dados anteriores
	for(i=0;i<(image->altura); i++){
		for(j=0; j<(image->largura); j++){
			image->imagem[i][j] = aux[i][j];
		}
	}

	//desaloca a memoria da matriz auxiliar
	for(i=0; i<(image->altura); i++){
		free(aux[i]);
	}
	free(aux);

}

//----------------------------------------------------------------
/*
 * Funcao que imprime a matriz de um "objeto" TipoImagem especificada via parametro.
 * A funcao tambem desaloca a memoria usada pela matriz depois que a mesma e' impressa.
 *
*/
void ImprimeImagem(TipoImagem *image){

	//imprime a string "chave"
	printf("P1\n");
	//imprime as dimensoes da imagem
	printf("%d %d\n", image->largura, image->altura);

	int i=0;
	int j=0;

	//faz a impressao propriamente dita.
	for(i=0; i<(image->altura); i++){
		for(j=0; j<(image->largura); j++){
			printf("%d ", image->imagem[i][j]);
		}
		printf("\n");
	}

	/*
	 * Desaloca a memoria da matriz principal. Este e' o motivo pelo qual o "objeto" image
	 * e' recebido por ponteiro.
	*/
	for(i=0; i<(image->altura); i++){
		free(image->imagem[i]);
	}
	free(image->imagem);

	return;
}

//----------------------------------------------------------------

