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

    bool send(DroneCmd command, UInt32 ackPacketSize = DRONE_PK_ACK_SIZE);

    AckPacket*  ackPacket();

    void extractContent(UInt8* buffer, UInt32 size);

private:
    ByteStream*     mInput;
    ByteStream*     mOutput;

    bool isOpen;

    AckPacket* mAck;

    void buildHeader(DroneCmd command);
    bool extractAck();
};

#endif // Drone
