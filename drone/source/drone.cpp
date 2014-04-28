// Baptiste Burles, Kliplab, 2014

#include "../include/drone.h"

Drone::Drone()
{
    uint8_t* temp;

    temp = (uint8_t*)malloc(DRONE_STREAM_SIZE);
    mInput = newByteStream(temp);

    temp = (uint8_t*)malloc(DRONE_STREAM_SIZE);
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

void Drone::buildDefaultHeader(DroneCmd command, uint16_t sizeIWantForNextPacket)
{
    uint8_t address = SET_ADDRESS(MASTER, DRONE);

    resetByteStream(mOutput);
    write4ToByteStream(mOutput, DRONE_PK_MAGIC);
    write1ToByteStream(mOutput, address);
    write1ToByteStream(mOutput, command);
    write2ToByteStream(mOutput, sizeIWantForNextPacket);
}

void Drone::buildEndOfHeader()
{
    for(int i=getByteStreamSize(mOutput) ; i < DRONE_PK_HEADER_SIZE; i++)
    {
        write1ToByteStream(mOutput, 0);
    }
}

bool Drone::sendHeader()
{
    uint32_t size = getByteStreamSize(mOutput);

    if (RadioUart::instance()->write(mOutput->buffer, size)==false)
    {
        qDebug() << "Drone::sendHeader: write failed (" << size << " bytes to send) !";
        return false;
    }

    return true;
}

bool Drone::receiveAck(uint32_t sizeToReceive)
{
    resetByteStream(mInput);

    if (RadioUart::instance()->read(mInput->buffer, sizeToReceive)!=sizeToReceive)
    {
        qDebug() << "Drone::receiveAck: failed to read " << sizeToReceive << " bytes.";
        return false;
    }

    if (extractAck()==false)
    {
        qDebug() << "Drone::receiveAck failed to extract ack from packet!";
        return false;
    }

 /*   qDebug() << "Drone::receiveAck from" << mAck->from <<
                " Result:" << mAck->result <<
                " for Command:" << mAck->command <<
                " Next bytes:" << mAck->sizeOfNextPacket;
*/
    if (mAck->result != DRONE_CMD_RESULT_OK)
    {
        qDebug() << "Drone::receiveAck FAILED from" << mAck->from <<
                       " Result:" << mAck->result <<
                       " for Command:" << mAck->command <<
                       " Next bytes:" << mAck->sizeOfNextPacket;

        qDebug() << "Drone::receiveAck COMMAND FAILED ON DRONE!";
        return false;
    }

    return true;
}


bool Drone::requestLog(QString & string)
{
    buildDefaultHeader(DRONE_CMD_LOG_SIZE, 0);
    buildEndOfHeader();

    if (sendHeader()==false)
    {
        return false;
    }

    if (receiveAck(DRONE_PK_ACK_SIZE)==false)
    {
        return false;
    }

    uint16_t size = ackPacket()->sizeOfNextPacket;

    qDebug() << "==> Size of log: "<< size;

    waitMs(50);

    if (size != 0)
    {
        buildDefaultHeader(DRONE_CMD_LOG, 0);
        buildEndOfHeader();

        if (sendHeader()==false)
        {
            return false;
        }

        if (receiveAck( size + DRONE_PK_ACK_SIZE )==false)
        {
            return true;
        }

        memset(mLog, 0, 512);

        extractContent(mLog, ackPacket()->sizeOfNextPacket );

        string = QString((char *)mLog);
    }

    return true;
}

bool Drone::write(uint16_t address, uint8_t* buffer, uint16_t size)
{
    buildDefaultHeader(DRONE_CMD_MEMORY, size);
    buildEndOfHeader();

    if (sendHeader()==false)
    {
        return false;
    }

    if (receiveAck(DRONE_PK_ACK_SIZE)==false)
    {
        return false;
    }

    resetByteStream(mOutput);
    write2ToByteStream(mOutput, address);
    writeBufferToByteStream(mOutput, buffer, size);

    if (sendHeader()==false)
    {
        return false;
    }

    return receiveAck(DRONE_PK_ACK_SIZE);
}

uint16_t Drone::read(uint16_t address, uint8_t* buffer)
{
    buildDefaultHeader(DRONE_CMD_MEMORY, 2);
    write2ToByteStream(mOutput, address);
    buildEndOfHeader();

    if (sendHeader()==false)
    {
        return 0;
    }

    if (receiveAck(DRONE_PK_ACK_SIZE)==false)
    {
        return 0;
    }

    uint16_t size = ackPacket()->sizeOfNextPacket;

    buildDefaultHeader(DRONE_CMD_MEMORY,size);
    buildEndOfHeader();

    if (sendHeader()==false)
    {
        return 0;
    }

    if (receiveAck(size + DRONE_PK_ACK_SIZE)==false)
    {
        return 0;
    }

    size = ackPacket()->sizeOfNextPacket;
    extractContent(buffer, size );

    return size;
}

bool Drone::extractAck()
{
    uint32_t magic = read4FromByteStream(mInput);
    if (magic!=DRONE_PK_MAGIC)
    {
        qDebug() << "Drone::extractAck error: wrong magic packet " << magic;
        return false;
    }

    uint8_t address = read1FromByteStream(mInput);

    mAck->from = GET_SENDER(address);
    mAck->to = GET_RECEIVER(address);
    mAck->command = (DroneCmd)read1FromByteStream(mInput);
    mAck->result = (DroneCmdResult)read1FromByteStream(mInput);
    mAck->sizeOfNextPacket = read2FromByteStream(mInput);

    return true;
}

void Drone::extractContent(uint8_t* buffer, uint32_t size)
{
    readBufferFromByteStream(mInput, buffer, size);
}
