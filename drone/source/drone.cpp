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

    mAck = new AckPacket();
}

Drone::~Drone()
{
    free(mInput->buffer);
    free(mInput);

    free(mOutput->buffer);
    free(mOutput);
}

AckPacket*  Drone::ackPacket()
{
    return mAck;
}

bool Drone::connected()
{
    return isOpen;
}

void Drone::connect()
{
    if (isOpen==false)
    {
        if (RadioUart::instance()->open( DesktopApp::portComFromSettings())==false)
        {
            qDebug() << "Drone::connect failed to open uart: " << DesktopApp::portComFromSettings();
            return;
        }

        isOpen = true;
    }
    else
    {
        RadioUart::instance()->close();
        isOpen = false;
    }
}

bool Drone::send(DroneCmd command, UInt32 ackPacketSize)
{
    buildHeader(command);

    UInt32 size = getByteStreamSize(mOutput);

//    qDebug() << "Drone::send: size:"<< size;

    if (RadioUart::instance()->write(mOutput->buffer, size)==false)
    {
        qDebug() << "RadioUart::instance()->write  failed!";
        return false;
    }

    resetByteStream(mInput);

    qDebug() << "===> Read: want" << ackPacketSize << " bytes.";

    if (RadioUart::instance()->read(mInput->buffer, ackPacketSize)!=ackPacketSize)
    {
        qDebug() << "RadioUart::instance()->read failed !";
        return false;
    }

    if (extractAck()==false)
    {
        return false;
    }

    qDebug() << "Drone::send received ack from" << mAck->from <<
                " Result:" << mAck->result <<
                " for Command:" << mAck->command <<
                " Size:" << mAck->sizeOfNextPacket;

    return true;
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

/*    for(int i=0 ; i < DRONE_PK_HEADER_SIZE; i++)
    {
        printf("%x ", mOutput->buffer[i]);
    }
*/
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

    mAck->from = GET_SENDER(address);
    mAck->to = GET_RECEIVER(address);
    mAck->command = (DroneCmd)read1FromByteStream(mInput);
    mAck->result = (DroneCmdResult)read1FromByteStream(mInput);
    mAck->sizeOfNextPacket = read2FromByteStream(mInput);

    return true;
}

void Drone::extractContent(UInt8* buffer, UInt32 size)
{
    readBufferFromByteStream(mInput, buffer, size);
}
