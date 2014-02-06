#ifndef DRONE_H
#define DRONE_H

#include <babcode.h>

#include "../../../common/include/desktopapp.h"

#include "droneprotocol.h"

typedef struct _ack_packet_
{
    UInt8 from;
    UInt8 to;
    DroneCmd command;
    DroneCmdResult result;
    UInt16  sizeOfNextPacket;
} AckPacket;

class Drone
{
public:
    Drone();
    ~Drone();

    void connect();
    bool connected();

    bool requestLog(QString & string);

    bool write(UInt16 address, UInt8* buffer, UInt16 size);

    UInt16 read(UInt16 address, UInt8* buffer);


    AckPacket*  ackPacket();
    void extractContent(UInt8* buffer, UInt32 size);


private:
    ByteStream*     mInput;
    ByteStream*     mOutput;

    bool isOpen;

    AckPacket* mAck;

    UInt8           mLog[512];


    void buildDefaultHeader(DroneCmd command, UInt16 sizeIWantForNextPacket);
    void buildEndOfHeader();
    bool sendHeader();

    bool receiveAck(UInt32 sizeToReceive);
    bool extractAck();
};

#endif // Drone
