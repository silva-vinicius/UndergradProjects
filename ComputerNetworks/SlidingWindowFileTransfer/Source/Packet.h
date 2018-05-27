//
// Created by vinicius on 21/11/17.
//

#ifndef SERVER_PACKET_H
#define SERVER_PACKET_H




typedef struct packet{
    char packet_kind; //ACK:0, regular data package:1, last package in a transmission:2, file name packet: 3, file ack: 4

    /*Sequence number:
     * If packet_kind = 0, sq_no means the packet's acknowledgment number.
     * If packet_kind = 1 or 2, sq_no means the actual packet's sequence number
     */
    long long int sq_no;

    int validBytes;

    char *data;
}Packet;

//------------------------------------------------------------------------------
char getCheckSum(char* array, int length);


//----------------------------------------------------------------------------
Packet* getNewPacket(char packet_kind, long long int sq_no, int pseudoBuffLen, char* data, int dataLen);

//----------------------------------------------------------------------------
char* serializePacket(Packet packet, int pseudoBufferSize);

//----------------------------------------------------------------------------
Packet* desserializePacket(char* serializedPacket, int pseudoBufferSize);


#endif //SERVER_PACKET_H
