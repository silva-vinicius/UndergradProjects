/*
 * Bordas.c
 *
 *  Created on: 21/03/2014
 *      Author: viniciusoliveira
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "TipoImagem.h"


int main(int argc, char *argv[]){
	TipoImagem img;
	LeImagem(&img);
	DetectaBorda(&img);
	ImprimeImagem(&img);
	return 0;
}
