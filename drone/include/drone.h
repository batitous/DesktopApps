#ifndef DRONE_H
#define DRONE_H

#include <babcode.h>

#include "../../../common/include/desktopapp.h"

#include "droneprotocol.h"

typedef struct _ack_packet_
{
    uint8_t from;
    uint8_t to;
    DroneCmd command;
    DroneCmdResult result;
    uint16_t  sizeOfNextPacket;
} AckPacket;

class Drone
{
public:
    Drone();
    ~Drone();

    void connect();
    bool connected();

    bool requestLog(QString & string);

    bool write(uint16_t address, uint8_t* buffer, uint16_t size);

    uint16_t read(uint16_t address, uint8_t* buffer);


    AckPacket*  ackPacket();
    void extractContent(uint8_t* buffer, uint32_t size);


private:
    ByteStream*     mInput;
    ByteStream*     mOutput;

    bool isOpen;

    AckPacket* mAck;

    uint8_t           mLog[512];


    void buildDefaultHeader(DroneCmd command, uint16_t sizeIWantForNextPacket);
    void buildEndOfHeader();
    bool sendHeader();

    bool receiveAck(uint32_t sizeToReceive);
    bool extractAck();
};

#endif // Drone
