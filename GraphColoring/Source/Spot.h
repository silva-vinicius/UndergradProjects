/*
 * Spot.h
 *
 *  Created on: 14/11/2014
 *      Author: viniciusoliveira
 */

#ifndef SPOT_H_
#define SPOT_H_
#include "AdjList.h"

typedef struct Spot{
	int ID; //Identificador do ponto
	double x_coord;
	double y_coord;
	AdjList adj; //Lista de adjacencia do ponto (fila de ints)
	int amnt_adj; //Quantidade de vizinhos do ponto;

}Spot;

#endif /* SPOT_H_ */
