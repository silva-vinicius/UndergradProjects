//
// Created by vinicius on 21/11/17.
//

#ifndef SERVER_LIST_H
#define SERVER_LIST_H

#include "Packet.h"

typedef struct List{

    Packet* array;
    int size;
}List;


//-----------------------------------------------------------------------------------------
void initList(List* l, int windowSize);

//-----------------------------------------------------------------------------------------
void insertElement(List* l, Packet p);

//-----------------------------------------------------------------------------------------
void removeElementByKey(List* l, long long int k, int windowSize);

//-----------------------------------------------------------------------------------------
void removeAllWithSeqLessThan(List* l, long long max, int* flagLastPacketRemoved, int windowSize);

//-----------------------------------------------------------------------------------------
//returns a copy of the element with the specified key
Packet* getElementByKey(List* l, long long int k);

#endif //SERVER_LIST_H
