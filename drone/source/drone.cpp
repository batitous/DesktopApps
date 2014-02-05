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

bool Drone::run(DroneCmd command)
{
    return runFullCommand(command, 0, DRONE_PK_ACK_SIZE);
}

bool Drone::runWithSize(DroneCmd command, UInt16 size)
{
    return runFullCommand(command, size, DRONE_PK_ACK_SIZE);
}

bool Drone::request(DroneCmd command, UInt32 requestByteSize)
{
    return runFullCommand(command, 0, requestByteSize);
}

bool Drone::runFullCommand(DroneCmd command, UInt16 specificSize, UInt32 ackPacketSize)
{
    buildHeader(command, specificSize);
    emptyHeaderContent();

    return sendAndReceive(ackPacketSize);
}

bool Drone::writeToMemory(UInt16 addr, UInt8* buffer, UInt16 size)
{
    resetByteStream(mOutput);
    write2ToByteStream(mOutput, addr);
    writeBufferToByteStream(mOutput, buffer, size);

    return sendAndReceive(DRONE_PK_ACK_SIZE);
}

bool Drone::prepareReadFromMemory(UInt16 addr)
{
    buildHeader(DRONE_CMD_MEMORY, 2);
    write2ToByteStream(mOutput, addr);

    qDebug() << "read size command:" << getByteStreamSize(mOutput);

    for(int i=10 ; i < DRONE_PK_HEADER_SIZE; i++)
    {
        write1ToByteStream(mOutput, 0);
    }

    return sendAndReceive(DRONE_PK_ACK_SIZE);
}

bool Drone::sendAndReceive(UInt32 ackPacketSize)
{
    UInt32 size = getByteStreamSize(mOutput);

    if (RadioUart::instance()->write(mOutput->buffer, size)==false)
    {
        qDebug() << "Drone::sendAndReceive: write failed (" << size << " bytes to send) !";
        return false;
    }

    resetByteStream(mInput);

    if (RadioUart::instance()->read(mInput->buffer, ackPacketSize)!=ackPacketSize)
    {
        qDebug() << "Drone::sendAndReceive: failed to read " << ackPacketSize << " bytes.";
        return false;
    }

    if (extractAck()==false)
    {
        qDebug() << "Drone::sendAndReceive failed to extract ack from packet!";
        return false;
    }

    qDebug() << "Drone::runFullCommand received ack from" << mAck->from <<
                " Result:" << mAck->result <<
                " for Command:" << mAck->command <<
                " Next bytes:" << mAck->sizeOfNextPacket;

    return true;
}

void Drone::buildHeader(DroneCmd command, UInt16 size)
{
    UInt8 address = SET_ADDRESS(MASTER, DRONE);

    resetByteStream(mOutput);
    write4ToByteStream(mOutput, DRONE_PK_MAGIC);
    write1ToByteStream(mOutput, address);
    write1ToByteStream(mOutput, command);
    write2ToByteStream(mOutput, size);
}

void Drone::emptyHeaderContent()
{
    //empty content
    for(int i=8 ; i < DRONE_PK_HEADER_SIZE; i++)
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
