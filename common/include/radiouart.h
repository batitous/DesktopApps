// Baptiste Burles, Kliplab, 2014

#ifndef RADIOUART_H
#define RADIOUART_H

#include <QtCore/QString>
#include <babcode.h>

#define RADIO_BUFFER_SIZE       (32)

class RadioUart
{
public:
    static RadioUart* instance();

    ~RadioUart(void);

    bool open(const QString & specific);

    void close();

    bool write(UInt8 *buffer, UInt32 size);

    UInt32 read(UInt8 *buffer, UInt32 size);

private:
    RadioUart(void);

    static RadioUart* radioUart;

    UInt8 linkBuffer[RADIO_BUFFER_SIZE];

    bool getUartByte(UInt8 * b);
    bool uartWrite(UInt8 *buffer, UInt32 size);
    UInt32 uartRead(UInt8 *buffer, UInt32 size);
};

#endif // RADIOUART_H
