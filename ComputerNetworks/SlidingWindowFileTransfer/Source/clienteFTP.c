#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>s
#include "tp_socket.h"
#include "Packet.h"

//----------------------------------------------------------------------------------------------------------------------
//Handling errors in system calls
void error(char* msg){
    perror(msg);
    exit(1);
}

//----------------------------------------------------------------------------------------------------------------------
/*
 * returns 0 if reception timed out at first packet
 * returns 1 if reception was successfully completed
 */
int receiveFile(FILE* recvdFile, int com_sckt, so_addr* serverAddr, int pseudoBuffLen, int flagInit){

    if(flagInit){

        struct timeval timeout = {1, 0};
        setsockopt(com_sckt, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(struct timeval));
    }

    int bytesReceived=0;

    Packet* receivingPacket;
    char* serializedRecvPacket = (char*)malloc((pseudoBuffLen+14)*sizeof(char));

    int expectedSeqNum=1;

    int flagLastPacketDelivered=0;
    int packetsReceived=0;

    int readBytes=0;

    Packet* ackPacket;
    char* serializedSendingPacket;

    int lastPacket=0;

    while(!flagLastPacketDelivered){

        //Packets containing data
        readBytes = tp_recvfrom(com_sckt, serializedRecvPacket, pseudoBuffLen+14, serverAddr);

        bytesReceived+=readBytes;

        if(readBytes>0){
            packetsReceived++;
            receivingPacket = desserializePacket(serializedRecvPacket, pseudoBuffLen);


            if(receivingPacket!=NULL && (receivingPacket->packet_kind==(char)1 || receivingPacket->packet_kind==(char)2) && receivingPacket->sq_no==expectedSeqNum){
                //we received a correct packet and we should proceed with the transmission

                if(receivingPacket->packet_kind==2){
                    //we are delivering the last packet
                    flagLastPacketDelivered=1;
                }

                //deliver data
                fwrite(receivingPacket->data, sizeof(char), receivingPacket->validBytes, recvdFile);


                lastPacket = expectedSeqNum;
                expectedSeqNum++;

            }else{


                if(packetsReceived==1 && receivingPacket==NULL){
                    //first packet is corrupt. Send the request again
                    return 0;
                }

            }

            //we ack whichever packet we receive, but always informing the last packet we received correctly
            //printf("\nWe are acking the packet of number %d\n", lastPacket);
            ackPacket = getNewPacket(0, lastPacket, pseudoBuffLen, NULL, 0);
            serializedSendingPacket = serializePacket(*ackPacket, pseudoBuffLen);
            tp_sendto(com_sckt,serializedSendingPacket,pseudoBuffLen+14, serverAddr );
            free(serializedSendingPacket);
        }else{

            //we didn't receive anything in this iteration

            //if we don't receive anything in the first iteration, we return and send the request again
            if(packetsReceived==0){
                return 0;
            }
        }
    }

    //we inform the server that we are done with this file
    Packet* fileAckPacket;

    int numTries=0;
    fileAckPacket = getNewPacket(4, lastPacket, pseudoBuffLen, NULL, 0);
    serializedSendingPacket = serializePacket(*fileAckPacket, pseudoBuffLen);

    while(numTries<20){

        numTries++;

        tp_sendto(com_sckt,serializedSendingPacket,pseudoBuffLen+14, serverAddr );

        readBytes = tp_recvfrom(com_sckt, serializedRecvPacket, pseudoBuffLen+14, serverAddr);
        bytesReceived+=readBytes;

        if(readBytes>0){
            receivingPacket = desserializePacket(serializedRecvPacket, pseudoBuffLen);

            if(receivingPacket!=NULL && receivingPacket->packet_kind==0){
                break;
            }

        }
    }

    free(serializedRecvPacket);

    return bytesReceived;
}

//----------------------------------------------------------------------------------------------------------------------
void readArgs(int argc, char* argv[], char** serverAddress, int* port, int* buffer, int* windowSize, char** fileName){


    if (argc != 6){
        printf("Usage: %s <server address> <server port> <file name> <buffer size> <window size>", argv[0]);
        exit(0);
    }

    if(tp_init()<0){
        error("Could not initialize the courseworks given library");
    }

    //reads the server address in the format "xxx.xxx.xxx.xxx"
    *serverAddress = (char*) malloc(strlen(argv[1])*sizeof(char));
    strcpy(*serverAddress, argv[1]);

    //reads the port number from command line
    *port = atoi((argv)[2]);

    //reads buffer size from command line
    *buffer = atoi((argv)[4]);

    if((*buffer)<strlen(argv[3])){
        error("The buffer must be big enough to accomodate the file name string");
    }

    *fileName = (char*)malloc(strlen(argv[3])*sizeof(char));
    strcpy(*fileName, argv[3]);



    *windowSize = atoi((argv)[5]);


}

//----------------------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[]) {


    char* serverIP;
    int serverPort;
    char* fileName;
    int pseudoBuffLen;
    int windowSize;

    readArgs(argc, argv, &serverIP, &serverPort, &pseudoBuffLen, &windowSize, &fileName);

    FILE* requestedFile = fopen(fileName, "wb");

    if(tp_init()<0){
        error("Could not initialize the courseworks given library");
    }


    int mtu = tp_mtu();

    if(pseudoBuffLen+14>mtu){
        printf("Error. Buffer size cannot be larger than %d\n", mtu-14);
        exit(1);
    }

    so_addr* serverAddr = (so_addr*)malloc(sizeof(so_addr));

    if(tp_build_addr(serverAddr, serverIP, serverPort)<0){
        error("It was not possible to build the servers address");
    }

    int com_sckt = tp_socket(0);

    //create the packet the will carry data to server. Initially, it is the request
    Packet* requestPacket = getNewPacket((char)(3),(char)(0),pseudoBuffLen,fileName, strlen(fileName));

    //we are doing this to avoid memory leaks
    char* serializedPacket = serializePacket(*requestPacket, pseudoBuffLen);

    int transmissionFinished=0;

    int flagInitSocket=1;

    //Structs used to store the transmission beginning and end times
    struct timespec startTime, endTime;

    //Stores the OS's time before requesting the file
    clock_gettime(CLOCK_MONOTONIC_RAW, &startTime);

    int bytesReceived;

    while(!transmissionFinished){

        tp_sendto(com_sckt, serializedPacket, pseudoBuffLen+14, serverAddr);

        bytesReceived = receiveFile(requestedFile, com_sckt, serverAddr, pseudoBuffLen, flagInitSocket);

        if(bytesReceived!=0){
            transmissionFinished=1;
        }
        flagInitSocket=0;
    }

    //Stores the OS's time after receiving the file
    clock_gettime(CLOCK_MONOTONIC_RAW, &endTime);

    //elapsedTime in milliseconds.
    //1 second = 1000 millis
    //1 milli = 1000000 nanosecs
    u_int64_t elapsedTime = (endTime.tv_sec - startTime.tv_sec)*1000 + (endTime.tv_nsec - startTime.tv_nsec)/1000000;

    double timeSeconds = ((double)elapsedTime / (double)1000);


    printf("Buffer = %5u byte(s), %10.2f kbps (%5u bytes em %3u.%06u s)\n",
           pseudoBuffLen,
           ((bytesReceived/1000) / timeSeconds ),
           bytesReceived,
           (elapsedTime/1000),
           ((elapsedTime%1000)*1000)); //Multiplying by 1000 so that the number is displayed in the first digits

    free(fileName);
    free(serverIP);
    free(serializedPacket);
    fclose(requestedFile);

    printf("Program finished!\n");
    return 0;
}
