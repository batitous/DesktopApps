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

bool RadioUart::getUartByte(uint8_t * b)
{
    uint32_t timeout = 24;

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


bool RadioUart::uartWrite(uint8_t *buffer, uint32_t size)
{
    uint32_t result = sendBufferToUART(buffer, size);

    if (result!=UART_OK)
    {
        qDebug() << "RadioUart::uartWrite failed code " << result;
        return false;
    }

    return true;
}

uint32_t RadioUart::uartRead(uint8_t *buffer, uint32_t size)
{
    uint32_t counter;

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
    uint8_t b;
    char * comport = (char *)specific.toLatin1().constData();
    uint32_t result = initUART(comport, 115200);

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

bool RadioUart::write(uint8_t *buffer, uint32_t size)
{
    uint32_t pkSize = RADIO_BUFFER_SIZE-1;
    uint32_t pkNumber = size / pkSize;
    uint32_t remind = size - (pkNumber * pkSize);
    uint32_t i;
    uint8_t* ptr;
    uint8_t flag;

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

uint32_t RadioUart::read(uint8_t *buffer, uint32_t size)
{
    uint32_t pkSize = RADIO_BUFFER_SIZE-1;
    uint32_t pkNumber = size / pkSize;
    uint32_t remind = size - (pkNumber * pkSize);
    uint32_t i;
    uint8_t* ptr;

    uint8_t sizeRcv;

    uint32_t timeout = 4;

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
