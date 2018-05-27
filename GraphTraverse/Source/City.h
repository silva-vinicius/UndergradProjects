/*
 * City.h
 *
 *  Created on: 12/10/2014
 *      Author: viniciusoliveira
 */

#ifndef CITY_H_
#define CITY_H_
#include "Corner.h"

//-----------------------------------------------------------------------------------------
typedef struct City {
	Corner** cornerGrid;
	int streets;
	int avenues;
} City;

//-----------------------------------------------------------------------------------------
City createCity(int streets, int avenues);
void closeCorner(City* city, int streetNumber, int avenueNumber);
void getAmntPaths(City* city);
void printCity(City city);
void freeCity(City* city);
//-----------------------------------------------------------------------------------------
#endif /* CITY_H_ */
