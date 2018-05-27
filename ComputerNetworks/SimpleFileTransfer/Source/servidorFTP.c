#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

//http://www.geeksforgeeks.org/socket-programming-cc/
//https://codereview.stackexchange.com/questions/43914/client-server-implementation-in-c-sending-data-files

//funcao para tratar erros em chamadas de sistema
void error(char* msg){
    perror(msg);
    exit(1);
}

//----------------------------------------------------------------------------------
void sendFile(int comSckt, char* fileName, int buffLen){


    FILE* requestedFile;

    char* trvlBuffer;

    trvlBuffer = (char*) calloc(buffLen, sizeof(char));

    requestedFile = fopen(fileName, "rb");

    if(requestedFile==NULL){
        printf("Arquivo %s nao encontrado.\n", fileName);
        return;
    }


//    printf("Transmissao do arquivo %s iniciada \n\n", fileName);

    int nReadBytes = 0;
    while ( (nReadBytes = fread(trvlBuffer,  1, buffLen, requestedFile))!=0){
        send(comSckt, trvlBuffer, nReadBytes, 0);
    }

    free(trvlBuffer);
    close(comSckt);
//    printf("Arquivo %s foi enviado\n", fileName);

}

//----------------------------------------------------------------------------------
int main(int argc, char* argv[]){

    //le a porta a ser escutada
    int portNumber = atoi((argv)[1]);

    //le o tamanho do buffer da linha de comando
    int buffLen = atoi((argv)[2]);


    int server_fd; //File descriptor do socket de boas vindas
    int com_socket; //Numero que representa o socket de comunicacao

    struct sockaddr_in address; //endereco onde o servidor pode ser encontrado na internet

    int addrLen= sizeof(address);

    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0 ){
        error("Falha na criacao do socket");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port=htons(portNumber);


    //"plugar"o socket a porta a ser escutada
    if( bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0 ){

        error("Falha no bind do socket");
    }

    //escutar por requisicoes ao socket de boas vindas:
    if(listen(server_fd, 3) < 0){
        error("Falha ao escutar o socket");
    }

    int respondedRequests=0;

    char* fileName = (char*)calloc(sizeof(char), 100);

    while(respondedRequests<30){
        if((com_socket = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrLen)) < 0 ){

            error("Falha ao aceitar conexao");
        }

        read( com_socket, fileName, 100);

        //ler o arquivo e mandar os blocos individualmente.
        sendFile(com_socket, fileName, buffLen);

        respondedRequests++;
    }
    free(fileName);
    close(server_fd);

    return 0;
}