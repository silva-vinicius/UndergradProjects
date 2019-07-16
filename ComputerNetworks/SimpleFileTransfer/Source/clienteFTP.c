#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>


//http://www.geeksforgeeks.org/socket-programming-cc/

//CLIENT
void error(const char* msg){
    perror(msg);
    exit(1);
}

//---------------------------------------------------------------------------------
int receiveFile(char* fileName, int comSckt, int buffLen){

    char* buffer;
    buffer = (char*)calloc(buffLen, sizeof(char));

    FILE* receivedFile = fopen(fileName, "wb");

    int totalRcvdBytes=0;
    
    int itrRcvdBytes=0;

    //receives <buffLen> bytes until there are no more data to be received
    while((itrRcvdBytes = recv(comSckt,buffer, buffLen, 0)) > 0){
        totalRcvdBytes+=itrRcvdBytes;
        fwrite(buffer, sizeof(char), itrRcvdBytes, receivedFile);
    }

    fclose(receivedFile);
    free(buffer);

    return totalRcvdBytes;
}

//---------------------------------------------------------------------------------
int main(int argc, char* argv[]){

    struct sockaddr_in serverAddr;


    //Reading input from command line
    char* serverIP = (argv)[1];
    int serverPort = atoi((argv)[2]);
    char* requestedFile = (argv)[3];
    int buffLen = atoi((argv)[4]);

    int com_socket=0;

    //creates a TCP socket:
    if( (com_socket = socket(AF_INET, SOCK_STREAM, 0))  < 0 ){

        error("Erro na criacao do socket");
    }

    memset(&serverAddr, '0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);


    if(inet_pton(AF_INET, serverIP, &serverAddr.sin_addr)<=0){
        error("Endereco do servidor invalido");
    }

    //Structs used to store the times of beginning and end of the transmission.
    struct timespec startTime, endTime;

    //reads the OS's clock time before requesting the file.
    clock_gettime(CLOCK_MONOTONIC_RAW, &startTime);

    if(connect(com_socket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) <0){
        error("It was not possible to connect to the server");
    }

    send(com_socket, requestedFile, strlen(requestedFile), 0);


    int bytesReceived = receiveFile(requestedFile, com_socket, buffLen);


    //reads the OS's clock time after receiving the file.
    clock_gettime(CLOCK_MONOTONIC_RAW, &endTime);


    //elapsedTime in milliseconds.
    //1 second = 1000 millis
    //1 milli = 1000000 nanosecs
    u_int64_t elapsedTime = (endTime.tv_sec - startTime.tv_sec)*1000 + (endTime.tv_nsec - startTime.tv_nsec)/1000000;

    double timeSeconds = ((double)elapsedTime / (double)1000);


    printf("Buffer %5u byte(s), %10.2f kbps (%5u bytes in %3u.%06u s)\n",
           buffLen,
           ((bytesReceived/1000) / timeSeconds ),
           bytesReceived,
           (elapsedTime/1000),
           ((elapsedTime%1000)*1000)); //multiplying by 1000 so that the number will be in the first decimal digits

    return 0;

}
