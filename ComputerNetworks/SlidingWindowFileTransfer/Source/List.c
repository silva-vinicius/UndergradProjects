#include <stdlib.h>
#include <string.h>
#include "List.h"

//-----------------------------------------------------------------------------------------
void initList(List* l, int windowSize){

    l->array = (Packet*)malloc(windowSize*sizeof(Packet));
    l->size=0;
}

//-----------------------------------------------------------------------------------------
void insertElement(List* l, Packet p){

    (l->size) ++;

//    l->array = (Packet*)realloc(l->array, ((l->size)*sizeof(Packet)));
    l->array[(l->size) - 1] = p;
}

//-----------------------------------------------------------------------------------------
void removeElementByKey(List* l, long long int k, int windowSize){

    int i=0;

    if(l->size==0){
        return;
    }

    Packet* newArray = (Packet*)malloc(windowSize*sizeof(Packet));

    int j=0;;

    while(i<l->size){

        if(l->array[i].sq_no != k){
            newArray[j] = l->array[i];
            j++;
        }else{
            //we free the data space occupied by the element we are removing
            free(l->array[i].data);
        }
        i++;
    }

    free(l->array);
    l->array = newArray;
    (l->size) --;
}

//-----------------------------------------------------------------------------------------
void removeAllWithSeqLessThan(List* l, long long max, int* flagLastPacketRemoved, int windowSize){

    int i=0;

    int originalSize = l->size;
    Packet* originalCollection = (Packet*)malloc(originalSize*sizeof(Packet));
    memcpy(originalCollection, l->array, originalSize*sizeof(Packet));

    for(i=0; i< originalSize; i++){

        if(originalCollection[i].sq_no < max){
            if(originalCollection[i].packet_kind == 2){
                *flagLastPacketRemoved=1;
            }
            removeElementByKey(l, originalCollection[i].sq_no, windowSize);
        }
    }

    free(originalCollection);
}

//-----------------------------------------------------------------------------------------
//returns a copy of the element with the specified key
Packet* getElementByKey(List* l, long long int k){

    Packet* p = (Packet*)malloc(sizeof(Packet));

    int i=0;

    while(i<(l->size)){

        if(l->array[i].sq_no == k){
            *p = l->array[i];
            p->data = (char*)malloc(l->array[i].validBytes*sizeof(char));
            memcpy(p->data,l->array[i].data, l->array[i].validBytes*sizeof(char));
            return p;
        }
        i++;
    }
    return NULL;
}
