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

    bool run(DroneCmd command);
    bool runWithSize(DroneCmd command, UInt16 size);

    bool request(DroneCmd command, UInt32 requestByteSize);

    bool writeToMemory(UInt16 addr, UInt8* buffer, UInt16 size);

    AckPacket*  ackPacket();

    void extractContent(UInt8* buffer, UInt32 size);

private:
    ByteStream*     mInput;
    ByteStream*     mOutput;

    bool isOpen;

    AckPacket* mAck;

    bool runFullCommand(DroneCmd command, UInt16 specificSize, UInt32 ackPacketSize);
    bool sendAndReceive(UInt32 ackPacketSize);
    void buildHeader(DroneCmd command, UInt16 size);
    bool extractAck();
};

#endif // Drone
