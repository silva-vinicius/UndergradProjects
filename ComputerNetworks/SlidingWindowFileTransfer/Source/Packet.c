#include <stdlib.h>
#include <string.h>

#include "Packet.h"

//------------------------------------------------------------------------------
char getCheckSum(char* array, int length){

    char checksum = 0; // could be an int if preferred

    int x=0;
    for(x = 0; x < length; x++)
    {
        checksum += array[x];
    }

    //Perform bitwise inversion
    checksum=~checksum;
    //Increment
    checksum++;

    return checksum;

}


//----------------------------------------------------------------------------
Packet* getNewPacket(char packet_kind, long long int sq_no, int pseudoBuffLen, char* data, int dataLen){

    Packet* newPacket = (Packet*)malloc(sizeof(Packet));
    newPacket->packet_kind = packet_kind;
    newPacket->sq_no = sq_no;
    newPacket->data = NULL;

    if(data==NULL){
        newPacket->validBytes=0;
    }else{
        newPacket->validBytes = dataLen;
    }

    if(pseudoBuffLen>0){
        newPacket->data = (char*)malloc(pseudoBuffLen*sizeof(char));

        //we cant create a packet that carries more data than the theoretical buffer size
        if(pseudoBuffLen < dataLen){
            return NULL;
        }

        int i=0;

        for(i=0; i<dataLen; i++){
            (newPacket->data)[i] = data[i];
        }

    }else{
        return NULL;
    }

    return newPacket;
}

//----------------------------------------------------------------------------
char* serializePacket(Packet packet, int pseudoBufferSize){

    /* 1 byte to identify the packet kind,
     * 8 bytes to identify the sequence number,
     * 4 bytes to identify the amount of valid bytes
     * <pseudoBufferSize> bytes for the buffer itself
     * 1 byte for checksum
    */
    char* serializedPacket = (char*)malloc((14 + pseudoBufferSize)*sizeof(char));

    //coding the packet type
    serializedPacket[0] = (char)( ((int)packet.packet_kind) &7 );

    //coding the sequence number
    serializedPacket[1] = (char)( ( (packet.sq_no) >>56 ) &0xff);
    serializedPacket[2] = (char)( ( (packet.sq_no) >>48 ) &0xff);
    serializedPacket[3] = (char)( ( (packet.sq_no) >>40 ) &0xff);
    serializedPacket[4] = (char)( ( (packet.sq_no) >>32 ) &0xff);
    serializedPacket[5] = (char)( ( (packet.sq_no) >>24 ) &0xff);
    serializedPacket[6] = (char)( ( (packet.sq_no) >>16 ) &0xff);
    serializedPacket[7] = (char)( ( (packet.sq_no) >> 8 ) &0xff);
    serializedPacket[8] = (char)( ( (packet.sq_no)      ) &0xff);

    //coding the number of valid bytes in data
    serializedPacket[ 9] = (char)( ( (packet.validBytes) >>24 ) &0xff);
    serializedPacket[10] = (char)( ( (packet.validBytes) >>16 ) &0xff);
    serializedPacket[11] = (char)( ( (packet.validBytes) >> 8 ) &0xff);
    serializedPacket[12] = (char)( ( (packet.validBytes)& 0xff));

    //coding the actual transfer data
    int i=0;
    for(i=0; i<packet.validBytes; i++){
        serializedPacket[13+i] = packet.data[i];
    }

    //guarantees that all serialized packets have the same length
    while(i<pseudoBufferSize){
        serializedPacket[13+i]=(char)(3);
        i++;
    }

    //coding the checksum
    char checksum = getCheckSum(serializedPacket, 13+pseudoBufferSize);
    serializedPacket[13+pseudoBufferSize] = checksum;


    return serializedPacket;
}

//----------------------------------------------------------------------------
Packet* desserializePacket(char* serializedPacket, int pseudoBufferSize){

    //First thing to do is to check the checksum as if it doesnt match, we dont need to proceed.
    char readChecksum = serializedPacket[13+pseudoBufferSize];
    char calculatedChecksum = getCheckSum(serializedPacket, pseudoBufferSize + 13);

    //is the packet corrupt?
    if(readChecksum!=calculatedChecksum){
        return NULL;
    }
    Packet* p = (Packet*)malloc(sizeof(Packet));

    char packet_kind = serializedPacket[0];

    long long int seq_no = ( (((long long int)((unsigned char)serializedPacket[1]))<<56) |
                             (((long long int)((unsigned char)serializedPacket[2]))<<48) |
                             (((long long int)((unsigned char)serializedPacket[3]))<<40) |
                             (((long long int)((unsigned char)serializedPacket[4]))<<32) |
                             (((long long int)((unsigned char)serializedPacket[5]))<<24) |
                             (((long long int)((unsigned char)serializedPacket[6]))<<16) |
                             (((long long int)((unsigned char)serializedPacket[7]))<< 8) |
                             (((long long int)((unsigned char)serializedPacket[8]))));

    //teste

    int validBytes =     (  (((int)((unsigned char)serializedPacket[ 9]))<<24) |
                            (((int)((unsigned char)serializedPacket[10]))<<16) |
                            (((int)((unsigned char)serializedPacket[11]))<< 8) |
                            (((int)((unsigned char)serializedPacket[12]))));

    char* content=NULL;

    int i=0;

    int addslashZero=0;

    if(validBytes>=0){
        if(packet_kind==(char)3){
            //extra space for \0
            addslashZero=1;

        }

        content = (char*)malloc((sizeof(char)*validBytes) + addslashZero);
        bzero(content, (sizeof(char)*validBytes) + addslashZero);



        for(i=0;i<validBytes; i++){
            content[i] = serializedPacket[13+i];
        }

        if(packet_kind==(char)3) {
            content[i] = '\0';
        }

        if(validBytes==0){
            content = NULL;
        }

    }else{
        return NULL;
    }


    p->packet_kind = packet_kind;
    p->sq_no = seq_no;

    if(content!=NULL){
        p->data = (char*)malloc((sizeof(char)*validBytes) + addslashZero);
        memcpy(p->data, content, validBytes);
        free(content);
    }else{
        p->data=NULL;
    }


    p->validBytes = validBytes;

    return p;
}
