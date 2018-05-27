/*
 * TipoImagem.h
 *
 *  Created on: 21/03/2014
 *      Author: viniciusoliveira
 */

#ifndef TIPOIMAGEM_H_
#define TIPOIMAGEM_H_

#endif /* TIPOIMAGEM_H_ */


typedef struct{
	int altura;
	int largura;
	int **imagem;
}TipoImagem;

void LeImagem(TipoImagem *image);
void DetectaBorda(TipoImagem *image);
void ImprimeImagem(TipoImagem *image);

