// Baptiste Burles, Kliplab, 2014

#include "../include/drone.h"

Drone::Drone()
{
    UInt8* temp;

    temp = (UInt8*)malloc(DRONE_STREAM_SIZE);
    mInput = newByteStream(temp);

    temp = (UInt8*)malloc(DRONE_STREAM_SIZE);
    mOutput = newByteStream(temp);

    isOpen = false;
}

Drone::~Drone()
{
    free(mInput->buffer);
    free(mInput);

    free(mOutput->buffer);
    free(mOutput);
}

void Drone::connect()
{
    if (isOpen==false)
    {
        if (RadioUart::instance()->open( DesktopApp::portComFromSettings())==false)
        {

            return;
        }

        isOpen = true;
    }
}

void Drone::send(DroneCmd command)
{

    buildHeader(command);

    UInt32 size = getByteStreamSize(mOutput);

    qDebug() << "Drone::send: size:"<< size;

    if (RadioUart::instance()->write(mOutput->buffer, size)==false)
    {
        qDebug() << "RadioUart::instance()->write  failed!";
        return;
    }

    resetByteStream(mInput);

    if (RadioUart::instance()->read(mInput->buffer, DRONE_PK_ACK_SIZE)!=DRONE_PK_ACK_SIZE)
    {
        qDebug() << "RadioUart::instance()->read failed !";
        return;
    }

    if (extractAck()==false)
    {
        return;
    }

    qDebug() << "Drone::send received ack from" << mAckFrom << " Result:" << mAckResult << " for Command:" << mAckCommand;


}

void Drone::buildHeader(DroneCmd command)
{
    UInt8 address = SET_ADDRESS(MASTER, DRONE);

    resetByteStream(mOutput);
    write4ToByteStream(mOutput, DRONE_PK_MAGIC);
    write1ToByteStream(mOutput, address);
    write1ToByteStream(mOutput, command);

    //empty content
    for(int i=6 ; i < DRONE_PK_HEADER_SIZE; i++)
    {
        write1ToByteStream(mOutput, 0);
    }
}

bool Drone::extractAck()
{
    UInt32 magic = read4FromByteStream(mInput);
    if (magic!=DRONE_PK_MAGIC)
    {
        qDebug() << "Drone::extractAck error: wrong magic packet " << magic;
        return false;
    }

    UInt8 address = read1FromByteStream(mInput);

    mAckFrom = GET_SENDER(address);
    mAckTo = GET_RECEIVER(address);

    mAckCommand = (DroneCmd)read1FromByteStream(mInput);

    mAckResult = (DroneCmdResult)read1FromByteStream(mInput);

    return true;
}
