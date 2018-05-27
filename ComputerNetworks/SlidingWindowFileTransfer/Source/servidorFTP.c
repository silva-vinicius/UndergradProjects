

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "tp_socket.h"
#include "Packet.h"
#include "List.h"
#include <arpa/inet.h>
#define MAXTIMER 2


//----------------------------------------------------------------------------------------------------------------------
//funcao para tratar erros em chamadas de sistema
void error(char* msg){
    perror(msg);
    exit(1);
}


//----------------------------------------------------------------------------------------------------------------------
void clearReceivingBuffer(int socket, int pseudoBuffLen, so_addr* cliAddr ){

    int readBytes=0;
    char* fakeBuffer = (char*)malloc(100*pseudoBuffLen*sizeof(char));

    while(readBytes>=0){
        readBytes = tp_recvfrom(socket, fakeBuffer,100*pseudoBuffLen,cliAddr);
    }

    //at this point, there are no more bytes to read

};

//----------------------------------------------------------------------------------------------------------------------
void readArgs(int argc, char* argv[], int* port, int* buffer, int* windowSize){

    if (argc != 4){
        printf("Usage: %s <port> <buffer> <window size>", argv[0]);
        exit(0);
    }

    if(tp_init()<0){
        error("Erro na inicializacao da biblioteca do TP");
    }

    //reads the port number from command line
    *port = atoi((argv)[1]);

    //reads buffer size from command line
    *buffer = atoi((argv)[2]);

    *windowSize = atoi((argv)[3]);
}

//----------------------------------------------------------------------------------------------------------------------
char* receiveFileName(int mtu, int sockfd, so_addr* cliAddr, int pseudoBuffLen){
	
	//we are not allowing timeouts for now
	struct timeval timeout = {0, 0};
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(struct timeval));

    char* fileName=NULL;
    int flagFileNameReceived=0;

    int f_recv_size=0;

    Packet* requestPacket=NULL;

    //allocating space for us to receive the requestPacket containing the file name.
    char* receivingSerializedPckt = (char*)malloc(pseudoBuffLen+14*sizeof(char));


    while(!flagFileNameReceived){

        //Receives a request
        f_recv_size = tp_recvfrom(sockfd, receivingSerializedPckt, pseudoBuffLen+14,  cliAddr);

        if(f_recv_size>0) {
            requestPacket = desserializePacket(receivingSerializedPckt, pseudoBuffLen);

            //we received an intact packet
            if (requestPacket != NULL  && requestPacket->packet_kind == (char) (3) &&
                requestPacket->sq_no == (char) (0)){

                fileName = (char*)malloc(requestPacket->validBytes * sizeof(char));

                memcpy(fileName, requestPacket->data, requestPacket->validBytes);

                flagFileNameReceived = 1;
            }

        }
    }


    int fileNameReceivedAcked=0;
    Packet* ackPacket=NULL;
    char* sendingSerializedPacket=NULL;

    //making sure that our "receiving buffer" doesnt contain invalid data
    bzero(receivingSerializedPckt, pseudoBuffLen+14*sizeof(char));

    while(!fileNameReceivedAcked){

        ackPacket = getNewPacket(0,0,pseudoBuffLen,NULL,0);

        sendingSerializedPacket = serializePacket(*ackPacket,pseudoBuffLen);
        tp_sendto(sockfd,sendingSerializedPacket,pseudoBuffLen+14,cliAddr);

        f_recv_size = tp_recvfrom(sockfd, receivingSerializedPckt, pseudoBuffLen+14,  cliAddr);

        if(f_recv_size>0) {
            ackPacket = desserializePacket(receivingSerializedPckt, pseudoBuffLen);

            if (ackPacket != NULL  && ackPacket->packet_kind == (char) (0) &&
                ackPacket->sq_no == (char) (0)){

                fileNameReceivedAcked=1;

            }
        }
    }

    free(sendingSerializedPacket);
    free(ackPacket);
    free(receivingSerializedPckt);

    if(requestPacket!=NULL  ){
        free(requestPacket->data);
        free(requestPacket);
    }

    return fileName;
}

