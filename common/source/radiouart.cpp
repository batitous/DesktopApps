// Baptiste Burles, Kliplab, 2014

#include "../include/radiouart.h"

#include <QtCore/QDebug>

#define SIZE_MASK               0x1F
#define FIRST_PACKET            0x40
#define END_OF_PACKET           0x20
#define ERROR_BIT               0x80

RadioUart* RadioUart::radioUart=0;


RadioUart* RadioUart::instance()
{
    if (radioUart==0)
    {
        radioUart = new RadioUart();
    }

    return radioUart;
}

RadioUart::RadioUart()
{
}

RadioUart::~RadioUart()
{
}

bool RadioUart::getUartByte(UInt8 * b)
{
    UInt32 timeout = 24;

    while (getByteFromUARTNoWait(b)!=0)
    {
        timeout--;

        if (timeout==0)
        {
            return false;
        }
    }

    return true;
}


bool RadioUart::uartWrite(UInt8 *buffer, UInt32 size)
{
    UInt32 result = sendBufferToUART(buffer, size);

    if (result!=UART_OK)
    {
        qDebug() << "RadioUart::uartWrite failed code " << result;
        return false;
    }

    return true;
}

UInt32 RadioUart::uartRead(UInt8 *buffer, UInt32 size)
{
    UInt32 counter;

    for( counter=0 ; counter != size; counter++)
    {
        if ( getUartByte(&buffer[counter])==false)
        {
            return counter;
        }
    }

    return counter;
}


bool RadioUart::open(const QString & specific)
{
    UInt8 b;
    UInt8 * comport = (UInt8 *)specific.toLatin1().constData();
    UInt32 result = initUART(comport, 115200);

    if (result!=UART_OK)
    {
        qDebug() << "RadioUart::open failed code " << result;
        return false;
    }

    // clean uart
    while (getByteFromUARTNoWait(&b)==0)
    {
    }

    return true;
}

bool RadioUart::write(UInt8 *buffer, UInt32 size)
{
    UInt32 pkSize = RADIO_BUFFER_SIZE-1;
    UInt32 pkNumber = size / pkSize;
    UInt32 remind = size - (pkNumber * pkSize);
    UInt32 i;
    UInt8* ptr;
    UInt8 flag;

    ptr = buffer;
    for (i=0; i < pkNumber; i++)
    {
        flag = 0;

        if (i==0)
        {
            flag = FIRST_PACKET;
        }

        if (remind==0 && i == (pkNumber-1))
        {
            flag |= END_OF_PACKET;
        }

        flag |= (pkSize & SIZE_MASK);

        linkBuffer[0] = flag;
        memcpy(&linkBuffer[1], ptr, pkSize);

        if (uartWrite(linkBuffer, RADIO_BUFFER_SIZE)==false)
        {
            return false;
        }

        ptr += pkSize;
    }

    if (remind!=0)
    {
        flag = 0;
        if (pkNumber == 0)
        {
            flag = FIRST_PACKET;
        }

        flag |= (remind & SIZE_MASK) | END_OF_PACKET;

        linkBuffer[0] = flag;
        memcpy(&linkBuffer[1], ptr, remind);

        if (uartWrite(linkBuffer, RADIO_BUFFER_SIZE)==false)
        {
            return false;
        }
    }

    return true;
}

UInt32 RadioUart::read(UInt8 *buffer, UInt32 size)
{
    UInt32 pkSize = RADIO_BUFFER_SIZE-1;
    UInt32 pkNumber = size / pkSize;
    UInt32 remind = size - (pkNumber * pkSize);
    UInt32 i;
    UInt8* ptr;

    UInt8 sizeRcv;

    UInt32 timeout = 4;

    ptr = buffer;
    for (i=0; i < pkNumber; i++)
    {
        while (1)
        {
            if (uartRead(linkBuffer,RADIO_BUFFER_SIZE)==RADIO_BUFFER_SIZE)
            {
                sizeRcv = linkBuffer[0] & SIZE_MASK;

//                qDebug() << "Read packet:" << i << " flag: " << linkBuffer[0] << " Size:" << sizeRcv;

                if (i==0 && (linkBuffer[0] & FIRST_PACKET) != FIRST_PACKET )
                {
                    qDebug() << "RadioUart::read: not first packet (1)!";
                    return 0;
                }

                if (sizeRcv!=pkSize)
                {
                    qDebug() << "RadioUart::read: wrong size " << sizeRcv << " pk "<< pkSize;
                    return 0;
                }

                memcpy(ptr, &linkBuffer[1], pkSize);
                ptr += pkSize;
                break;
            }
            else
            {
                return 0;
            }
        }
    }

    if (remind!=0)
    {
        while (1)
        {
            if (uartRead(linkBuffer,RADIO_BUFFER_SIZE)==RADIO_BUFFER_SIZE)
            {
                sizeRcv = linkBuffer[0] & SIZE_MASK;

//                qDebug() << "Read remind flag " << linkBuffer[0] << " Size" << sizeRcv;

                if (pkNumber==0 && (linkBuffer[0] & FIRST_PACKET) != FIRST_PACKET )
                {
                    qDebug() << "RadioUart::read: not first packet (2)!";
                    return false;
                }

                if ((linkBuffer[0] & END_OF_PACKET) != END_OF_PACKET)
                {
                    qDebug() << "RadioUart::read: end of packet failed!";
                    return false;
                }

                if (sizeRcv!=remind)
                {
                    qDebug() << "RadioUart::read: wrong size " << linkBuffer[0] << "remind " << remind;
                    return false;
                }

                memcpy(ptr, &linkBuffer[1], remind);
                ptr += pkSize;
                break;
            }
            else
            {
                qDebug() << "RadioUart::read timeout remind" << remind;
                return 0;
            }
        }
    }

    return size;
}

void RadioUart::close(void)
{
    closeUART();
}
