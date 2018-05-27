/*
 ============================================================================
 Name        : TP1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Page.h"
#include "List.h"
#include "FifoMemory.h"
#include "LruMemory.h"
#include "LfuMemory.h"
#include "MruMemory.h"

int main(void) {

	/*********************TESTS*********************/
	/*-----------DEC TO BIN OK----------------------
	int i=0;
	int *array;
	array= dectobin(20,32);

	for(i=0; i<32; i++){
		printf("%d", array[i]);
	}
	printf("\n\n");
	//----------------------------------------------

	//-----------BYTE MANIPULATIONS OK--------------
	Byte b;
	b = createByte(array, 32);
	printf("Byte created. Printing underneath...\n");
	printByte(b);
	printf("\n");
	printf("Deleting byte...\n");
	deleteByte(&b);
	printf("Byte deleted...\n Attempting to print:\n");
	printByte(b);
	printf("\n\n");
	//----------------------------------------------

	//-----------PAGE MANIPULATIONS OK--------------
	Page pagina;
	pagina = createPage(4);
	loadPage(&pagina,4);
	printPage(pagina);
	//----------------------------------------------

	//-----------QUEUE MANIPULATIONS OK--------------
	Page pagina2;
	pagina2 = createPage(4);
	loadPage(&pagina2,10);

	List fila;
	setListEmpty(&fila);




	insertElement(&fila, pagina);
	insertElement(&fila, pagina2);
	printf("Attempting to print list:\n");
	printList(fila);
	printf("\n\n");

	printf("Attempting to delist:\n");
	removeElement(&fila,&pagina);
	printf("Pageframe Removed\n");

	printf("Attempting to print list again:\n");
	printList(fila);
	printf("\n\n");

	removeElement(&fila,&pagina);
	if(isEmpty(fila)){
		printf("Fila vazia!\n\n");
		printList(fila);
	}
	//----------------------------------------------*/

	LruMemory lru;
	FifoMemory fifo;
	LfuMemory lfu;
	MruMemory mru;

	int instances=0;
	int memorySize;
	int pageSize;
	int setSize;
	int* instructions;

	int* stackDistance;
	int* pageDistance;

	scanf("%d", &instances);

	int i=0;
	int j=0;


	for(i=0; i<instances; i++){

		//leitura das configuracoes
		scanf("%d %d %d", &memorySize, &pageSize, &setSize);


		instructions = (int*)malloc(setSize*sizeof(int));

		//leitura dos acessos
		for(j=0; j<setSize; j++){
			scanf("%d", &(instructions[j]));
		}


		createFifoMemory(&fifo,memorySize, pageSize);
		pageDistance = processFifoInstructions(&fifo, instructions, setSize, pageSize);
		printf("%d ", fifo.pageFaults);
		freeFifoMemory(&fifo);



		createLruMemory(&lru,memorySize, pageSize);
		stackDistance = processLruInstructions(&lru, instructions, setSize, pageSize);
		printf("%d ", lru.pageFaults);
		freeLruMemory(&lru);



		createLfuMemory(&lfu,memorySize,pageSize);
		processLfuInstructions(&lfu, instructions, setSize, pageSize);
		printf("%d ", lfu.pageFaults);
		freeLfuMemory(&lfu);


		createMruMemory(&mru,memorySize,pageSize);
		processMruInstructions(&mru, instructions, setSize, pageSize);
		printf("%d ", mru.pageFaults);
		freeMruMemory(&mru);


		printf("\n");

		for(j=0; j<(setSize-1); j++){
			printf("%d ", pageDistance[j]);
		}
		printf("\n");


		for(j=0; j<setSize; j++){
			printf("%d ", stackDistance[j]);
		}


		free(instructions);
		printf("\n");

	}










	/*
	printf("Array lido:\n");
	for(i=0; i<setSize; i++){
		printf("%d ", instructions[i]);
	}
	printf("\n\n");
	*-/

	createLruMemory(&lru, tamMemoria, tamPagina);
	int* stackDistance;

	stackDistance = processLruInstructions(&lru, instructions, setSize, tamPagina);

	printf("O numero de page faults foi de: %d\n", lru.pageFaults);

	printf("Dis. de pilha:\n");
	for(i=0; i<setSize; i++){
		printf("%d ", stackDistance[i]);
	}
	printf("\n");
	*/



	/*
	//-*********************************************-/

	//-
	puts("!!!Hello World!!!"); // prints !!!Hello World!!!


	//-----------PAGE MANIPULATIONS OK--------------
	Page pagina;
	pagina = createPage(4);
	loadPage(&pagina,4);
	printPage(pagina);
	//----------------------------------------------

	//-----------QUEUE MANIPULATIONS OK--------------
	Page pagina2;
	pagina2 = createPage(4);
	loadPage(&pagina2,10);

	List fila;
	setListEmpty(&fila);




	listInsertElement(&fila, pagina);
	listInsertElement(&fila, pagina2);
	printf("Attempting to print list:\n");
	printList(fila);
	printf("Imprimiu\n\n");

	backToLast(&fila, pagina);
	printf("Attempting to print list again:\n");
	printList(fila);
	*/

	return EXIT_SUCCESS;
}
