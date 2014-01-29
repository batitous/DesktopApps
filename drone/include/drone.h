#ifndef DRONE_H
#define DRONE_H

#include <babcode.h>

#include "../../../common/include/desktopapp.h"

#include "droneprotocol.h"


class Drone
{
public:
    Drone();
    ~Drone();

    void connect();
    void send(DroneCmd command);

private:
    ByteStream*     mInput;
    ByteStream*     mOutput;

    bool isOpen;

    UInt8       mAckFrom;
    UInt8       mAckTo;
    DroneCmd    mAckCommand;
    DroneCmdResult mAckResult;

    void buildHeader(DroneCmd command);
    bool extractAck();

};

#endif // Drone