//----------------------------------------------------------------------------------------------------------------------
void sendFile(int comSckt, so_addr* client_addr,  char* fileName, int pseudoBuffLen, int windowSize){


    long long int base=1;
    long long int nextseqnum=1;

    //sets a timeout for acks receival.
    struct timeval timeout = {1, 0};
    setsockopt(comSckt, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(struct timeval));

    clearReceivingBuffer(comSckt,pseudoBuffLen,client_addr);

    //indicates how many acknowledgement bytes we've read.
    int recv_size=0;

    int actualBuffLen = pseudoBuffLen+14;

    List sndPacket;
    initList(&sndPacket,windowSize);

    Packet* sendingPacket=NULL;
    Packet* receivingPacket = NULL;
    char* serializedSendingPacket;
    char* serializedReceivingPacket = (char*)malloc(actualBuffLen*sizeof(char));

    //opens the file
    FILE* requestedFile = fopen(fileName, "rb");

	if(requestedFile==NULL){
		error("Houve um problema ao abrir o arquivo requisitado\n");	
	}

    //finds out how many bytes we need to send
    fseek(requestedFile,0L,SEEK_END);
    long fileDim = ftell(requestedFile);

    //rewinding the file
    fseek(requestedFile,0L, SEEK_SET);
    long int totalReadBytes=0;


    char* currentData = NULL;
    size_t nReadBytes=0;

    struct timespec referenceTime;
    struct timespec now;

    int packetType;
    int timer_running=0;
    int flagLastPacketRemoved=0;
    int flagCanReadNext=1;
    int flagNewDataReady=0;
    int numClosingTries=0;





    while(numClosingTries<20){

        if(sndPacket.size==0 && flagLastPacketRemoved){
            numClosingTries++;
        }

        if(flagCanReadNext){
            currentData = (char*)malloc(pseudoBuffLen * sizeof(char));
            (nReadBytes = fread(currentData,  1, pseudoBuffLen, requestedFile));
            totalReadBytes += nReadBytes;
            if(nReadBytes>0){
                flagNewDataReady=1;
            }
        }

        if(flagNewDataReady){

            //this means we've read the entire file
            if(totalReadBytes == fileDim){

                packetType=2;

            }else{
                packetType=1;
            }

            //printf("nextSeqNum: %d Base: %d, window size: %d\n", nextseqnum, base, windowSize);
            if(nextseqnum < (base + windowSize)){
                //printf("bextseqNum < base + windowSize, condicao verdadeira\n\n");
                sendingPacket= getNewPacket((char)packetType, nextseqnum, pseudoBuffLen, currentData,(int)nReadBytes);
                insertElement(&sndPacket, *sendingPacket);
                serializedSendingPacket = serializePacket(*sendingPacket,pseudoBuffLen);

                //printf("\nWe will send the packet of number %d\n", sendingPacket->sq_no);
                tp_sendto(comSckt, serializedSendingPacket, actualBuffLen, client_addr);

                free(currentData);
                currentData=NULL;

                if(base==nextseqnum){
                    timer_running=1;
                    clock_gettime(CLOCK_MONOTONIC_RAW, &referenceTime);

                }
                nextseqnum++;

                //the new data is being processed, so it's not new anymore.
                flagNewDataReady=0;

                //we are ready to receive new data
                if(totalReadBytes < fileDim){
                    flagCanReadNext=1;
                }else{
                    flagCanReadNext=0;
                }

            }else{
                //we refuse this data for now, but we do know that we have more data to send
                flagCanReadNext=0;
                flagNewDataReady=1;
            }

        }

        clock_gettime(CLOCK_MONOTONIC_RAW, &now);

        int elapsedSeconds = (int) (now.tv_sec - referenceTime.tv_sec);

        if(timer_running && elapsedSeconds >= MAXTIMER){
            //printf("\nTIMEOUT on server\n\n");
            clock_gettime(CLOCK_MONOTONIC_RAW, &referenceTime);

            int i=0;
            for(i=0; i<sndPacket.size; i++){
                sendingPacket = getElementByKey(&sndPacket, base+i);
                serializedSendingPacket = serializePacket(*sendingPacket,pseudoBuffLen);

                //printf("\nWe will send the packet of number %d\n", sendingPacket->sq_no);
                tp_sendto(comSckt,serializedSendingPacket, actualBuffLen, client_addr );

                if(sendingPacket!=NULL){
                    if(sendingPacket->data!=NULL){
                        free(sendingPacket->data);
                    }
                    free(sendingPacket);
                }
                if(serializedSendingPacket!=NULL){
                    free(serializedSendingPacket);
                }

            }
        }


        recv_size = tp_recvfrom(comSckt, serializedReceivingPacket, actualBuffLen, client_addr);

        if (recv_size > 0) {
            receivingPacket = desserializePacket(serializedReceivingPacket, pseudoBuffLen);

            if (receivingPacket != NULL && receivingPacket->packet_kind == 0) {
                base = receivingPacket->sq_no + 1;
                removeAllWithSeqLessThan(&sndPacket, base, &flagLastPacketRemoved, windowSize);

                if (base == nextseqnum) {
                    timer_running = 0;
                } else {

                    clock_gettime(CLOCK_MONOTONIC_RAW, &referenceTime);
                    timer_running = 1;

                }
            }

            if (receivingPacket != NULL && receivingPacket->packet_kind == 4) {
                sendingPacket = getNewPacket(0, 0, pseudoBuffLen, NULL, 0);
                serializedSendingPacket = serializePacket(*sendingPacket, pseudoBuffLen);
                tp_sendto(comSckt, serializedSendingPacket, actualBuffLen, client_addr);
                break;
            }
        }

    }

}

//----------------------------------------------------------------------------------------------------------------------


int main(int argc, char* argv[]) {

    //reading user arguments:
    int portNumber, pseudoBuffLen, windowSize;

    readArgs(argc, argv, &portNumber, &pseudoBuffLen, &windowSize);

    if(tp_init()<0){
        error("Erro na inicializacao da biblioteca do TP");
    }


    int mtu = tp_mtu();

    if(pseudoBuffLen+14 > mtu){
        printf("O tamanho do buffer nao pode ser maior que: %d\n", mtu-14);
        exit(1);
    }

    //creates the socket the server will listen for requests
    int sockfd = tp_socket((unsigned short)portNumber);

    //represents the client's address. We will set this variable when the client makes contact.
    so_addr* cliAddr =(so_addr*)malloc(sizeof(struct sockaddr_in));


    int i=0;
    while(i<15){
		char* requestedFileName = receiveFileName(mtu, sockfd, cliAddr, pseudoBuffLen);

    	sendFile(sockfd,cliAddr,requestedFileName,pseudoBuffLen,windowSize);

    	free(requestedFileName);
		
		i++;
	}

    
    printf("server finished\n");


    return 0;
}

