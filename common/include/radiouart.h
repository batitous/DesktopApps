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

    bool write(uint8_t *buffer, uint32_t size);

    uint32_t read(uint8_t *buffer, uint32_t size);

private:
    RadioUart(void);

    static RadioUart* radioUart;

    Uart   mUart;
    uint8_t linkBuffer[RADIO_BUFFER_SIZE];

    bool getUartByte(uint8_t * b);
    bool uartWrite(uint8_t *buffer, uint32_t size);
    uint32_t uartRead(uint8_t *buffer, uint32_t size);
};

#endif // RADIOUART_H
