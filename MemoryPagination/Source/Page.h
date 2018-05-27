/*
 * Page.h
 *
 *  Created on: 08/09/2014
 *      Author: viniciusoliveira
 */

#ifndef PAGE_H_
#define PAGE_H_

//-----------------------------------------------------------------------------------------
typedef struct{
	long int* page;
	int pageID;
	int length;
	int max_size;
	int accesses;
}Page;

//-----------------------------------------------------------------------------------------
Page createPage(int);
void loadPage(Page*, int);
void printPage(Page);


#endif /* PAGE_H_ */
