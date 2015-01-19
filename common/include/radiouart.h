/* The MIT License (MIT)
 
 Copyright (c) 2014 Baptiste Burles, Kliplab
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 */
#ifndef RADIOUART_H
#define RADIOUART_H

#include <QtCore/QString>
#include <babextended.h>

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
